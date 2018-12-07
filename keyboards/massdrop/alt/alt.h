#pragma once

#include "quantum.h"
#include "config_led.h"
#include "matrix.h"

#include "i2c_master.h"
#include "led_matrix.h" //For led keycodes
#include "led_instructions.h"
#include "usb/udi_cdc.h"
#include "usb/usb2422.h"

#define LAYOUT( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K14, K15, \
    K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K30, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, \
    K46, K47, K48, K49, K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, \
    K61, K62, K63, K64, K65, K66, K67 \
) { \
    {   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,   K12,   K13,   K14,   K15, }, \
    {   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K30, }, \
    {   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K40,   K41,   K42, KC_NO,   K43,   K44, }, \
    {   K45, KC_NO,   K46,   K47,   K48,   K49,   K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58, }, \
    {   K59,   K60,   K61, KC_NO, KC_NO, KC_NO,   K62, KC_NO, KC_NO, KC_NO,   K63,   K64,   K65,   K66,   K67, }, \
}

#define TOGGLE_FLAG_AND_PRINT(var, name) { \
        if (var) { \
            dprintf(name " disabled\r\n"); \
            var = !var; \
        } else { \
            var = !var; \
            dprintf(name " enabled\r\n"); \
        } \
    }

// Rows/cols match key matrix. Values correspond to LED IDs.
static const uint8_t MATRIX_TO_LED_ID[MATRIX_ROWS][MATRIX_COLS] = {
  {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
  { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
  { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,  0, 43, 44 },
  { 45,  0, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 },
  { 59, 60, 61,  0,  0,  0, 62,  0,  0,  0, 63, 64, 65, 66, 67 },
};

static const keypos_t LED_ID_TO_KEYMAP[68] = {
  { .col = -1, .row = -1 }, // Dummy row for 0s above

  // 1 - 15
  { .col =  0, .row =  0 },
  { .col =  1, .row =  0 },
  { .col =  2, .row =  0 },
  { .col =  3, .row =  0 },
  { .col =  4, .row =  0 },
  { .col =  5, .row =  0 },
  { .col =  6, .row =  0 },
  { .col =  7, .row =  0 },
  { .col =  8, .row =  0 },
  { .col =  9, .row =  0 },
  { .col = 10, .row =  0 },
  { .col = 11, .row =  0 },
  { .col = 12, .row =  0 },
  { .col = 13, .row =  0 },
  { .col = 14, .row =  0 }, // LED 15

  // 16 - 30
  { .col =  0, .row =  1 },
  { .col =  1, .row =  1 },
  { .col =  2, .row =  1 },
  { .col =  3, .row =  1 },
  { .col =  4, .row =  1 },
  { .col =  5, .row =  1 },
  { .col =  6, .row =  1 },
  { .col =  7, .row =  1 },
  { .col =  8, .row =  1 },
  { .col =  9, .row =  1 },
  { .col = 10, .row =  1 },
  { .col = 11, .row =  1 },
  { .col = 12, .row =  1 },
  { .col = 13, .row =  1 },
  { .col = 14, .row =  1 }, // LED 30

  // 31 - 44
  { .col =  0, .row =  2 },
  { .col =  1, .row =  2 },
  { .col =  2, .row =  2 },
  { .col =  3, .row =  2 },
  { .col =  4, .row =  2 },
  { .col =  5, .row =  2 },
  { .col =  6, .row =  2 },
  { .col =  7, .row =  2 },
  { .col =  8, .row =  2 },
  { .col =  9, .row =  2 },
  { .col = 10, .row =  2 },
  { .col = 11, .row =  2 }, // LED 42
  // gap
  { .col = 13, .row =  2 },
  { .col = 14, .row =  2 },

  // 45 - 58
  { .col =  0, .row =  3 },
  // gap
  { .col =  2, .row =  3 },
  { .col =  3, .row =  3 },
  { .col =  4, .row =  3 },
  { .col =  5, .row =  3 },
  { .col =  6, .row =  3 },
  { .col =  7, .row =  3 },
  { .col =  8, .row =  3 },
  { .col =  9, .row =  3 },
  { .col = 10, .row =  3 },
  { .col = 11, .row =  3 },
  { .col = 12, .row =  3 },
  { .col = 13, .row =  3 },
  { .col = 14, .row =  3 },

  // 59 - 67
  { .col =  0, .row =  4 },
  { .col =  1, .row =  4 },
  { .col =  2, .row =  4 },
  // gap
  // gap
  // gap
  { .col =  6, .row =  4 },
  // gap
  // gap
  // gap
  { .col = 10, .row =  4 },
  { .col = 11, .row =  4 },
  { .col = 12, .row =  4 },
  { .col = 13, .row =  4 },
  { .col = 14, .row =  4 },
};

// Rows/cols match key laoyut. Values correspond to LED IDs.
// Note that matrix and key layout may not match (see CTRL Keyboard)
static const uint8_t KEYMAP_TO_LED_ID[KEYMAP_ROWS][KEYMAP_COLS] = {
  {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
  { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
  { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,  0, 43, 44 },
  { 45,  0, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 },
  { 59, 60, 61,  0,  0,  0, 62,  0,  0,  0, 63, 64, 65, 66, 67 },
};
