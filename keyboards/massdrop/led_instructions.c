#include <math.h>
#include <stdint.h>
#include "led_matrix.h"
#include "led_instructions.h"
#include "quantum.h"

uint8_t highest_active_layer = 0;
uint32_t temp_layer_state = 0;

__attribute__((weak))
led_instruction_t led_instructions[] = { { .end = 1 } };

// TODO: is there a better way to allocate this array to be the same length as
// the led_setups array?
float animation_offsets[11];

float breathe_mult;

uint8_t led_animation_id;
uint8_t led_lighting_mode;
float led_animation_period_scalar;
uint8_t led_animation_direction;
uint8_t led_animation_orientation;
uint8_t led_animation_breathe_cur;
uint8_t breathe_step;
uint8_t breathe_dir;

uint32_t ef_axis_x = EF_AXIS_X;
uint32_t ef_axis_x_invert = EF_AXIS_X_INVERT;
uint32_t ef_axis_y = EF_AXIS_Y;
uint32_t ef_axis_y_invert = EF_AXIS_Y_INVERT;

led_setup_t *led_animation;

void rgb_matrix_init_user(void) {
  led_animation_id = 0;
  led_lighting_mode = LED_MODE_NORMAL;
  led_animation_period_scalar = 1;
  led_animation_direction = 0;
  led_animation_orientation = 0;
  led_animation_breathe_cur = BREATHE_MIN_STEP;
  breathe_step = 1;
  breathe_dir = 1;
}

static void apply_blend(float* r, float* g, float* b, uint32_t effect, float applied_r, float applied_g, float applied_b) {
  uint32_t blend = effect & 0xffc00000;

  float temp_r;
  float temp_g;
  float temp_b;

  switch(blend) {
    case EF_NONE:
      if (*r == 0.0f && *g == 0.0f && *b == 0.0f) {
        *r = applied_r;
        *g = applied_g;
        *b = applied_b;
      }
      break;
    case EF_OVER:
      *r = applied_r;
      *g = applied_g;
      *b = applied_b;
      break;
    case EF_ADD:
      *r += applied_r;
      *g += applied_g;
      *b += applied_b;
      break;
    case EF_SUBTRACT:
      *r -= applied_r;
      *g -= applied_g;
      *b -= applied_b;
      break;
    case EF_MULTIPLY:
      *r = *r * applied_r / 255.0f;
      *g = *g * applied_g / 255.0f;
      *b = *b * applied_b / 255.0f;
      break;
    case EF_DIVIDE:
      *r = *r / applied_r * 255.0f;
      *g = *g / applied_g * 255.0f;
      *b = *b / applied_b * 255.0f;
      break;
    case EF_RBG:
      temp_g = *g;
      temp_b = *b;
      *g = temp_b;
      *b = temp_g;
      break;
    case EF_GRB:
      temp_r = *r;
      temp_g = *g;
      *r = temp_g;
      *g = temp_r;
      break;
    case EF_GBR:
      temp_r = *r;
      temp_g = *g;
      temp_b = *b;
      *r = temp_g;
      *g = temp_b;
      *b = temp_r;
      break;
    case EF_BRG:
      temp_r = *r;
      temp_g = *g;
      temp_b = *b;
      *r = temp_b;
      *g = temp_r;
      *b = temp_g;
      break;
    case EF_BGR:
      temp_r = *r;
      temp_b = *b;
      *r = temp_b;
      *b = temp_r;
      break;
  }
}

static void rgb_matrix_pattern(led_setup_t *f, uint8_t anim_id, float* ro, float* go, float* bo, issi3733_led_t *led) {
  float led_px = led->px;
  float led_py = led->py;
  float px;
  float py;

  while (f->end != 1)
  {
    // Reset px, py for the new frame
    px = led_px;
    py = led_py;

    bool is_x_axis = f->ef & (ef_axis_x | ef_axis_x_invert);
    bool is_x_axis_invert = f->ef & ef_axis_x_invert;
    bool is_y_axis = f->ef & (ef_axis_y | ef_axis_y_invert);
    bool is_y_axis_invert = f->ef & ef_axis_y_invert;

    if (f->ef & (EF_ANIM_SCROLL | EF_ANIM_SCROLL_INVERT)) {
      float offset;

      if (
        (led_animation_direction && (f->ef & EF_ANIM_SCROLL_INVERT)) || (!led_animation_direction && (f->ef & EF_ANIM_SCROLL))
      ) {
        offset = -animation_offsets[anim_id];
      } else {
        offset = animation_offsets[anim_id];
      }

      if (is_x_axis_invert) {
        px -= offset;
      } else if (is_x_axis) {
        px += offset;
      }

      if (is_y_axis_invert) {
        py -= offset;
      } else if (is_y_axis) {
        py += offset;
      }
    }

    if (is_x_axis_invert) {
      px = 100.0f - px;
    }

    if (is_y_axis_invert) {
      py = 100.0f - py;
    }

    float effect_pct = 0;

    // Calculate the px within the start-stop percentage for color blending
    if (is_x_axis && is_y_axis) {
      float pd = fmod(px + py + 200.0f, 200.0f) / 2.0f;
      if (pd < f->hs || pd > f->he) { f++; continue; }

      // Scrolled on both axes
      effect_pct = (pd - f->hs) / (f->he - f->hs);
    } else if (is_x_axis) {
      px = fmod(px + 100.0f, 100.0f);
      if (px < f->hs || px > f->he) { f++; continue; }

      // Scrolled horizontally
      effect_pct = (px - f->hs) / (f->he - f->hs);
    } else if (is_y_axis) {
      py = fmod(py + 100.0f, 100.0f);
      if (py < f->hs || py > f->he) { f++; continue; }

      // Scrolled vertically
      effect_pct = (py - f->hs) / (f->he - f->hs);
    } else if (f->ef & EF_ANIM_TIME) {
      float offset;

      if (!led_animation_direction) {
        offset = animation_offsets[anim_id];
      } else {
        offset = 100.0f - animation_offsets[anim_id];
      }

      if (offset < f->hs || offset > f->he) { f++; continue; }
      effect_pct = (offset - f->hs) / (f->he - f->hs);
    }

    float applied_r = (effect_pct * (f->re - f->rs)) + f->rs;
    float applied_g = (effect_pct * (f->ge - f->gs)) + f->gs;
    float applied_b = (effect_pct * (f->be - f->bs)) + f->bs;

    apply_blend(ro, go, bo, f->ef, applied_r, applied_g, applied_b);

    f++;
  }
}

void rgb_matrix_run_user(led_disp_t disp) {
  led_animation = (led_setup_t*) led_setups[led_animation_id];

  breathe_mult = 1;

  if (led_animation_breathing)
  {
    //+60us 119 LED
    led_animation_breathe_cur += breathe_step * breathe_dir;

    if (led_animation_breathe_cur >= BREATHE_MAX_STEP)
      breathe_dir = -1;
    else if (led_animation_breathe_cur <= BREATHE_MIN_STEP)
      breathe_dir = 1;

    //Brightness curve created for 256 steps, 0 - ~98%
    breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
    if (breathe_mult > 1) breathe_mult = 1;
    else if (breathe_mult < 0) breathe_mult = 0;
  }

  //Only needs to be calculated once per frame
  int anim_index;
  for (anim_index = 0; anim_index < led_setups_count; anim_index += 1) {
    led_setup_t *animation = led_setups[anim_index];
    uint32_t ms;

    if (animation->ms > 0) {
      ms = (uint32_t) animation->ms * led_animation_period_scalar;
    } else {
      ms = (uint32_t) DEFAULT_ANIM_PERIOD_MS * led_animation_period_scalar;
    }

    if (ms <= 0) {
      ms = 1;
    }

    float position_offset = (float) (disp.clk_ms % ms);

    // Scale offset to range 0-100
    animation_offsets[anim_index] = position_offset * 100.0f / ms;
  }

  if (led_animation_orientation) {
    ef_axis_x = EF_AXIS_Y;
    ef_axis_x_invert = EF_AXIS_Y_INVERT;
    ef_axis_y = EF_AXIS_X;
    ef_axis_y_invert = EF_AXIS_X_INVERT;
  } else {
    ef_axis_x = EF_AXIS_X;
    ef_axis_x_invert = EF_AXIS_X_INVERT;
    ef_axis_y = EF_AXIS_Y;
    ef_axis_y_invert = EF_AXIS_Y_INVERT;
  }

  highest_active_layer = 0;
  temp_layer_state = layer_state;

  while (temp_layer_state >> 1 != 0) {
      highest_active_layer++;
      temp_layer_state = temp_layer_state >> 1;
  }
}

void rgb_run(issi3733_led_t *led)
{
  float ro = 0;
  float go = 0;
  float bo = 0;

  if (led_lighting_mode == LED_MODE_KEYS_ONLY && led->scan == 255)
  {
    //Do not act on this LED
  }
  else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && led->scan != 255)
  {
    //Do not act on this LED
  }
  else if (led_lighting_mode == LED_MODE_INDICATORS_ONLY)
  {
    //Do not act on this LED (Only show indicators)
  }
  else
  {
    led_instruction_t *led_cur_instruction;
    led_cur_instruction = led_instructions;

    //Act on LED
    if (led_cur_instruction->end) {
      // If no instructions, use normal pattern
      rgb_matrix_pattern(led_animation, led_animation_id, &ro, &go, &bo, led);
    } else {
      uint8_t skip;
      uint8_t modid = (led->id - 1) / 32;                         //PS: Calculate which id# contains the led bit
      uint32_t modidbit = 1 << ((led->id - 1) % 32);              //PS: Calculate the bit within the id#
      uint32_t *bitfield;                                             //PS: Will point to the id# within the current instruction

      while (!led_cur_instruction->end) {
        skip = 0;

        //PS: Check layer active first
        if (led_cur_instruction->flags & LED_FLAG_MATCH_LAYER) {
          if (led_cur_instruction->layer != highest_active_layer) {
            skip = 1;
          }
        }

        if (!skip)
        {
          if (led_cur_instruction->flags & LED_FLAG_MATCH_ID) {
            bitfield = &led_cur_instruction->id0 + modid;       //PS: Add modid as offset to id0 address. *bitfield is now idX of the led id
            if (~(*bitfield) & modidbit) {                      //PS: Check if led bit is not set in idX
              skip = 1;
            }
          }
        }

        if (!skip) {
          if (led_cur_instruction->flags & LED_FLAG_USE_RGB) {
            ro = led_cur_instruction->r;
            go = led_cur_instruction->g;
            bo = led_cur_instruction->b;
          } else if (led_cur_instruction->flags & LED_FLAG_USE_PATTERN) {
            rgb_matrix_pattern(led_setups[led_cur_instruction->pattern_id], led_cur_instruction->pattern_id, &ro, &go, &bo, led);
          } else if (led_cur_instruction->flags & LED_FLAG_USE_ROTATE_PATTERN) {
            rgb_matrix_pattern(led_animation, led_animation_id, &ro, &go, &bo, led);
          } else if (led_cur_instruction->flags & LED_FLAG_USE_COLOR_MAP) {
            led_static_color_t static_color = static_color_map[led->id];
            apply_blend(&ro, &go, &bo, static_color.ef, (float) static_color.r, (float) static_color.g, (float) static_color.b);
          }
        }

        led_cur_instruction++;
      }
    }
  }

  //Clamp values 0-255
  if (ro > 255) ro = 255; else if (ro < 0) ro = 0;
  if (go > 255) go = 255; else if (go < 0) go = 0;
  if (bo > 255) bo = 255; else if (bo < 0) bo = 0;

  if (led_animation_breathing)
  {
    ro *= breathe_mult;
    go *= breathe_mult;
    bo *= breathe_mult;
  }

  *led->rgb.r = (uint8_t)ro;
  *led->rgb.g = (uint8_t)go;
  *led->rgb.b = (uint8_t)bo;





// TODO: Re-enable indicators





// #ifdef USB_LED_INDICATOR_ENABLE
//   if (keyboard_leds())
//   {
//       uint8_t kbled = keyboard_leds();
//       if (
//           #if USB_LED_NUM_LOCK_SCANCODE != 255
//           (led->scan == USB_LED_NUM_LOCK_SCANCODE && kbled & (1<<USB_LED_NUM_LOCK)) ||
//           #endif //NUM LOCK
//           #if USB_LED_CAPS_LOCK_SCANCODE != 255
//           (led->scan == USB_LED_CAPS_LOCK_SCANCODE && kbled & (1<<USB_LED_CAPS_LOCK)) ||
//           #endif //CAPS LOCK
//           #if USB_LED_SCROLL_LOCK_SCANCODE != 255
//           (led->scan == USB_LED_SCROLL_LOCK_SCANCODE && kbled & (1<<USB_LED_SCROLL_LOCK)) ||
//           #endif //SCROLL LOCK
//           #if USB_LED_COMPOSE_SCANCODE != 255
//           (led->scan == USB_LED_COMPOSE_SCANCODE && kbled & (1<<USB_LED_COMPOSE)) ||
//           #endif //COMPOSE
//           #if USB_LED_KANA_SCANCODE != 255
//           (led->scan == USB_LED_KANA_SCANCODE && kbled & (1<<USB_LED_KANA)) ||
//           #endif //KANA
//           (0))
//       {
//           if (*led->rgb.r > 127) *led->rgb.r = 0;
//           else *led->rgb.r = 255;
//           if (*led->rgb.g > 127) *led->rgb.g = 0;
//           else *led->rgb.g = 255;
//           if (*led->rgb.b > 127) *led->rgb.b = 0;
//           else *led->rgb.b = 255;
//       }
//   }
// #endif //USB_LED_INDICATOR_ENABLE
}
