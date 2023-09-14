// Copyright 2023 Shawn McElroy, aka Autoferrit  (@autoferrit)
// Copyright 2023 @autoferrit
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "spacerock.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define LAYOUT_wrapper(...)   LAYOUT(__VA_ARGS__)

#define HRM_GUI_A    LGUI_T(KC_A)
#define HRM_GUI_SCLN RGUI_T(KC_SCLN)
#define HRM_GUI_O    RGUI_T(KC_O)
#define HRM_ALT_S    LALT_T(KC_S)
#define HRM_ALT_R    LALT_T(KC_R)
#define HRM_ALT_L    RALT_T(KC_L)
#define HRM_ALT_I    RALT_T(KC_I)
#define HRM_SFT_D    LALT_T(KC_D)
#define HRM_SFT_S    LALT_T(KC_S)
#define HRM_SFT_E    RALT_T(KC_E)
#define HRM_SFT_K    RALT_T(KC_K)
#define HRM_CTL_F    LCTL_T(KC_F)
#define HRM_CTL_T    LCTL_T(KC_T)
#define HRM_CTL_J    RCTL_T(KC_J)
#define HRM_CTL_N    RCTL_T(KC_N)


// clang-format off
#define _______________COLEMAK_L_TOP_______________ KC_Q, KC_W,    KC_F,    KC_P,    KC_B
#define _______________COLEMAK_L_MID_______________ KC_A, KC_R,    KC_S,    KC_T,    KC_G
#define _______________COLEMAK_L_MID_GASC__________ HRM_GUI_A, HRM_ALT_R, HRM_SFT_S, HRM_CTL_T, KC_G
#define _______________COLEMAK_L_BOT_______________ KC_Z, KC_X,    KC_C,    KC_D,    KC_V

#define _______________COLEMAK_R_TOP_______________ KC_J, KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _______________COLEMAK_R_MID_______________ KC_M, KC_N,    KC_E,    KC_I,    KC_O
#define _______________COLEMAK_R_MID_CSAG__________ KC_M, HRM_CTL_N, HRM_SFT_E, HRM_ALT_I, HRM_GUI_O
#define _______________COLEMAK_R_BOT_______________ KC_K, KC_H,    KC_COMM, KC_DOT,  KC_SLSH

#define _______________QUERTY__L_TOP_______________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define _______________QUERTY__L_MID_______________ KC_A, KC_S, KC_D, KC_F, KC_G
#define _______________QUERTY__L_MID_GASC__________ HRM_GUI_A, HRM_ALT_S, HRM_SFT_D, HRM_CTL_F, KC_G
#define _______________QUERTY__L_BOT_______________ KC_Z, KC_X, KC_C, KC_V, KC_B

#define _______________QUERTY__R_TOP_______________ KC_Y, KC_U, KC_I,    KC_O,   KC_P
#define _______________QUERTY__R_MID_______________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define _______________QUERTY__R_MID_CSAG__________ KC_H, HRM_CTL_J, HRM_SFT_K, HRM_ALT_L, HRM_GUI_SCLN
#define _______________QUERTY__R_BOT_______________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#define ____________THUMB_LEFT____________ KC_LCTL, LY_NAV, HYPR_T(KC_SPC), SC_LSPO
#define ____________THUMB_RIGHT___________ SC_RSPC,  HYPR_T(KC_ENT), LY_NAV, KC_RCTL

#define ________OSM_LEFT_________ KC_LGUI,  LC_LALT, OS_CTRL
#define ________OSM_RIGHT________ OS_CTRL, OS_ALT, OS_CMD

#define __________________RGB_INC__________________ RGB_MOD,  RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI
#define __________________RGB_DEC__________________ RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD
#define __________________RGB_DEC__________________ RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD

#define __________________NAV__LT__________________ KC_PGUP, M_LEFT,  KC_UP,   M_RIGHT, M_UP
#define __________________NAV__LM__________________ KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, M_DOWN


#define __LPT__ KC_TAB
#define __LPM__ LALT_T(KC_ESC)
#define __LPB__ KC_LGUI

#define __RPT__ MO(_ADJUST)
#define __RPM__ KC_LALT
#define __RPB__ KC_RGUI
