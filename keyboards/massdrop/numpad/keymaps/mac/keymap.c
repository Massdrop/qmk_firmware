#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AGCR = SAFE_RANGE, //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  MO(1),   KC_TAB,  KC_BSPC,  \
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
        KC_P7,   KC_P8,   KC_P9,   			\
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
        KC_P1,   KC_P2,   KC_P3,            \
        KC_P0,            KC_PDOT, KC_PENT  \
    ),
    [1] = LAYOUT(
    	U_T_AGCR,_______, _______, _______, \
        KC_MPLY, KC_MSTP, KC_VOLU, KC_MUTE, \
        KC_MPRV, KC_MNXT, KC_VOLD,          \
        _______, _______, _______, _______, \
        _______, _______, _______,          \
		MD_BOOT,          TG_NKRO, DBG_TOG  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, \
        _______, _______, _______, _______, \
        _______, _______, _______,          \
        _______, _______, _______, _______, \
        _______, _______, _______, 	        \
        _______, _______, _______, _______, \
     ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    reset_keyboard();
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
