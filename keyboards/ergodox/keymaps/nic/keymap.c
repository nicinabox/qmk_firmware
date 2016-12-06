#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define DEFAULT 0
#define LOWER 1
#define NUMPAD 2
#define NAV 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[DEFAULT] = KEYMAP(
  KC_EQUAL,           KC_1,     KC_2,     KC_3,     KC_4,   KC_5,   KC_ESCAPE,
  KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,   _______,
  KC_LCTL,            KC_A,     KC_S,     KC_D,     KC_F,   KC_G,
  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,   ALL_T(KC_GRAVE),
  KC_CAPSLOCK,        _______,  KC_LALT,  KC_LGUI,  MO(LOWER),

                                          KC_HOME,  KC_END,
                                                    KC_PGUP,
                              F(1),   KC_DELETE,   KC_PGDOWN,


    TG(NUMPAD),      KC_6,      KC_7,     KC_8,      KC_9,      KC_0,      KC_MINUS,
    _______,         KC_Y,      KC_U,     KC_I,      KC_O,      KC_P,      KC_BSLS,
                     KC_H,      KC_J,     KC_K,      KC_L,      KC_SCOLON, KC_QUOTE,
    MOD_MEH,         KC_N,      KC_M,     KC_COMMA,  KC_DOT,    KC_SLASH,  KC_LSHIFT,
                                F(0),     KC_LEFT,   KC_DOWN,    KC_UP,    KC_RIGHT,

    KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK,
    KC_AUDIO_VOL_UP,
    KC_AUDIO_VOL_DOWN,  KC_ENTER, F(2)
),

[LOWER] = KEYMAP(
  _______,          _______,  _______,  _______,  LGUI(LSFT(KC_4)), LGUI(LCTL(LSFT(KC_4))),  _______,
  LGUI(KC_BSPACE),  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,           KC_PERC,                 _______,
  _______,          _______,  _______,  _______,  _______,          KC_GRAVE,                _______,
  _______,          _______,  _______,  _______,  _______,          _______,
  _______,          _______,  _______,  _______,  _______,

                                                _______,  _______,
                                                          _______,
                                      _______,  _______,  _______,


  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
            _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_BSLS,
  _______,  _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_PIPE,
                      _______,  _______,  _______,  _______,  _______,

  _______, _______,
  _______,
  _______, _______, _______
),

[NUMPAD] = KEYMAP(
  _______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,

                        _______,  _______,
                                  _______,
                _______, _______, _______,

  _______,  _______,  _______,  KC_SLSH,  KC_ASTR,    _______,   _______,
  _______,  KC_UP,    KC_7,     KC_8,     KC_9,       KC_MINUS,  _______,
            KC_DOWN,  KC_4,     KC_5,     KC_6,       KC_PLUS,   _______,
  _______,  _______,  KC_1,     KC_2,     KC_3,       _______,   _______,
                      KC_0,     KC_0,     KC_DOT,     _______,   _______,

  _______, _______,
  _______,
  _______, _______, _______
),

[NAV] = KEYMAP(
  RESET,  _______,_______,_______,_______,_______,_______,
  M(0),   _______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,

                        _______,  _______,
                                  _______,
                _______, _______, _______,


  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,
            KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,

  KC_MPRV,_______,
  _______,
  KC_MUTE,_______,_______
),

};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_TAP_TOGGLE(NAV),

  // Tap for backspace, hold for LOWER
  [1] = ACTION_LAYER_TAP_KEY(LOWER, KC_BSPC),

  // Tap for space, hold for shift
  [2] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_SPC),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
      case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
    }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
