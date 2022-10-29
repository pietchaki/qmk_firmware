#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _MACRO 2
#define _ADJUST 3
#define _GAMING 4
#define _GAMING2 5

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	SYMB,
	MACRO,
	ADJUST,
	ALT_TAB,
	WIN_E,
	SQLFX,
};

// Shortcut to make keymap more readable
#define FN3_ESC LT(_ADJUST, KC_ESC)
#define THUMB1 LT(_SYMB, KC_DEL)
#define THUMB2 LT(_MACRO, KC_INS)
#define THUMB3 LCTL_T(KC_HOME)
#define THUMB4 LSFT_T(KC_END)

//MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	case ALT_TAB:
		if (record->event.pressed) {
			if (!is_alt_tab_active) {
				is_alt_tab_active = true;
				register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		} else {
			unregister_code(KC_TAB);
		}
		break;
	case WIN_E:
		if (record->event.pressed) {
			SEND_STRING(SS_LWIN("e"));
		}
		break;
	case SQLFX:
		if (record->event.pressed) {
			SEND_STRING(SS_TAP(X_END) ", " SS_TAP(X_DELETE) SS_TAP(X_END));
		}
		break;
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
	if (is_alt_tab_active) {
		if (timer_elapsed(alt_tab_timer) > 1000) {
			unregister_code(KC_LALT);
			is_alt_tab_active = false;
		}
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     FN3_ESC ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                                                ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_PSCR , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_CAPS ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_GRV                            ,KC_MINS ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_TAB                            ,KC_EQL  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,THUMB1  ,THUMB2          ,THUMB3  ,THUMB4  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_INT1 , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 KC_LALT ,KC_NUBS ,KC_RBRC ,KC_BSLS      ,KC_LCTL     ,KC_SPC  ,KC_BSPC         ,KC_ENT  ,KC_SPC      ,KC_RALT      ,KC_LEFT ,KC_RGHT ,KC_DOWN ,KC_UP
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
[_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5                                               ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_EXLM ,KC_AT   ,KC_RCBR ,KC_PIPE,S(KC_NUBS),KC_F11                           ,KC_LPRN ,KC_PSLS ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PMNS ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_HASH ,KC_DLR  ,KC_RBRC ,KC_NUHS ,KC_AMPR ,KC_F12                            ,KC_RPRN ,KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_PERC ,KC_SLSH ,KC_LPRN ,KC_RPRN ,KC_ASTR ,_______ ,XXXXXXX         ,_______ ,_______ ,KC_QUES ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 _______ ,_______ ,_______ ,_______      ,_______     ,KC_ENT  ,XXXXXXX         ,_______ ,_______     ,KC_P0        ,KC_P0   ,KC_PDOT ,KC_PENT ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_MACRO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   RCS(KC_ESC),XXXXXXX,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                                             ,KC_F13  ,KC_F14  ,KC_F15  ,KC_F16  ,XXXXXXX ,TG(_GAMING) ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,WIN_E   ,XXXXXXX ,XXXXXXX ,G(KC_L)                           ,XXXXXXX ,KC_F17   ,KC_F18 ,KC_F19  ,KC_F20  ,XXXXXXX ,TG(_GAMING2) , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,ALT_TAB                           ,XXXXXXX ,KC_F21  ,KC_F22  ,KC_F23  ,KC_F24  ,XXXXXXX ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,SQLFX   ,XXXXXXX ,_______         ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX      ,XXXXXXX     ,XXXXXXX, XXXXXXX         ,XXXXXXX ,XXXXXXX     ,XXXXXXX      ,KC_MRWD ,KC_MFFD ,KC_VOLD ,KC_VOLU
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                                             ,BL_DEC, BL_INC   ,XXXXXXX ,XXXXXXX ,RGB_MOD ,RGB_TOG ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                           ,BL_TOGG ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RESET                             ,BL_BRTG ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RGB_HUD ,RGB_HUI , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX         ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RGB_SAD ,RGB_SAI , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX         ,XXXXXXX ,XXXXXXX     ,XXXXXXX      ,XXXXXXX ,XXXXXXX ,RGB_VAD ,RGB_VAI
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
    [_GAMING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                                                ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TG(_GAMING) , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_CAPS ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_GRV                            ,KC_MINS ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_SLSH ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_TAB                            ,KC_EQL  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_LBRC , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_DEL  ,KC_INS          ,KC_HOME ,KC_END  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_INT1 , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 KC_LALT ,KC_NUBS ,KC_RBRC ,KC_BSLS      ,KC_LCTL     ,KC_SPC  ,KC_BSPC         ,KC_PGDN ,KC_PGUP     ,KC_RALT      ,KC_LEFT ,KC_RGHT ,KC_DOWN ,KC_UP
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
  [_GAMING2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                                                ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,TG(_GAMING2) , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_GRV  ,KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_6                              ,KC_MINS ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_CAPS ,KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G                              ,KC_EQL  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_LBRC , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_B    ,KC_LCTL ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N            ,KC_HOME ,KC_END  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_INT1 , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 KC_LALT ,KC_NUBS ,KC_NUBS ,XXXXXXX      ,KC_LALT     ,KC_SPC  ,KC_BSPC         ,KC_PGDN ,KC_PGUP     ,KC_RALT      ,KC_LEFT ,KC_RGHT ,KC_DOWN ,KC_UP
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
/*  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     FN3_ESC ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                                                ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_PSCR , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_CAPS ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_GRV                            ,KC_MINS ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_TAB                            ,KC_EQL  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT , 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,THUMB1  ,THUMB2          ,THUMB3  ,THUMB4  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_INT1 , 
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 KC_LALT ,KC_NUBS ,KC_RBRC ,KC_BSLS      ,KC_LCTL     ,KC_SPC  ,KC_BSPC         ,KC_ENT  ,KC_SPC      ,KC_RALT      ,KC_LEFT ,KC_RGHT ,KC_DOWN ,KC_UP
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
*/
};
