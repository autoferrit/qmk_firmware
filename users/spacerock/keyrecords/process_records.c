
#include "spacerock.h"
#include "version.h"
// #include "features/callum.h"
#include "features/swapper.h"
#include "os_detection.h"

#ifdef FEATURE_SENTENCE_CASE_ENABLE
    #include "features/sentence_case.h"
#endif

#ifdef HAPTIC_ENABLE
    #include "drivers/haptic/drv2605l.h"
#endif //HAPTIC ENABLE

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#ifdef FEATURE_SWAPPER_ENABLE
    bool sw_win_active = false;
    bool sw_lang_active = false;
#endif

#ifdef FEATURE_CALLUM_ENABLE
    oneshot_state os_shft_state = os_up_unqueued;
    oneshot_state os_ctrl_state = os_up_unqueued;
    oneshot_state os_alt_state = os_up_unqueued;
    oneshot_state os_cmd_state = os_up_unqueued;
#endif

/**
 * @brief Main user keycode handler
 *
 * This handles all of the keycodes for the user, including calling feature handlers.
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord_t data structure
 * @return true Continue processing keycode and send to host
 * @return false Stop process keycode and do not send to host
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// ┌───────────────────────────────────────────────────────────┐
// │ f e a t u r e s                                           │
// └───────────────────────────────────────────────────────────┘

    //
    // Repeat
    // this needs to be the first check for keycodes unless achordion is used then
    // that should be first
    #ifdef FEATURE_REPEAT_KEY_ENABLE
        if (!process_repeat_key_with_alt(keycode, record, REPEAT, ALTREP)) {
            return false;
        }
    #endif

    //
    // Deactivte NAV layer if a non nav key is pressed
    if (get_highest_layer(layer_state | default_layer_state) == _NAV) {
        if (record->event.pressed) {
            // if one of the keys below is not pressed then disable _NAV
            switch (keycode) {
                case LY_ADJ:
                // navs
                case KC_PGUP:
                case KC_PGDN:
                case KC_LEFT:
                case KC_RIGHT:
                case KC_DOWN:
                case KC_UP:
                case M_LEFT:
                case M_RIGHT:
                case M_DOWN:
                case M_UP:
                // nums
                case KC_ASTR:
                case KC_SLSH:
                case KC_0:
                case KC_1:
                case KC_2:
                case KC_3:
                case KC_4:
                case KC_5:
                case KC_6:
                case KC_7:
                case KC_8:
                case KC_9:
                case KC_PLUS:
                case KC_MINS:
                case KC_DOT:
                    return true;
                default:
                    layer_off(_NAV);
                    return true;
            }
        }
    }

    //
    // Swapper
    switch (detected_host_os()) {
        case OS_MACOS:
            update_swapper(
                &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
                keycode, record
            );
            break;
        default:
            update_swapper(
                &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
                keycode, record
            );
            break;
    }

    //
    // Callum
    #ifdef FEATURE_CALLUM_ENABLE
        update_oneshot(
            &os_shft_state, KC_LSFT, OS_LSFT,
            keycode, record
        );
        update_oneshot(
            &os_shft_state, KC_RSFT, OS_RSFT,
            keycode, record
        );
        update_oneshot(
            &os_ctrl_state, KC_LCTL, OS_CTRL,
            keycode, record
        );
        update_oneshot(
            &os_alt_state, KC_LALT, OS_ALT,
            keycode, record
        );
        update_oneshot(
            &os_cmd_state, KC_LGUI, OS_CMD,
            keycode, record
        );
        //break;
    #endif

    //
    // Sentence Case
    #ifdef FEATURE_SENTENCE_CASE_ENABLE
        if (!process_sentence_case(keycode, record)) { return false; }
    #endif

    switch (keycode) {

// ┌───────────────────────────────────────────────────────────┐
// │ l a y e r                                                 │
// └───────────────────────────────────────────────────────────┘
        case TG_DEF:
            if (record->event.pressed) {
                layer_clear();
                if (IS_LAYER_ON(_GAME)) {
                    set_single_persistent_default_layer(_COLEMAK);
                    layer_move(_COLEMAK);
                } else {
                    set_single_persistent_default_layer(_GAME);
                    layer_move(_GAME);
                }
                #ifdef HAPTIC_ENABLE
                  drv2605l_pulse(transition_hum);
                #endif // HAPTIC_ENABLE
            }
            return false;
        case LY_DEF:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_GAME)) {
                    layer_clear();
                    layer_move(_GAME);
                } else {
                    layer_clear();
                    layer_move(_COLEMAK);
                }
                #ifdef HAPTIC_ENABLE
                  drv2605l_pulse(transition_hum);
                #endif // HAPTIC_ENABLE
            }
            return false;

// ┌───────────────────────────────────────────────────────────┐
// │ q m k                                                     │
// └───────────────────────────────────────────────────────────┘

        case MAKE_H:
            if (record->event.pressed) {
                #ifdef KEYBOARD_klor_2040
                    SEND_STRING ("qmk compile -kb klor/2040 -km spacerock");
                    tap_code(KC_ENTER);
                #endif
                #ifdef KEYBOARD_splitkb_kyria_rev3
                    SEND_STRING ("qmk compile -kb splitkb/kyria/rev3 -km spacerock");
                    tap_code(KC_ENTER);
                #endif
                #ifdef KEYBOARD_splitkb_kyria_rev3
                    SEND_STRING ("qmk compile -kb hillside/52 -km spacerock");
                    tap_code(KC_ENTER);
                #endif
            }
            return false;

// ┌───────────────────────────────────────────────────────────┐
// │ o s  s h o r t c u t                                      │
// └───────────────────────────────────────────────────────────┘

        case OS_COPY:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD("c"));
                } else {
                    SEND_STRING(SS_LCTL("c"));
                }
            }
            return true;

        case OS_CUT:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD("x"));
                } else {
                    SEND_STRING(SS_LCTL("x"));
                }
            }
            return true;

        case OS_PASTE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD("v"));
                } else {
                    SEND_STRING(SS_LCTL("v"));
                }
            }
            return true;

        case OS_UNDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD("z"));
                } else {
                    SEND_STRING(SS_LCTL("z"));
                }
            }
            return true;

        case OS_REDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD(SS_LSFT("z")));
                } else {
                    SEND_STRING(SS_LCTL(SS_LSFT("z")));
                }
            }
            return true;

        case OS_SAVE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LCMD("s"));
                } else {
                    SEND_STRING(SS_LCTL("s"));
                }
            }
            return true;


// ┌───────────────────────────────────────────────────────────┐
// │ p r o d u c t i v i t y                                   │
// └───────────────────────────────────────────────────────────┘

        case SNAP1:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LSFT(SS_LCMD("4")));           //MAC
                } else {
                    SEND_STRING(SS_LWIN(SS_TAP(X_PSCR)));         //WIN
                }
            }
            break;

        case SNAP2:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    SEND_STRING(SS_LSFT(SS_LCMD(SS_LCTL("4"))));  //MAC
                } else {
                    SEND_STRING(SS_LSFT(SS_LWIN("S")));           //WIN
                }
            }
            break;

        case KC_MPLY:
            if (record->event.pressed) {
            #ifdef HAPTIC_ENABLE
                    drv2605l_pulse(sharp_click);
            #endif // HAPTIC_ENABL
            }
            break;
    }

    return true;
}
