#include "quantum.h"
#include "led_matrix.h"
#include QMK_KEYBOARD_H

static uint16_t last_boost_update;
static uint8_t led_boosts[ISSI3733_LED_COUNT + 1];
static uint8_t led_boost_index;
static uint8_t led_cur_index;

#define LED_BOOST_REFRESH_INTERVAL_IN_MS 40
#define LED_BOOST_DECAY 0.7
#define LED_BOOST_PROPAGATE 0.5
#define LED_BOOST_PEAK 100

#define MIN_RGB 0x050008
#define MIN_R (MIN_RGB >> 16 & 0xff)
#define MIN_G (MIN_RGB >> 8 & 0xff)
#define MIN_B (MIN_RGB & 0xff)

#define MAX_RGB 0xc26eff
#define MAX_R (MAX_RGB >> 16 & 0xff)
#define MAX_G (MAX_RGB >> 8 & 0xff)
#define MAX_B (MAX_RGB & 0xff)

#define UNDERGLOW_RGB 0x4f002e
#define UNDERGLOW_R (UNDERGLOW_RGB >> 16 & 0xff)
#define UNDERGLOW_G (UNDERGLOW_RGB >> 8 & 0xff)
#define UNDERGLOW_B (UNDERGLOW_RGB & 0xff)

#define UNDERGLOW_SCAN_CODE 255

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define KEY_LED_COUNT 67

static void update_led_boosts(void);
static void set_nearest_led_to_max(uint8_t col, uint8_t row);
static uint8_t calculate_new_color_component_value(issi3733_led_t *led_cur, uint8_t max, uint8_t min);
static void calculate_new_led_boosts(uint8_t new_led_boosts[]);
static uint8_t calculate_new_led_boost_at(int index);
static uint8_t get_propagated_boost_from_neighbors(int led_position);
static uint8_t get_led_boost_at_keypos(uint8_t row, uint8_t col);
static void set_new_led_boosts(uint8_t* new_led_boosts);
static uint8_t map_key_position_to_led_index(uint8_t col, uint8_t row);


void rgb_matrix_init_user(void) {
  for (int i = 1; i <= ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = 0;
  }
  last_boost_update = timer_read();
  led_boost_index = 0;
  led_cur_index = 0;
}

void rgb_matrix_run_user(led_disp_t disp) {
  led_cur_index = 0;
  update_led_boosts();
}

void rgb_matrix_record_key_press(keyrecord_t *record) {
  if (record->event.pressed) {
    keypos_t key = record->event.key;
    set_nearest_led_to_max(key.col, key.row);
  }
}


static void update_led_boosts(void) {
  if (timer_elapsed(last_boost_update) > LED_BOOST_REFRESH_INTERVAL_IN_MS) {
    last_boost_update = timer_read();

    uint8_t new_led_boosts[ISSI3733_LED_COUNT + 1];
    calculate_new_led_boosts(new_led_boosts);
    set_new_led_boosts(new_led_boosts);
  }
}

void rgb_run(issi3733_led_t *led_cur) {
  if (led_cur->scan == UNDERGLOW_SCAN_CODE) {
    *led_cur->rgb.r = UNDERGLOW_R;
    *led_cur->rgb.g = UNDERGLOW_G;
    *led_cur->rgb.b = UNDERGLOW_B;
  } else {
    *led_cur->rgb.r = calculate_new_color_component_value(led_cur, MAX_R, MIN_R);
    *led_cur->rgb.g = calculate_new_color_component_value(led_cur, MAX_G, MIN_G);
    *led_cur->rgb.b = calculate_new_color_component_value(led_cur, MAX_B, MIN_B);
  }
}

static void set_nearest_led_to_max(uint8_t col, uint8_t row) {
  uint8_t led_index = map_key_position_to_led_index(col, row);
  if (led_index > 0 && led_index <= ISSI3733_LED_COUNT) {
    led_boosts[led_index] = LED_BOOST_PEAK;
  }
}

static uint8_t calculate_new_color_component_value(issi3733_led_t *led_cur, uint8_t max, uint8_t min) {
  uint8_t current_boost = led_boosts[led_cur->id];
  return (float)(max - min) * current_boost / LED_BOOST_PEAK + min;
}

static void calculate_new_led_boosts(uint8_t new_led_boosts[]) {
  for (int i = 1; i <= ISSI3733_LED_COUNT; i++) {
    new_led_boosts[i] = calculate_new_led_boost_at(i);
  }
}

static uint8_t calculate_new_led_boost_at(int index) {
  uint8_t decayed_boost = led_boosts[index] * LED_BOOST_DECAY;
  uint8_t propagated_boost = get_propagated_boost_from_neighbors(index);
  uint8_t new_boost = (propagated_boost > decayed_boost) ? propagated_boost : decayed_boost;
  if (new_boost > LED_BOOST_PEAK) {
    new_boost = LED_BOOST_PEAK;
  }
  return new_boost;
}

static uint8_t get_propagated_boost_from_neighbors(int led_position) {
  if (led_position < 0 || led_position > KEY_LED_COUNT) {
    return 0;
  }
  keypos_t led_keypos = LED_ID_TO_KEYMAP[led_position];
  uint8_t top_boost    = get_led_boost_at_keypos(led_keypos.row - 1, led_keypos.col);
  uint8_t bottom_boost = get_led_boost_at_keypos(led_keypos.row + 1, led_keypos.col);
  uint8_t left_boost   = get_led_boost_at_keypos(led_keypos.row, led_keypos.col - 1);
  uint8_t right_boost  = get_led_boost_at_keypos(led_keypos.row, led_keypos.col + 1);
  uint8_t max_boost = max(max(top_boost, bottom_boost), max(left_boost, right_boost));
  if (max_boost > LED_BOOST_PEAK) {
    max_boost = LED_BOOST_PEAK;
  }
  return max_boost * LED_BOOST_PROPAGATE;
}

static uint8_t get_led_boost_at_keypos(uint8_t row, uint8_t col) {
  if (row < 0 || row >= MATRIX_ROWS || col < 0 || col >= MATRIX_COLS) {
    return 0;
  }
  uint8_t led_index = KEYMAP_TO_LED_ID[row][col];
  if (led_index <= 0) {
    return 0;
  }
  return led_boosts[led_index];
}

static void set_new_led_boosts(uint8_t* new_led_boosts) {
  for (int i = 1; i <= ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = new_led_boosts[i];
  }
}

static uint8_t map_key_position_to_led_index(uint8_t col, uint8_t row) {
  if (row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS) {
    return KEYMAP_TO_LED_ID[row][col];
  }
  return -1;
}
