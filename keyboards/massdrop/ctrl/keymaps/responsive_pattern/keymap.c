#include QMK_KEYBOARD_H

#include <math.h>

enum ctrl_keycodes {
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

    L_SP_PR,            //LED Splash Pattern Select Previous
    L_SP_NE,            //LED Splash Pattern Select Next

    L_SP_WD,            //LED Splash Widen Wavefront width
    L_SP_NW,            //LED Splash Narrow Wavefront width

    L_SP_FA,            //LED Splash wave travel speed faster (shorter period)
    L_SP_SL,            //LED Splash wave travel speed slower (longer period)

    L_CP_PR,            //LED Color Pattern Select Previous
    L_CP_NX,            //LEB Color Pattern Select Next

};


#if ISSI3733_LED_COUNT == 119
#   define NUMBER_OF_KEYS 87
#elif ISSI3733_LED_COUNT == 105
#   define NUMBER_OF_KEYS 67
#endif


#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_MUTE, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_MPLY, KC_MSTP, KC_VOLU, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   KC_TRNS, KC_TRNS, KC_TRNS, U_T_AUTO,U_T_AGCR,KC_TRNS, MO(2),   KC_TRNS, KC_TRNS, KC_TRNS,   KC_MPRV, KC_MNXT, KC_VOLD, \
        L_T_PTD, L_PTP,   L_BRD,   L_PTN,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, L_T_MD,  L_T_ONF, KC_TRNS, KC_TRNS, MD_BOOT, TG_NKRO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS \
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
        L_CP_NX, L_SP_SL, L_SP_WD, L_SP_FA, KC_TRNS, KC_TRNS, L_CP_NX, L_SP_SL, L_SP_WD, L_SP_FA, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
        L_CP_PR, L_SP_PR, L_SP_NW, L_SP_NE, KC_TRNS, KC_TRNS, L_CP_PR, L_SP_PR, L_SP_NW, L_SP_NE, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG_NKRO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS \
    ),
    /*
    [X] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG_NKRO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS \
    ),
    */
};

typedef uint8_t _ub;

#define COLOR_PATTERN_RGB_COUNT 18
_ub COLOR_PATTERNS[][COLOR_PATTERN_RGB_COUNT][3] = {
    { // default rainbow color
        {255,   0,   0}, {255,   0,   0}, {255, 127,   0},
        {255, 127,   0}, {255, 255,   0}, {255, 255,   0},
        {120, 255,   0}, {120, 255,   0}, {  0, 255,   0},
        {  0, 255,   0}, {  0, 255, 120}, {  0, 255, 120},
        {  0,   0, 255}, {  0,   0, 255}, { 75,   0, 130},
        { 75,   0, 130}, { 43,   0, 130}, { 43,   0, 130},
    }, { // light rainbow color
        {248,  12,  18}, {238,  17,   0}, {255,  51,  17},
        {255,  68,  32}, {255, 102,  68}, {255, 153,  51},
        {254, 174,  45}, {204, 187,  51}, {208, 195,  16},
        {170, 204,  34}, {105, 208,  37}, { 34, 204, 170},
        { 18, 189, 185}, { 17, 170, 187}, { 68,  68, 221},
        { 51,  17, 187}, { 59,  12, 189}, { 68,  34, 153},
    }, { // white flat
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
        {255, 255, 255}, {255, 255, 255}, {255, 255, 255},
    }, { // white fade, cos curve
        {255, 255, 255}, {255, 255, 255}, {252, 252, 252},
        {247, 247, 247}, {240, 240, 240}, {232, 232, 232},
        {221, 221, 221}, {209, 209, 209}, {196, 196, 196},
        {181, 181, 181}, {164, 164, 164}, {147, 147, 147},
        {128, 128, 128}, {108, 108, 108}, { 88,  88,  88},
        { 66,  66,  66}, { 45,  45,  45}, { 23,  23,  23},
    }, 
};
const _ub COLOR_PATTERNS_COUNT = sizeof(COLOR_PATTERNS) / sizeof(COLOR_PATTERNS[0]);


#define LED_NUMBERS (NUMBER_OF_KEYS + 1)


/*
configuration struct for splash effect

DRIPPLE_PATTERN: (0 ~ 5)
    - 0: None
    - 1: background off, wave on
    - 2: background on, wave off
    - 3: rainbow wave
    - 4: rainbow wave on rotation background
    - 5: activate on press then diminish

*/
struct{
    _ub DRIPPLE_PATTERN;
    _ub WAVE_FRONT_WIDTH;
    int WAVE_PERIOD;
    _ub COLOR_PATTERN_INDEX;
    _ub TRAVEL_DISTANCE;

} USER_CONFIG = { // this default setting is most appealing
    .DRIPPLE_PATTERN = 2,
    .WAVE_FRONT_WIDTH = 3,
    .WAVE_PERIOD = 50,
    .COLOR_PATTERN_INDEX = 0,
    .TRAVEL_DISTANCE = 20,
};

#define KEY_STROKES_LENGTH 10
struct {
    _ub alive;
    _ub led_id;
    uint32_t time;
} KEY_STROKES[KEY_STROKES_LENGTH] = {{}};

/*

definitions of led_instruction is in /tmk_core/protocol/arm_atsam/led_matrix.h
definitions of value of KC_* is in /tmk_core/common/keycode.h

*/
#define INDICATOR_INSTRUCTION( \
        offset, layer, id0, id1, id2, id3, r, g, b \
) [LED_NUMBERS + offset] = { \
    LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
    id0, id1, id2, id3, layer, r, g, b, 0, 0 \
}

#define INDICATORS_GROUP_NUMBER 21
led_instruction_t led_instructions[LED_NUMBERS + INDICATORS_GROUP_NUMBER + 1] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN,
            .id2 = 4286578688, .id3 = 1073741823}, // underglow
    // the flags and ids will be calculated in matrix_init_user()

    // INDICATOR_INSTRUCTION(0,  2, 4294967295, 4294967295, 16777215, 0, 0, 0, 0),
    INDICATOR_INSTRUCTION(1,  2, 0, 130, 0, 0,          255,  15,  15), // KC_TAB, KC_Y
    INDICATOR_INSTRUCTION(2,  2, 0, 260, 0, 0,          238, 127,  15), // QU
    INDICATOR_INSTRUCTION(3,  2, 0, 520, 0, 0,          255, 255,  15), // WI
    INDICATOR_INSTRUCTION(4,  2, 0, 1040, 0, 0,         127, 255,   0), // EO
    INDICATOR_INSTRUCTION(5,  2, 0, 17039360, 0, 0,       0, 255,   0), // KC_CAPS, KC_H
    INDICATOR_INSTRUCTION(6,  2, 0, 34078720, 0, 0,       0, 255, 120), // AJ
    INDICATOR_INSTRUCTION(7,  2, 0, 68157440, 0, 0,       0,   0, 255), // SK
    INDICATOR_INSTRUCTION(8,  2, 0, 136314880, 0, 0,     75,   0, 255), // DL
#define PATTERN_INDICATOR_OFFSET 9
    INDICATOR_INSTRUCTION(9,  2, 8323072, 0, 0, 0,      255, 255,   0), // KC_GRV, 123456,
#define ACTIVE_PATTERN_INDICATOR_OFFSET 10
    INDICATOR_INSTRUCTION(10, 2, 262144, 0, 0, 0,       255,   0,   0), // active pattern

#define COLOR_PATTERN_INSTRUCTION_OFFSET 11
    INDICATOR_INSTRUCTION(11, 2, 0, 0, 1, 0,            255, 255,   0), // Z
    INDICATOR_INSTRUCTION(12, 2, 0, 0, 2, 0,            255, 255,   0), // X
    INDICATOR_INSTRUCTION(13, 2, 0, 0, 4, 0,            255, 255,   0), // C
    INDICATOR_INSTRUCTION(14, 2, 0, 0, 8, 0,            255, 255,   0), // V
    INDICATOR_INSTRUCTION(15, 2, 0, 0, 16, 0,           255, 255,   0), // B
    INDICATOR_INSTRUCTION(16, 2, 0, 0, 32, 0,           255, 255,   0), // N
    INDICATOR_INSTRUCTION(17, 2, 0, 0, 64, 0,           255, 255,   0), // M
    INDICATOR_INSTRUCTION(18, 2, 0, 0, 128, 0,          255, 255,   0), // KC_COMMA
    INDICATOR_INSTRUCTION(19, 2, 0, 0, 256, 0,          255, 255,   0), // KC_DOT
#define COLOR_PATTERN_INSTRUCTION_END 19


    INDICATOR_INSTRUCTION(20, 1, 0, 3672092, 0, 0,      255,   0,   0), // QWE ASD P
    
    INDICATOR_INSTRUCTION(21, 1, 0, 3672092, 0, 0,      255, 255,   0), // QWE ASD P

};


const uint16_t PROGMEM fn_actions[] = {};

_ub KEYCODE_TO_LED_ID[256];
_ub DISTANCE_MAP[LED_NUMBERS][LED_NUMBERS];

_ub ktli(uint16_t keycode){

    if(keycode < 256){
        // the array is initialized in `matrix_init_user()`
        return KEYCODE_TO_LED_ID[keycode];
    }

    switch(keycode){
    case 20737: return 82;
    }

    return 0;
};





void add_led_instructions_id(uint16_t instruction_index, uint32_t id){
    uint16_t i = instruction_index;
    switch((id-1) / 32){
    case 0: led_instructions[i].id0 |= 1 << ((id-1) % 32); break;
    case 1: led_instructions[i].id1 |= 1 << ((id-1) % 32); break;
    case 2: led_instructions[i].id2 |= 1 << ((id-1) % 32); break;
    case 3: led_instructions[i].id3 |= 1 << ((id-1) % 32); break;
    }
}
void set_led_instructions_id(uint16_t instruction_index, uint32_t id){
    uint16_t i = instruction_index;
    led_instructions[i].id0 = 0;
    led_instructions[i].id1 = 0;
    led_instructions[i].id2 = 0;
    led_instructions[i].id3 = 0;
    add_led_instructions_id(i, id);
}
void refresh_color_pattern_indicator(void){
    _ub count = COLOR_PATTERN_INSTRUCTION_END - COLOR_PATTERN_INSTRUCTION_OFFSET + 1;
    _ub (*pattern_in_use)[3] = &COLOR_PATTERNS[USER_CONFIG.COLOR_PATTERN_INDEX][0];
    _ub step = COLOR_PATTERN_RGB_COUNT / count;
    uint16_t begin = LED_NUMBERS + COLOR_PATTERN_INSTRUCTION_OFFSET;
    for(_ub i = 0; i < count; ++i){
        led_instructions[begin + i].r = pattern_in_use[i * step][0];
        led_instructions[begin + i].g = pattern_in_use[i * step][1];
        led_instructions[begin + i].b = pattern_in_use[i * step][2];
    }
}



void init_keycode_to_led_map(void){
    uint16_t LED_MAP[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
            36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,
            52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,
#if NUMBER_OF_KEYS >= 87
            68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87
#endif
    );

    uint16_t key = 0;
    for(_ub y = 0; y < MATRIX_ROWS; ++y){
        for(_ub x = 0; x < MATRIX_COLS; ++x){
            key = keymaps[0][y][x];
            if(key < 256){
                KEYCODE_TO_LED_ID[key] = LED_MAP[y][x];
            }
        }
    }
}
#define KPM_HEIGHT 6
#define KPM_WIDTH 20
void init_distance_map(void){
    // proportional to the real keyboard
    unsigned short KEY_POSITION_MAP[KPM_HEIGHT][KPM_WIDTH] = {
        { KC_NO,   KC_ESC,  KC_NO,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_NO,  KC_F5,  KC_F6,   KC_F7,  KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS,  },
        // { KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    },
        { KC_NO,   KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, KC_BSPC, KC_NO,   KC_INS,  KC_HOME, KC_PGUP,  },
        { KC_NO,   KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, KC_BSLS, KC_NO,   KC_DEL,  KC_END,  KC_PGDN,  },
        { KC_NO,   KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,  KC_ENT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,    },
        { KC_NO,   KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,  KC_RSFT, KC_RSFT, KC_RSFT, KC_NO,   KC_NO,   KC_UP,   KC_NO,    },
        { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_NO,  20737,   KC_APP,   KC_RCTL, KC_RCTL, KC_RCTL, KC_NO,   KC_LEFT, KC_DOWN, KC_RIGHT, },
    };

    /*
    complexity of the below implementation ~O(n^2), n = number of keys
    */
    _ub x = 0, y = 0;
    // _ub raw_distance_map[LED_NUMBERS][LED_NUMBERS];
    while(x < KPM_WIDTH && y < KPM_HEIGHT){
        _ub sl = ktli(KEY_POSITION_MAP[y][x]); // source led
        for(_ub i = 0; i < KPM_WIDTH; ++i){
            for(_ub j = 0; j < KPM_HEIGHT; ++j){
                _ub tl = ktli(KEY_POSITION_MAP[j][i]); // target led
                if(sl == tl) continue;
                
                _ub dx = abs(i - x), dy = abs(j - y);

                _ub dis = dx + dy;
                if(i < x && j > y){ // core algorithm
                    dis -= dx < dy ? dx : dy; // min(dx, dy)
                }
                _ub _dis = DISTANCE_MAP[sl][tl];
                
                if(_dis && _dis <= dis) continue;

                DISTANCE_MAP[sl][tl] = dis;
                DISTANCE_MAP[tl][sl] = dis;
            }
        }
        if(x < KPM_WIDTH-1){
            ++x;
        } else{ // start next row iteration
            x = 0;
            ++y;
        }
    }
}
void init_led_instructions(void){
    /*
    suppose to iterate 87 times for a 87 keys keyboard
    as there are 87 led_structions with LED_FLAG_MATCH_ID
    which is suppose to be one key only

    so the led on each of the key can be modified by accessing the
    corresponding led_instruction[ktli(keycode)]:
    # see ktli(keycode) definition above
    */
    uint16_t flag = LED_FLAG_MATCH_ID;
    if(( USER_CONFIG.DRIPPLE_PATTERN == 2 ) || (
            USER_CONFIG.DRIPPLE_PATTERN == 4)){
        flag |= LED_FLAG_USE_ROTATE_PATTERN;
    } else{
        flag |= LED_FLAG_USE_RGB;
    }
    for(int i = 1; i < LED_NUMBERS; ++i){
        led_instructions[i].flags = flag;
        set_led_instructions_id(i, i);
    }

    led_instructions[LED_NUMBERS + INDICATORS_GROUP_NUMBER].end = 1;
    refresh_color_pattern_indicator();
}


void matrix_init_user(void) {
    init_keycode_to_led_map();
    init_distance_map(); // must be placed after keycode_to_led
    init_led_instructions();
    led_animation_speed += ANIMATION_SPEED_STEP * 15;
}; // end of matrix_init_user(), initialization function


/*
length of the array should be a safe, large enough value
more typically:
longest wave time * fastest typing speed
= 22 * WAVE_PREIOD * typing speed
*/


/*
Runs constantly in the background, in a loop.
https://beta.docs.qmk.fm/detailed-guides/custom_quantum_functions#matrix-scanning-code
*/
// uint32_t perf_timer[100] = {1};
void matrix_scan_user(void) {
    // perf_timer[perf_timer[0]] = timer_read32();
    // keyboard_leds()
    _ub wave_front[LED_NUMBERS] = {};
    for(int i = 0; i < KEY_STROKES_LENGTH; ++i){
        if(KEY_STROKES[i].alive){
            uint32_t e = timer_elapsed32(KEY_STROKES[i].time);
            _ub alive = 0;
            _ub l = KEY_STROKES[i].led_id;
            int period_passed = e / USER_CONFIG.WAVE_PERIOD;

            unsigned short dp;
            for(int j = 1 ; j < LED_NUMBERS; ++j){
                dp = period_passed - DISTANCE_MAP[l][j];
                // In virtue, dp should be larger than or equal to 0
                // but dp is unsigned so never mind......
                if(( dp < USER_CONFIG.WAVE_FRONT_WIDTH ) && (
                        DISTANCE_MAP[l][j] <= USER_CONFIG.TRAVEL_DISTANCE)){
                    switch(USER_CONFIG.DRIPPLE_PATTERN){
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        wave_front[j] += dp;
                        break;
                    default:
                        wave_front[j] = 1;
                        break;
                    }
                    alive = 1;
                }
            }
            
            // if it's never set in the loop, it would be zero
            KEY_STROKES[i].alive = alive;
        }
    }


    // enum failed
    #define USE_PATTERN 0
    #define BLACK_RGB 1
    #define COLOR_RGB 2
    uint16_t flag_rgb = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB;
    uint16_t flag_pattern = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN;
    for(int i = 1; i < LED_NUMBERS; ++i){
        _ub handle_type = USE_PATTERN, c = 0;
        switch(USER_CONFIG.DRIPPLE_PATTERN){
        case 0:
            handle_type = USE_PATTERN;
            break;
        case 1:
            if(wave_front[i]){
                handle_type = USE_PATTERN;
            } else{
                handle_type = BLACK_RGB;
            }
            break;
        case 2:
            if(wave_front[i]){
                handle_type = BLACK_RGB;
            } else{
                handle_type = USE_PATTERN;
            }
            break;
        case 3:
        case 4:
            if(wave_front[i]){
                handle_type = COLOR_RGB;
            } else if(USER_CONFIG.DRIPPLE_PATTERN == 4){
                handle_type = USE_PATTERN;
            } else{
                handle_type = BLACK_RGB;
            }
            break;
        case 5:
        case 6:
            if(wave_front[i]){
                handle_type = COLOR_RGB;
            } else{
                handle_type = USE_PATTERN;
            }
            break;
        }

        switch(handle_type){
        case USE_PATTERN:
            led_instructions[i].flags = flag_pattern;
            break;
        case BLACK_RGB:
            led_instructions[i].r = 0;
            led_instructions[i].g = 0;
            led_instructions[i].b = 0;
            led_instructions[i].flags = flag_rgb;
            break;
        case COLOR_RGB:
            c = (wave_front[i] * COLOR_PATTERN_RGB_COUNT /
                    USER_CONFIG.WAVE_FRONT_WIDTH) % COLOR_PATTERN_RGB_COUNT;
            _ub *arr = &COLOR_PATTERNS[USER_CONFIG.COLOR_PATTERN_INDEX][c][0];
            led_instructions[i].r = arr[0];
            led_instructions[i].g = arr[1];
            led_instructions[i].b = arr[2];
            led_instructions[i].flags = flag_rgb;
            break;
        }
    }

}; // end of matrix_scan_user (looping function)


#define MODS_SHIFT  (keyboard_report->mods & MOD_BIT(KC_LSHIFT) || keyboard_report->mods & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (keyboard_report->mods & MOD_BIT(KC_LCTL) || keyboard_report->mods & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (keyboard_report->mods & MOD_BIT(KC_LALT) || keyboard_report->mods & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
            }
            return false;
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







        
        case L_SP_PR: // previous dripple pattern
        case L_SP_NE: // next dripple pattern
            if (record->event.pressed) {
                

#define PATTERN_COUNT 7
                _ub incre = keycode == L_SP_PR ? PATTERN_COUNT-1 : 1;
                USER_CONFIG.DRIPPLE_PATTERN += incre;
                USER_CONFIG.DRIPPLE_PATTERN %= PATTERN_COUNT;

                if(USER_CONFIG.DRIPPLE_PATTERN <= 4){
                    USER_CONFIG.TRAVEL_DISTANCE = 20;
                    USER_CONFIG.COLOR_PATTERN_INDEX = 0;
                    USER_CONFIG.WAVE_PERIOD = 50;
                }

                _ub indicator_key = 0;
                switch(USER_CONFIG.DRIPPLE_PATTERN){
                case 0: // None
                    indicator_key = KC_GRV;
                    break;
                case 1: // background off, wave on
                    indicator_key = KC_1;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 2;
                    break;
                case 2: // background on, wave off
                    indicator_key = KC_2;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 5;
                    break;
                case 3: // background off, rainbow wave
                    indicator_key = KC_3;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;
                    break;
                case 4: // background on, rainbow wave
                    indicator_key = KC_4;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;
                    break;
                case 5:
                    indicator_key = KC_5;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;

                    USER_CONFIG.COLOR_PATTERN_INDEX = 2;
                    USER_CONFIG.TRAVEL_DISTANCE = 0;
                    USER_CONFIG.WAVE_PERIOD = 100;
                    break;
                case 6:
                    indicator_key = KC_6;
                    USER_CONFIG.WAVE_FRONT_WIDTH = 25;

                    USER_CONFIG.COLOR_PATTERN_INDEX = 3;
                    USER_CONFIG.TRAVEL_DISTANCE = 2;
                    USER_CONFIG.WAVE_PERIOD = 10;
                    break;
                }

                set_led_instructions_id(
                        LED_NUMBERS + ACTIVE_PATTERN_INDICATOR_OFFSET,
                        ktli(indicator_key));
                refresh_color_pattern_indicator();
                

                // remove effect after changing pattern
                for(int i = 0; i < KEY_STROKES_LENGTH; ++i){
                    KEY_STROKES[i].alive = 0;
                }

            }
            return false;
        case L_SP_WD:
        case L_SP_NW:
            if(record->event.pressed){
                short incre = keycode == L_SP_WD ? 1 : -1;
                USER_CONFIG.WAVE_FRONT_WIDTH += incre;
                if(USER_CONFIG.WAVE_FRONT_WIDTH < 1){
                    USER_CONFIG.WAVE_FRONT_WIDTH = 1;
                }
            }
            return false;
        case L_SP_FA:
        case L_SP_SL:
            if(record->event.pressed){
                short incre = keycode == L_SP_FA ? -1 : 1;
                
                USER_CONFIG.WAVE_PERIOD += 10 * incre;
                if(USER_CONFIG.WAVE_PERIOD < 10){
                    USER_CONFIG.WAVE_PERIOD = 10;
                }
            }
            return false;
        // these are the keys not in range 0x04 - 0x52
        case L_CP_PR:
        case L_CP_NX:
            if(record->event.pressed){
                _ub incre = keycode == L_CP_PR ? COLOR_PATTERNS_COUNT - 1 : 1;
                USER_CONFIG.COLOR_PATTERN_INDEX += incre;
                USER_CONFIG.COLOR_PATTERN_INDEX %= COLOR_PATTERNS_COUNT;
                refresh_color_pattern_indicator();
            }
            return false;
        default:
            /*
            for reference to key code value, see:
            /tmk_core/common/keycode.h(195): enum hid_keyboard_keypad_usage
            */

            if (record->event.pressed){
                _ub led_id = ktli(keycode);
                if(led_id){
                    for(int i = 0; i < KEY_STROKES_LENGTH; ++i){
                        if(!KEY_STROKES[i].alive){
                            KEY_STROKES[i].alive = 1;
                            KEY_STROKES[i].led_id = led_id;
                            KEY_STROKES[i].time = timer_read32();
                            break;
                        }
                    }
                }
            }
            return true; //Process all other keycodes normally
    }
}
