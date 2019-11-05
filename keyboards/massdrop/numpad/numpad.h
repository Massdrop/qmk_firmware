#pragma once

#include "quantum.h"
#include "config_led.h"
#include "matrix.h"

#include "i2c_master.h"
#include "led_matrix.h" //For led keycodes
#include "usb/udi_cdc.h"
#include "usb/usb2422.h"	// For usb_gcr_auto only

// Updated -PS082019
#define LAYOUT( \
    K001, K002, K003, K004, \
	K005, K006, K007, K008,  \
	K009, K010, K011, \
	K012, K013, K014, K015, \
    K016, K017, K018, \
	K019, K020, K021  \
) { \
    {   K001,  K002,  K003,  K004	}, \
	{   K005,  K006,  K007,  K008	}, \
	{	K009,  K010,  K011,  KC_NO  }, \
    {   K012,  K013,  K014,  K015	}, \
	{   K016,  K017,  K018,  KC_NO	}, \
	{   K019,  KC_NO, K020,  K021	}  \
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
