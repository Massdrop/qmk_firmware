#include QMK_KEYBOARD_H

enum alt_keycodes {
  L_BRI = SAFE_RANGE, //LED Brightness Increase
  L_BRD,              //LED Brightness Decrease
  L_PTN,              //LED Pattern Select Next
  L_PTP,              //LED Pattern Select Previous
  L_PSI,              //LED Pattern Speed Increase
  L_PSD,              //LED Pattern Speed Decrease
  L_T_MD,             //LED Toggle Mode
  L_T_ONF,            //LED Toggle On / Off
  L_ON,               //LED On
  L_OFF,              //LED Off
  L_T_BR,             //LED Toggle Breath Effect
  L_T_PTD,            //LED Toggle Scrolling Pattern Direction
  U_T_AUTO,           //USB Extra Port Toggle Auto Detect / Always Active
  U_T_AGCR,           //USB Toggle Automatic GCR control
  DBG_TOG,            //DEBUG Toggle On / Off
  DBG_MTRX,           //DEBUG Toggle Matrix Prints
  DBG_KBD,            //DEBUG Toggle Keyboard Prints
  DBG_MOU,            //DEBUG Toggle Mouse Prints
  MD_BOOT,            //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
  [1] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_MUTE, \
    L_T_BR,  L_PSD,   L_BRI,   L_PSI,   KC_TRNS, KC_TRNS, KC_TRNS, U_T_AUTO,U_T_AGCR,KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_END, \
    L_T_PTD, L_PTP,   L_BRD,   L_PTN,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_VOLU, \
    KC_TRNS, L_T_MD,  L_T_ONF, KC_TRNS, KC_TRNS, MD_BOOT, TG_NKRO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_PGUP, KC_VOLD, \
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END  \
  ),
  /*
  [X] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
  ),
  */
};

const uint16_t PROGMEM fn_actions[] = {

};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (keyboard_report->mods & MOD_BIT(KC_LSHIFT) || keyboard_report->mods & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (keyboard_report->mods & MOD_BIT(KC_LCTL) || keyboard_report->mods & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (keyboard_report->mods & MOD_BIT(KC_LALT) || keyboard_report->mods & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t key_timer;

  keypos_t key = record->event.key;
  uint8_t led_id = MATRIX_TO_LED_ID[key.row][key.col];

  if (led_id > 0) {
    uint8_t led_col = LED_ID_TO_KEYMAP[led_id].col;
    uint8_t led_row = LED_ID_TO_KEYMAP[led_id].row;

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (record->event.pressed) {
      g = 255;
      b = 125;
    }

    uint8_t row = 0;
    while (row < KEYMAP_ROWS) {
      rgb_matrix_set_color(KEYMAP_TO_LED_ID[row][led_col], r, g, b);
      row += 1;
    }

    uint8_t col = 0;
    while (col < KEYMAP_COLS) {
      rgb_matrix_set_color(KEYMAP_TO_LED_ID[led_row][col], r, g, b);
      col += 1;
    }
  }

  switch (keycode) {
    case U_T_AUTO:
      if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
        TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
      }
      return false;
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
        if (timer_elapsed32(key_timer) >= 500) {
          reset_keyboard();
        }
      }
      return false;
    default:
      return true; //Process all other keycodes normally
  }
}
