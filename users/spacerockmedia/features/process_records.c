#include QMK_KEYBOARD_H
#include "spacerockmedia.h"
#include "features/process_records.h"
#include "features/callum/process_records.h"
#include "features/layers/process_records.h"
#include "features/macros/process_records.h"

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

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
    if (!process_record_features_layers(keycode, record)) {
        return false;
    }

    if (!process_record_features_callum(keycode, record)) {
        return false;
    }

    if (!process_record_features_macros(keycode, record)) {
        return false;
    }

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
    // Sentence Case
    #ifdef FEATURE_SENTENCE_CASE_ENABLE
        if (!process_sentence_case(keycode, record)) { return false; }
    #endif

    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    return true;
}
