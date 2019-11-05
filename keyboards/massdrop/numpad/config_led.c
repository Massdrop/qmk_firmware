#ifdef RGB_MATRIX_ENABLE
#include "numpad.h"

#include "led_matrix.h"
#include "rgb_matrix.h"
#include "config_led.h"

// This table can be almost-automatically derived from ISSI3733_LED_MAP that is
// defined in config_led.h

// scan in the following equations refers to the scan variable of ISSI3733_LED_MAP
//   col = (uint8_t)(scan / 8)
//   row = (uint8_t)(scan % 8)
//   
// You can calculate the (0-244, 0-64) x/y values from the x/y values defined in
// ISSI3733_LED_MAP with the following formula:
//   uint8_t rgb_x = ((ISSI3733_LED_MAP[i].x - MIN_X) / (MAX_X - MIN_X)) * 224;
//   uint8_t rgb_y = ((ISSI3733_LED_MAP[i].y - MIN_Y) / (MAX_Y - MIN_Y)) * 64; //TODO: 64 - this?
// Where the min/max vars are the minimum and maximum "bounds" of x/y values
// present in ISSI3733_LED_MAP
//
// The row/col values need to be manually tweaked though, compensating for the
// "empty" cells that are a product of larger keys
//
// There is a quick-and-dirty implementation of this under ledvis.html

led_config_t g_led_config = {
  {
    {   0,   1,   2,   3 },
    {   4,   5,   6,   7 },
	{   8,   9,  10,  NO_LED  },
	{  11,  12,  13,  14 },
    {  15,  16,  17,  NO_LED},
    {  18,  NO_LED, 19,  20 },
  },
  {
// Key Lights
	{ 28,  61 }, { 84,  61 }, { 139, 61 }, { 195, 61 },
	{ 28,  46 }, { 84,  46 }, { 139, 46 }, { 195, 46 },
	{ 28,  37 }, { 84,  37 }, { 139, 37 },
	{ 28,  27 }, { 84,  27 }, { 139, 27 }, { 180, 29 },
	{ 28,  17 }, { 84,  17 }, { 139, 17 },
	{ 56,  7  }, { 139, 7  }, { 180, 9  },
// Underglow LEDs
	{ 7,   62 }, { 72,  63 }, { 150, 64 },
	{ 216, 62 }, { 224, 47 }, { 223, 32 }, { 223, 16 },
	{ 216, 1  }, { 150, 0  }, { 73,  0  },
	{ 7,   1  }, { 0,   16 }, { 0,   32 }, { 0,   47 }
  },
  {
// Key Lights (21) - LED_FLAG_KEYLIGHT, LED_FLAG_MODIFIER
    4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
// Underglow/border LEDs (14) - LED_FLAG_UNDERGLOW
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
  }
};


#ifdef USB_LED_INDICATOR_ENABLE
void rgb_matrix_indicators_kb(void)
{
	led_matrix_indicators();
}
#endif // USB_LED_INDICATOR_ENABLE

#endif
