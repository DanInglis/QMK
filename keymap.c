/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NUMPAD
};


enum tap_dance_codes {
  TD_KILL,
  TD_SHIFT,
  TD_LARW, TD_RARW,
  TD_F1, TD_F2, TD_F3, TD_F4, TD_F5, TD_F6, TD_F7, TD_F8, TD_F9, TD_F0
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

int cur_dance (qk_tap_dance_state_t *state);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |NumPad|Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  TD(TD_F1), TD(TD_F2),  TD(TD_F3),  TD(TD_F4),  TD(TD_F5),  TD(TD_F6),  TD(TD_F7),  TD(TD_F8),  TD(TD_F9),  TD(TD_F0),  KC_BSPC,      \
  KC_TAB,  KC_Q,      KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,       \
  KC_ESC,  KC_A,      KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,      \
  KC_LSFT, KC_Z,      KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    TD(TD_SHIFT), \
  KC_LCTL, KC_LALT,   KC_LGUI,    NUMPAD,     LOWER,      KC_SPC,     KC_SPC,     RAISE,      TD(TD_LARW),KC_DOWN,    KC_UP,      TD(TD_RARW)   \
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  KC_DEL,  _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_DEL,  _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |   =  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | Kill |      |      |      |   0  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______,     _______, _______, _______, KC_7,    KC_8,     KC_9,   KC_MINS,  _______, \
  _______, _______, _______, _______,     _______, _______, _______, KC_4,    KC_5,     KC_6,   KC_PLUS,  _______,  \
  _______, _______, _______, _______,     _______, _______, _______, KC_1,    KC_2,     KC_3,   KC_EQL,   _______, \
  _______, _______, _______, TD(TD_KILL), _______, _______, _______, KC_0,    KC_COMM,  KC_DOT, KC_SLSH,  _______, \
  _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,  _______  \
)

};

//Tap Dance Functions
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap kill_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap shift_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap larw_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap rarw_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f1_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f2_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f3_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f4_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f5_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f6_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f7_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f8_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f9_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap f0_tap_state = {
  .is_press_action = true,
  .state = 0
};


void kill_finished (qk_tap_dance_state_t *state, void *user_data) {
  kill_tap_state.state = cur_dance(state);
  switch (kill_tap_state.state) {
    case SINGLE_TAP: SEND_STRING(SS_TAP(X_TAB) SS_TAP(X_TAB) "Kill Confirmed." SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_ENT));
                      wait_ms(2000);
                      SEND_STRING(SS_LSFT(SS_TAP(X_TAB)) SS_TAP(X_ENT));
                      break;
  }
}
void kill_reset (qk_tap_dance_state_t *state, void *user_data) {
  //switch (kill_tap_state.state) {}
  kill_tap_state.state = 0;
}

void shift_finished (qk_tap_dance_state_t *state, void *user_data) {
  shift_tap_state.state = cur_dance(state);
  switch (shift_tap_state.state) {
    case SINGLE_TAP: register_code(KC_ENT); break;
    case SINGLE_HOLD: register_code(KC_RSHIFT); break;
  }
}
void shift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (shift_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ENT); break;
    case SINGLE_HOLD: unregister_code(KC_RSHIFT); break;
  }
  shift_tap_state.state = 0;
}

void larw_finished (qk_tap_dance_state_t *state, void *user_data) {
  larw_tap_state.state = cur_dance(state);
  switch (larw_tap_state.state) {
    case SINGLE_TAP: register_code(KC_LEFT); break;
    case SINGLE_HOLD: register_code(KC_HOME); break;
    case DOUBLE_HOLD: SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_LEFT) SS_TAP(X_HOME) "Cached "); break;
  }
}
void larw_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (larw_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LEFT); break;
    case SINGLE_HOLD: unregister_code(KC_HOME); break;
  }
  larw_tap_state.state = 0;
}

void rarw_finished (qk_tap_dance_state_t *state, void *user_data) {
  rarw_tap_state.state = cur_dance(state);
  switch (rarw_tap_state.state) {
    case SINGLE_TAP: register_code(KC_RIGHT); break;
    case SINGLE_HOLD: register_code(KC_END); break;
  }
}
void rarw_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rarw_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_RIGHT); break;
    case SINGLE_HOLD: unregister_code(KC_END); break;
  }
  rarw_tap_state.state = 0;
}

void f1_finished (qk_tap_dance_state_t *state, void *user_data) {
  f1_tap_state.state = cur_dance(state);
  switch (f1_tap_state.state) {
    case SINGLE_TAP: register_code(KC_1); break;
    case SINGLE_HOLD: register_code(KC_F1); break;
  }
}
void f1_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f1_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_1); break;
    case SINGLE_HOLD: unregister_code(KC_F1); break;
  }
  f1_tap_state.state = 0;
}

void f2_finished (qk_tap_dance_state_t *state, void *user_data) {
  f2_tap_state.state = cur_dance(state);
  switch (f2_tap_state.state) {
    case SINGLE_TAP: register_code(KC_2); break;
    case SINGLE_HOLD: register_code(KC_F2); break;
  }
}
void f2_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f2_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_2); break;
    case SINGLE_HOLD: unregister_code(KC_F2); break;
  }
  f2_tap_state.state = 0;
}

void f3_finished (qk_tap_dance_state_t *state, void *user_data) {
  f3_tap_state.state = cur_dance(state);
  switch (f3_tap_state.state) {
    case SINGLE_TAP: register_code(KC_3); break;
    case SINGLE_HOLD: register_code(KC_F3); break;
  }
}
void f3_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f3_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_3); break;
    case SINGLE_HOLD: unregister_code(KC_F3); break;
  }
  f3_tap_state.state = 0;
}

void f4_finished (qk_tap_dance_state_t *state, void *user_data) {
  f4_tap_state.state = cur_dance(state);
  switch (f4_tap_state.state) {
    case SINGLE_TAP: register_code(KC_4); break;
    case SINGLE_HOLD: register_code(KC_F4); break;
  }
}
void f4_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f4_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_4); break;
    case SINGLE_HOLD: unregister_code(KC_F4); break;
  }
  f4_tap_state.state = 0;
}

void f5_finished (qk_tap_dance_state_t *state, void *user_data) {
  f5_tap_state.state = cur_dance(state);
  switch (f5_tap_state.state) {
    case SINGLE_TAP: register_code(KC_5); break;
    case SINGLE_HOLD: register_code(KC_F5); break;
  }
}
void f5_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f5_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_5); break;
    case SINGLE_HOLD: unregister_code(KC_F5); break;
  }
  f5_tap_state.state = 0;
}

void f6_finished (qk_tap_dance_state_t *state, void *user_data) {
  f6_tap_state.state = cur_dance(state);
  switch (f6_tap_state.state) {
    case SINGLE_TAP: register_code(KC_6); break;
    case SINGLE_HOLD: register_code(KC_F6); break;
  }
}
void f6_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f6_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_6); break;
    case SINGLE_HOLD: unregister_code(KC_F6); break;
  }
  f6_tap_state.state = 0;
}

void f7_finished (qk_tap_dance_state_t *state, void *user_data) {
  f7_tap_state.state = cur_dance(state);
  switch (f7_tap_state.state) {
    case SINGLE_TAP: register_code(KC_7); break;
    case SINGLE_HOLD: register_code(KC_F7); break;
  }
}
void f7_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f7_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_7); break;
    case SINGLE_HOLD: unregister_code(KC_F7); break;
  }
  f7_tap_state.state = 0;
}

void f8_finished (qk_tap_dance_state_t *state, void *user_data) {
  f8_tap_state.state = cur_dance(state);
  switch (f8_tap_state.state) {
    case SINGLE_TAP: register_code(KC_8); break;
    case SINGLE_HOLD: register_code(KC_F8); break;
  }
}
void f8_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f8_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_8); break;
    case SINGLE_HOLD: unregister_code(KC_F8); break;
  }
  f8_tap_state.state = 0;
}

void f9_finished (qk_tap_dance_state_t *state, void *user_data) {
  f9_tap_state.state = cur_dance(state);
  switch (f9_tap_state.state) {
    case SINGLE_TAP: register_code(KC_9); break;
    case SINGLE_HOLD: register_code(KC_F9); break;
  }
}
void f9_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f9_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_9); break;
    case SINGLE_HOLD: unregister_code(KC_F9); break;
  }
  f9_tap_state.state = 0;
}

void f0_finished (qk_tap_dance_state_t *state, void *user_data) {
  f0_tap_state.state = cur_dance(state);
  switch (f0_tap_state.state) {
    case SINGLE_TAP: register_code(KC_0); break;
    case SINGLE_HOLD: register_code(KC_F10); break;
  }
}
void f0_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f0_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_0); break;
    case SINGLE_HOLD: unregister_code(KC_F10); break;
  }
  f0_tap_state.state = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
  //[FUNC]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, func_finished, func_reset),
  [TD_KILL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kill_finished, kill_reset),
  [TD_SHIFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished, shift_reset),
  [TD_LARW]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, larw_finished, larw_reset),
  [TD_RARW]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rarw_finished, rarw_reset),
  [TD_F1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f1_finished, f1_reset),
  [TD_F2]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f2_finished, f2_reset),
  [TD_F3]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f3_finished, f3_reset),
  [TD_F4]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f4_finished, f4_reset),
  [TD_F5]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f5_finished, f5_reset),
  [TD_F6]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f6_finished, f6_reset),
  [TD_F7]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f7_finished, f7_reset),
  [TD_F8]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f8_finished, f8_reset),
  [TD_F9]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f9_finished, f9_reset),
  [TD_F0]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f0_finished, f0_reset)
};





bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case NUMPAD:
          if (record->event.pressed) {
            layer_on(_NUMPAD);
          } else {
            layer_off(_NUMPAD);
          }
          return false;
          break;
      }
    return true;
};
