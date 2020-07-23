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

#pragma once

//Define number of IS31FL3733 drivers being used (1...16)
#define ISSI3733_DRIVER_COUNT 1
#define DRIVER_LED_TOTAL ISSI3733_LED_COUNT

//Hardware address of each driver (Refer to IS31FL3733 pdf "Table 1 Slave Address" and keyboard schematic)
#define ISSI3773_DRIVER_ADDRESSES { 0xA0 }

//LED I2C bus speed
#define I2C_HZ 580000

//Count of LED bodies
#define ISSI3733_LED_COUNT 35

#define LED_GCR_MAX                 165         //Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus
#define LED_GCR_STEP                10          //GCR increment/decrement value

#ifdef USE_MASSDROP_CONFIGURATOR
#define ANIMATION_SPEED_STEP        1

#define BREATHE_STEP                1
#define BREATHE_MIN_STEP            0
#define BREATHE_MAX_STEP            255
#endif

//Default Global Current Register value (Default brightness 0 - 255)
#define ISSI3733_GCR_DEFAULT LED_GCR_MAX

//Automatic power rollback and recovery
#define V5_HIGH                     2494        //5V high level = 4.75V (After low power detect, point at which LEDs are allowed to use more power )
#define V5_LOW                      2434        //5V low level = 4.634V (LED power rolled back to stay above this limit)
#define V5_CAT                      2206        //5V catastrophic level = 4.20V (Host USB port potential to shut down)

//LED Mapping - More practically generated from a spreadsheet program
//id: ID of the LED (Sync with PCB callouts)
//x: Physical X coordinate of LED (units do not matter)
//y: Physical Y coordinate of LED (units do not matter)
//drv: 1-Based index of ISSI3773_DRIVER_ADDRESSES
//cs: Matrix wiring CS col (1-9)
//swr: Matrix wiring SW Red row (1-12)
//swg: Matrix wiring SW Green row (1-12)
//swb: Matrix wiring SW Blue row (1-12)
//scan: Associated key matrix scancode (set 255 if none or 254 for LED to turn off in alternating mode)
//Note: Origin 0,0 may be located anywhere as the software will do the final layout
#define ISSI3733_LED_MAP { \
 { .id = 1,  .x = 0, 	.y = 0, 	 .adr = { .drv = 1, .cs = 2, .swr = 11, .swg = 10, .swb = 12 }, .scan = 0 }, \
 { .id = 2,  .x = 0.75, .y = 0, 	 .adr = { .drv = 1, .cs = 4, .swr = 11, .swg = 10, .swb = 12 }, .scan = 1 }, \
 { .id = 3,  .x = 1.5, 	.y = 0, 	 .adr = { .drv = 1, .cs = 5, .swr = 11, .swg = 10, .swb = 12 }, .scan = 2 }, \
 { .id = 4,  .x = 2.25, .y = 0, 	 .adr = { .drv = 1, .cs = 7, .swr = 11, .swg = 10, .swb = 12 }, .scan = 3 }, \
 { .id = 5,  .x = 0, 	.y = -1.125, .adr = { .drv = 1, .cs = 2, .swr = 8, .swg = 7, .swb = 9 }, .scan = 4 }, \
 { .id = 6,  .x = 0.75, .y = -1.125, .adr = { .drv = 1, .cs = 3, .swr = 8, .swg = 7, .swb = 9 }, .scan = 5 }, \
 { .id = 7,  .x = 1.5, 	.y = -1.125, .adr = { .drv = 1, .cs = 4, .swr = 8, .swg = 7, .swb = 9 }, .scan = 6 }, \
 { .id = 8,  .x = 2.25, .y = -1.125, .adr = { .drv = 1, .cs = 5, .swr = 8, .swg = 7, .swb = 9 }, .scan = 7 }, \
 { .id = 9,  .x = 0, 	.y = -1.875, .adr = { .drv = 1, .cs = 8, .swr = 8, .swg = 7, .swb = 9 }, .scan = 8 }, \
 { .id = 10, .x = 0.75, .y = -1.875, .adr = { .drv = 1, .cs = 7, .swr = 8, .swg = 7, .swb = 9 }, .scan = 9 }, \
 { .id = 11, .x = 1.5, 	.y = -1.875, .adr = { .drv = 1, .cs = 6, .swr = 8, .swg = 7, .swb = 9 }, .scan = 10 }, \
 { .id = 12, .x = 0,    .y = -2.625, .adr = { .drv = 1, .cs = 2, .swr = 5, .swg = 4, .swb = 6 }, .scan = 12 }, \
 { .id = 13, .x = 0.75, .y = -2.625, .adr = { .drv = 1, .cs = 3, .swr = 5, .swg = 4, .swb = 6 }, .scan = 13 }, \
 { .id = 14, .x = 1.50, .y = -2.625, .adr = { .drv = 1, .cs = 4, .swr = 5, .swg = 4, .swb = 6 }, .scan = 14 }, \
 { .id = 15, .x = 2.05, .y = -2.450, .adr = { .drv = 1, .cs = 5, .swr = 5, .swg = 4, .swb = 6 }, .scan = 15 }, \
 { .id = 16, .x = 0, 	.y = -3.375, .adr = { .drv = 1, .cs = 2, .swr = 2, .swg = 1, .swb = 3 }, .scan = 16 }, \
 { .id = 17, .x = 0.75, .y = -3.375, .adr = { .drv = 1, .cs = 3, .swr = 2, .swg = 1, .swb = 3 }, .scan = 17 }, \
 { .id = 18, .x = 1.50, .y = -3.375, .adr = { .drv = 1, .cs = 4, .swr = 2, .swg = 1, .swb = 3 }, .scan = 18 }, \
 { .id = 19, .x = 0.375,.y = -4.125, .adr = { .drv = 1, .cs = 6, .swr = 2, .swg = 1, .swb = 3 }, .scan = 20 }, \
 { .id = 20, .x = 1.5, 	.y = -4.125, .adr = { .drv = 1, .cs = 5, .swr = 2, .swg = 1, .swb = 3 }, .scan = 22 }, \
 { .id = 21, .x = 2.05, .y = -3.950, .adr = { .drv = 1, .cs = 8, .swr = 5, .swg = 4, .swb = 6 }, .scan = 23 }, \
 \
 { .id = 100, .x = -0.295,.y = 0.095,  .adr = { .drv = 1, .cs = 1, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 101, .x = 0.597, .y = 0.184,  .adr = { .drv = 1, .cs = 3, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 102, .x = 1.649, .y = 0.188,  .adr = { .drv = 1, .cs = 6, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 103, .x = 2.545, .y = 0.095,  .adr = { .drv = 1, .cs = 8, .swr = 11, .swg = 10, .swb = 12 }, .scan = 254 }, \
 { .id = 104, .x = 2.64,  .y = -1.05,  .adr = { .drv = 1, .cs = 9, .swr = 11, .swg = 10, .swb = 12 }, .scan = 255 }, \
 { .id = 105, .x = 2.635, .y = -2.235, .adr = { .drv = 1, .cs = 6, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 106, .x = 2.635, .y = -3.42,  .adr = { .drv = 1, .cs = 7, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 107, .x = 2.545, .y = -4.62,  .adr = { .drv = 1, .cs = 9, .swr = 5, .swg = 4, .swb = 6 }, .scan = 254 }, \
 { .id = 108, .x = 1.65,  .y = -4.71,  .adr = { .drv = 1, .cs = 9, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 109, .x = 0.6,   .y = -4.71,  .adr = { .drv = 1, .cs = 8, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 110, .x = -0.295,.y = -4.615, .adr = { .drv = 1, .cs = 7, .swr = 2, .swg = 1, .swb = 3 }, .scan = 255 }, \
 { .id = 111, .x = -0.39, .y = -3.42,  .adr = { .drv = 1, .cs = 1, .swr = 2, .swg = 1, .swb = 3 }, .scan = 254 }, \
 { .id = 112, .x = -0.39, .y = -2.235, .adr = { .drv = 1, .cs = 1, .swr = 5, .swg = 4, .swb = 6 }, .scan = 255 }, \
 { .id = 113, .x = -0.39, .y = -1.05,  .adr = { .drv = 1, .cs = 1, .swr = 8, .swg = 7, .swb = 9 }, .scan = 254 }  \
};


#define USB_LED_INDICATOR_ENABLE    //Comment out to disable indicator functionality
#ifdef USB_LED_INDICATOR_ENABLE     //Scan codes refer to actual key matrix codes, not KC_* (255 to disable)
    #define USB_LED_NUM_LOCK_SCANCODE       4
    //#define USB_LED_CAPS_LOCK_SCANCODE      255
    //#define USB_LED_SCROLL_LOCK_SCANCODE    255
    //#define USB_LED_COMPOSE_SCANCODE        255
    //#define USB_LED_KANA_SCANCODE           255
#endif //USB_LED_INDICATOR_ENABLE
