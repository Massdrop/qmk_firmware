typedef struct led_setup_s {
  float hs;         //Band begin at percent
  float he;         //Band end at percent
  uint32_t ef;      //Animation and color effects
  uint32_t ms;      //Animation period in ms (only first instruction of pattern)
  uint8_t rs;       //Red start value
  uint8_t re;       //Red end value
  uint8_t gs;       //Green start value
  uint8_t ge;       //Green end value
  uint8_t bs;       //Blue start value
  uint8_t be;       //Blue end value
  uint8_t end;      //Set to signal end of the setup
} led_setup_t;

typedef struct led_instruction_s {
  uint32_t id0; // Bitwise id, IDs 0-31
  uint32_t id1; // Bitwise id, IDs 32-63
  uint32_t id2; // Bitwise id, IDs 64-95
  uint32_t id3; // Bitwise id, IDs 96-127
  uint16_t flags; // Bitfield for LED instructions
  uint8_t layer;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t pattern_id;
  uint8_t end;
} led_instruction_t;

// LED Blends and Animation Options
// - - - - - -
#define EF_NONE           0x00000000  // No effect

#define EF_AXIS_X         0x00000001  // Pattern start/end on horizontal axis
#define EF_AXIS_X_INVERT  0x00000002  // Invert axis
#define EF_AXIS_Y         0x00000004  // Pattern start/end on vertical axis
#define EF_AXIS_Y_INVERT  0x00000008  // Invert axis
// #define EF_AXIS_Z         0x00000010 // Man, like, who knows what the future holds?
// #define EF_AXIS_Z_INVERT  0x00000020 // Reversed

// Cannot be combined with EF_ANIM_TIME
#define EF_ANIM_SCROLL         0x00000040  // Animate scroll in axis direction
#define EF_ANIM_SCROLL_INVERT  0x00000080  // Animate scroll in opposite of axis direction

// Cannot be combined with EF_ANIM_SCROLL(_INVERT)
#define EF_ANIM_TIME    0x00000100  // Animate over time

// Blend effects are all mutually-exclusive. Keep these bits separated from
// non-blend effects because led_instructions.c does a crude bit mask and
// switch-case.
#define EF_OVER           0x00400000  // Overwrite any previous color information with new
#define EF_ADD            0x00800000  // Add color values
#define EF_SUBTRACT       0x01000000  // Subtract color values
#define EF_MULTIPLY       0x02000000  // Multiply color values
#define EF_DIVIDE         0x04000000  // Divide color values
#define EF_RBG            0x08000000  // RGB -> RBG
#define EF_GRB            0x10000000  // RGB -> GRB
#define EF_GBR            0x20000000  // RGB -> GBR
#define EF_BRG            0x40000000  // RGB -> BRG
#define EF_BGR            0x80000000  // RGB -> BGR
// - - - - - -

#define DEFAULT_ANIM_PERIOD_MS 2500

// LED Extra Instructions
#define LED_FLAG_NULL                0x00
#define LED_FLAG_MATCH_ID            0x01
#define LED_FLAG_MATCH_LAYER         0x02
#define LED_FLAG_USE_RGB             0x10
#define LED_FLAG_USE_PATTERN         0x20
#define LED_FLAG_USE_ROTATE_PATTERN  0x40
#define LED_FLAG_USE_COLOR_MAP       0x80

extern uint8_t led_animation_id;
extern float led_animation_period_scalar;
extern uint8_t led_lighting_mode;
extern uint8_t led_animation_direction;
extern uint8_t led_animation_orientation;
extern uint8_t led_animation_breathe_cur;
extern uint8_t breathe_dir;

extern led_instruction_t led_instructions[];
extern void *led_setups[];
extern const uint8_t led_setups_count;

extern uint32_t layer_state;
