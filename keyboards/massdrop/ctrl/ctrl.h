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
  K61, K62, K63, K64, K65, K66, K67, K68, K69, K70, K71, K72, K73, K74, K75, \
  K76, K77, K78, K79, K80, K81, K82, K83, K84, K85, K86, K87 \
  \
) { \
  {   K01, K02, K03, K04, K05, K06, K07, K08   }, \
  {   K17, K18, K19, K20, K21, K22, K23, K24   }, \
  {   K34, K35, K36, K37, K38, K39, K40, K41   }, \
  {   K51, K52, K53, K54, K55, K56, K57, K58   }, \
  {   K64, K65, K66, K67, K68, K69, K70, K71   }, \
  {   K77, K78, K79, K80, K81, K82, K83, K84   }, \
  {   K09, K10, K11, K12, K13, K14, K15, K16   }, \
  {   K25, K26, K27, K28, K29, K30, K31, K32   }, \
  {   K42, K43, K44, K45, K46, K47, K48, K49   }, \
  {   K59, K60, K61, K62, K63, K76, K50, K33   }, \
  {   K72, K73, K74, K75, K85, K86, K87,       }, \
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
  {  1,  2,  3,  4,  5,  6,  7,  8 },
  { 17, 18, 19, 20, 21, 22, 23, 24 },
  { 34, 35, 36, 37, 38, 39, 40, 41 },
  { 51, 52, 53, 54, 55, 56, 57, 58 },
  { 64, 65, 66, 67, 68, 69, 70, 71 },
  { 77, 78, 79, 80, 81, 82, 83, 84 },
  {  9, 10, 11, 12, 13, 14, 15, 16 },
  { 25, 26, 27, 28, 29, 30, 31, 32 },
  { 42, 43, 44, 45, 46, 47, 48, 49 },
  { 59, 60, 61, 62, 63, 76, 50, 33 },
  { 72, 73, 74, 75, 85, 86, 87,  0 }
};

static const keypos_t LED_ID_TO_KEYMAP[109] = {
  { .col = -1, .row = -1 }, // Dummy row for 0s above

  // row 0: 1 - 18
  { .col =  0, .row =  0 },
  // gap
  { .col =  2, .row =  0 },
  { .col =  3, .row =  0 },
  { .col =  4, .row =  0 },
  { .col =  5, .row =  0 },
  { .col =  6, .row =  0 },
  { .col =  7, .row =  0 },
  { .col =  8, .row =  0 },
  { .col =  9, .row =  0 },
  // gap
  { .col = 11, .row =  0 },
  { .col = 12, .row =  0 },
  { .col = 13, .row =  0 },
  { .col = 14, .row =  0 },
  { .col = 15, .row =  0 },
  { .col = 16, .row =  0 },
  { .col = 17, .row =  0 }, // LED 16

  // row 1: 19 - 36
  { .col =  0, .row =  1 },
  { .col =  1, .row =  1 },
  { .col =  2, .row =  1 },
  { .col =  3, .row =  1 }, // LED 20
  { .col =  4, .row =  1 },
  { .col =  5, .row =  1 },
  { .col =  6, .row =  1 },
  { .col =  7, .row =  1 },
  { .col =  8, .row =  1 },
  { .col =  9, .row =  1 },
  { .col = 10, .row =  1 },
  { .col = 11, .row =  1 },
  { .col = 12, .row =  1 }, // LED 29
  // gap
  { .col = 14, .row =  1 },
  { .col = 15, .row =  1 },
  { .col = 16, .row =  1 },
  { .col = 17, .row =  1 },

  // row 2: 37 - 54
  { .col =  0, .row =  2 }, // LED 34
  // gap
  { .col =  2, .row =  2 },
  { .col =  3, .row =  2 },
  { .col =  4, .row =  2 },
  { .col =  5, .row =  2 },
  { .col =  6, .row =  2 },
  { .col =  7, .row =  2 },
  { .col =  8, .row =  2 },
  { .col =  9, .row =  2 },
  { .col = 10, .row =  2 },
  { .col = 11, .row =  2 },
  { .col = 12, .row =  2 }, // LED 45
  { .col = 13, .row =  2 },
  { .col = 14, .row =  2 },
  { .col = 15, .row =  2 },
  { .col = 16, .row =  2 },
  { .col = 17, .row =  2 },

  // row 3: 55 - 72
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
  // gap
  { .col = 14, .row =  3 },
  // gap
  // gap
  // gap

  // row 4: 73 - 90
  { .col =  0, .row =  4 },
  // gap
  { .col =  2, .row =  4 },
  { .col =  3, .row =  4 },
  { .col =  4, .row =  4 },
  { .col =  5, .row =  4 },
  { .col =  6, .row =  4 },
  { .col =  7, .row =  4 },
  { .col =  8, .row =  4 },
  { .col =  9, .row =  4 },
  { .col = 10, .row =  4 },
  { .col = 11, .row =  4 },
  // gap
  { .col = 13, .row =  4 },
  // gap
  // gap
  { .col = 16, .row =  4 },
  // gap

  // row 5: 91 - 108
  { .col =  0, .row =  5 },
  { .col =  1, .row =  5 },
  // gap
  { .col =  3, .row =  5 },
  // gap
  // gap
  { .col =  6, .row =  5 },
  // gap
  // gap
  // gap
  { .col = 10, .row =  5 },
  { .col = 11, .row =  5 },
  // gap
  { .col = 13, .row =  5 },
  { .col = 14, .row =  5 },
  { .col = 15, .row =  5 },
  { .col = 16, .row =  5 },
  { .col = 17, .row =  5 },
};

// Rows/cols match key laoyut. Values correspond to LED IDs.
// Note that matrix and key layout do not match for CTRL Keyboard.
static const uint8_t KEYMAP_TO_LED_ID[KEYMAP_ROWS][KEYMAP_COLS] = {
  {  1,  0,  2,  3,  4,  5,  6,  7,  8,  9,  0, 10, 11, 12, 13, 14, 15, 16 },
  { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,  0, 30, 31, 32, 33 },
  { 34,  0, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 },
  { 51,  0, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,  0, 63,  0,  0,  0 },
  { 64,  0, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,  0, 75,  0,  0, 76,  0 },
  { 77, 78,  0, 79,  0,  0, 80,  0,  0,  0, 81, 82,  0, 83, 84, 85, 86, 87 }
};
