/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID           0x04D8
#define PRODUCT_ID          0xEE67
#define DEVICE_VER          0x0100

#define MANUFACTURER        "Drop Inc."
#define PRODUCT             "Drop NUMPAD Keyboard"
#define SERIAL_NUM          "Unavailable"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

/* MCU Port name definitions */
#define PA 0
#define PB 1

/* Port and Pin definition of key row hardware configuration */
#define MATRIX_ROW_PORTS PA, PA, PA, PA, PA, PA
#define MATRIX_ROW_PINS   0,  1,  2,  3,  4,  5

/* Port and Pin definition of key column hardware configuration */
#define MATRIX_COL_PORTS PB, PB, PB, PB
#define MATRIX_COL_PINS   4,  5,  6,  7

#define IRST_PORT					PB
#define IRST_PIN					10
#define IRST_ENABLE PORT->Group[IRST_PORT].DIRSET.reg = (1 << IRST_PIN)
#define IRST_ON  PORT->Group[IRST_PORT].OUTSET.reg = (1 << IRST_PIN)
#define IRST_OFF PORT->Group[IRST_PORT].OUTCLR.reg = (1 << IRST_PIN)

#define SDB_PORT					PB
#define SDB_PIN						11
#define SDB_ENABLE PORT->Group[SDB_PORT].DIRSET.reg = (1 << SDB_PIN)
#define SDB_ENABLEIN PORT->Group[SDB_PORT].PINCFG[SDB_PIN].bit.INEN = 1
#define SDB_ON  PORT->Group[SDB_PORT].OUTSET.reg = (1 << SDB_PIN)
#define SDB_OFF PORT->Group[SDB_PORT].OUTCLR.reg = (1 << SDB_PIN)
#define SDB_IN()  ((PORT->Group[SDB_PORT].IN.reg & (1 << SDB_PIN)) != 0)

/* Debug LED (Small LED Located near MCU) */
/* PCB M15 */
#define DEBUG_LED_ENABLE            1
#define DEBUG_LED_PORT              PA
#define DEBUG_LED_PIN               27

// NUMPAD has no Hub
#define NO_MD_USB2422

/* Additional debugging ports */
/* PCB M44 */
//#define DEBUG_PORT1_ENABLE          1
//#define DEBUG_PORT1_PORT            PB
//#define DEBUG_PORT1_PIN             31
/* PCB M45 */
//#define DEBUG_PORT2_ENABLE          1
//#define DEBUG_PORT2_PORT            PB
//#define DEBUG_PORT2_PIN             10
/* PCB M46 */
//#define DEBUG_PORT3_ENABLE          1
//#define DEBUG_PORT3_PORT            PB
//#define DEBUG_PORT3_PIN             11

/* Debug Boot Tracing - During boot sequence, ground this pin to halt and display debug code using Debug LED */
/* This is useful in determining which hardware device may have malfunctioned or is improperly configured */
/* Feature is automatically disabled after successful boot */
/* PCB M27 */
#define DEBUG_BOOT_TRACING_ENABLE   1
#define DEBUG_BOOT_TRACING_PORT     PB
#define DEBUG_BOOT_TRACING_PIN      23

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

// Required BOOT key hold time (in ms) for restarting to bootloader -PS081419
#define BOOTKEY_HOLD_MS		2000

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* Force boot in NKRO mode */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_LED_PROCESS_LIMIT 15
#define RGB_MATRIX_LED_FLUSH_LIMIT 10
#define RGB_MATRIX_EXTRA_TOG

#include "config_led.h"
