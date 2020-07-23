/*
Copyright 2019 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef RAW_ENABLE

#    include "arm_atsam_protocol.h"
#    include <string.h>
#    include <raw_hid.h>
#    include <version.h>

#    define COMPILE_VER QMK_KEYBOARD ":" QMK_KEYMAP

// MFT Test Protocol Definitions

#    define RAWP_PROTOCOL_VERSION 0x00
#    define RAWP_CAT_MFGTEST 0x01

#    define RAWP_CMD_SET_RGB_MODE 0x01
#    define RAWP_CMD_SET_ALL_RGBS 0x02
#    define RAWP_CMD_SET_SPEC_RGBS 0x03
#    define RAWP_CMD_READ_ALL_ADCS 0x04
#    define RAWP_CMD_RET_GCR_INFO 0x05
#    define RAWP_CMD_RET_FW_INFO 0x06
#    define RAWP_CMD_RET_QMK_INFO 0x07

enum { RET_Success, RET_Fail, RET_Inactive, RET_UnknownCommand, RET_LEDNotFound };

typedef struct {
    uint8_t prot_ver;  // Protocol Version
    uint8_t cat;       // Category
    uint8_t cmd;       // Command
    uint8_t data[61];  // Parameters
} __attribute__((packed)) sRawp_command_t;

typedef struct {
    uint8_t prot_ver;  // Protocol Version
    uint8_t cat;       // Category
    uint8_t cmd;       // Command
    uint8_t result;    // Result
    uint8_t data[60];  // Parameters
} __attribute__((packed)) sRawp_response_t;

static uint8_t  raw_hid_todo    = 0;
static uint8_t *raw_hid_databuf = 0;

static void set_all_leds(uint8_t area, uint8_t r, uint8_t g, uint8_t b);
static bool set_one_led_id(uint8_t id, uint8_t r, uint8_t g, uint8_t b);

void raw_hid_receive(uint8_t *data, uint8_t length) {
    sRawp_command_t *pcmd = (sRawp_command_t *)data;
    sRawp_response_t resp;
    uint8_t          result = RET_Fail;

    if (length != RAW_EPSIZE) return;  // Whaa?  Shouldn't happen

    if ((pcmd->prot_ver != RAWP_PROTOCOL_VERSION) || (pcmd->cat != RAWP_CAT_MFGTEST)) return;

    memset((void *)&resp, 0, sizeof(resp));
    resp.prot_ver = pcmd->prot_ver;
    resp.cat      = pcmd->cat;
    resp.cmd      = pcmd->cmd;

    switch (pcmd->cmd) {
        case RAWP_CMD_SET_RGB_MODE:
            if (pcmd->data[0] > 0) {
                led_mfg_test_mode = LED_MFG_TEST_MODE_RAWP;
            } else {
                led_mfg_test_mode = LED_MFG_TEST_MODE_OFF;
            }
            result = RET_Success;
            break;

        case RAWP_CMD_SET_ALL_RGBS:
            set_all_leds(pcmd->data[0], pcmd->data[1], pcmd->data[2], pcmd->data[3]);
            if (pcmd->data[4] != 0) {
                usb_gcr_auto = 0;  // Manual GCR setting
                gcr_desired  = (pcmd->data[4] > LED_GCR_MAX ? LED_GCR_MAX : pcmd->data[4]);
            } else {
                usb_gcr_auto = 1;
            }
            result = RET_Success;
            break;

        case RAWP_CMD_SET_SPEC_RGBS: {
            uint8_t i, num = pcmd->data[0];
            uint8_t id, r, g, b;

            if (num > 0 && num <= 15) {
                result = RET_Success;
                for (i = 0; i < num; i++) {
                    id = pcmd->data[i * 4 + 1];
                    r  = pcmd->data[i * 4 + 2];
                    g  = pcmd->data[i * 4 + 3];
                    b  = pcmd->data[i * 4 + 4];
                    if (id == 0) {
                        set_all_leds(LED_MODE_NORMAL, r, g, b);
                    } else {
                        if (set_one_led_id(id, r, g, b) != true) {
                            // Flag at least one LED ID not found
                            result = RET_LEDNotFound;
                        }
                    }
                }
            } else {
                result = RET_Fail;
                break;
            }
            break;
        }

        case RAWP_CMD_READ_ALL_ADCS:
            raw_hid_todo    = RAWP_CMD_READ_ALL_ADCS;
            raw_hid_databuf = data;
            return;  // do not send any packet - defer to execute in foreground

        case RAWP_CMD_RET_GCR_INFO:
            resp.data[0] = ((uint16_t)g_v_5v_avg) & 0xff;
            resp.data[1] = ((uint16_t)g_v_5v_avg) >> 8;
            resp.data[2] = gcr_desired & 0xff;
            resp.data[3] = gcr_desired >> 8;
            resp.data[4] = gcr_actual & 0xff;
            resp.data[5] = gcr_actual >> 8;
            resp.data[6] = gcr_actual_last & 0xff;
            resp.data[7] = gcr_actual_last >> 8;
            result       = RET_Success;
            break;

        case RAWP_CMD_RET_FW_INFO: {
            uint8_t        length = 0;
            const uint8_t *str    = udc_get_string_serial_name(&length);

            resp.data[0] = PRODUCT_ID & 0xff;
            resp.data[1] = PRODUCT_ID >> 8;
            resp.data[2] = DEVICE_VER & 0xff;
            resp.data[3] = DEVICE_VER >> 8;
            if (str != NULL) {
                strncpy((char *)(&resp.data[4]), (char *)str, (length < 16 ? length : 16));
            } else {
                strncpy((char *)(&resp.data[4]), SERIAL_NUM, 16);
            }
            strncpy((char *)(&resp.data[20]), COMPILE_VER, 40);
            result = RET_Success;
            break;
        }

        case RAWP_CMD_RET_QMK_INFO:
            strncpy((char *)(&resp.data[0]), QMK_VERSION, 40);
            strncpy((char *)(&resp.data[40]), QMK_BUILDDATE, 20);
            result = RET_Success;
            break;

        default:
            // Unhandled command
            result = RET_UnknownCommand;
    }

    resp.result = result;

    raw_hid_send((uint8_t *)&resp, sizeof(resp));
}

void raw_hid_task(void) {
    sRawp_command_t *pcmd = (sRawp_command_t *)raw_hid_databuf;
    sRawp_response_t resp;
    uint8_t          result = RET_Fail;

    if ((raw_hid_todo == RAWP_CMD_READ_ALL_ADCS) && (raw_hid_databuf != NULL)) {
        uint8_t  mask = pcmd->data[0];
        uint8_t  i, count = 0;
        uint16_t val;

        memset((void *)&resp, 0, sizeof(resp));
        resp.prot_ver = pcmd->prot_ver;
        resp.cat      = pcmd->cat;
        resp.cmd      = pcmd->cmd;

        for (i = 0; i < ADC_NUM_INDICES; i++) {
            if (mask & 0x01) {
                val = adc_get(i);
                if (val != (uint16_t)ADC_NA) {
                    resp.data[count * 3 + 1] = i;
                    resp.data[count * 3 + 2] = val & 0xff;
                    resp.data[count * 3 + 3] = val >> 8;
                    count++;
                }
            }
            mask >>= 1;
        }
        resp.data[0] = count;
        result       = RET_Success;

        resp.result = result;
        raw_hid_send((uint8_t *)&resp, sizeof(resp));

        raw_hid_todo    = 0;
        raw_hid_databuf = 0;
    }
}

static void set_all_leds(uint8_t mode, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        if ((mode == LED_MODE_NORMAL) || ((mode == LED_MODE_KEYS_ONLY) && !(LED_IS_EDGE(led_map[i].scan) || LED_IS_INDICATOR(led_map[i].scan))) || ((mode == LED_MODE_NON_KEYS_ONLY) && (LED_IS_EDGE(led_map[i].scan) || LED_IS_INDICATOR(led_map[i].scan))) || ((mode == LED_MODE_INDICATORS_ONLY) && LED_IS_INDICATOR(led_map[i].scan))) {
            led_set_one_rawp(i, r, g, b);
        }
    }
}

static bool set_one_led_id(uint8_t id, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        if (id == led_map[i].id) {
            led_set_one_rawp(i, r, g, b);
            return (true);
        }
    }
    return (false);
}
#endif  // RAW_ENABLE
