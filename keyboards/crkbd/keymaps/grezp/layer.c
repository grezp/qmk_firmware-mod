#include QMK_KEYBOARD_H
#include "enums.h"

// Render Blank Space
void render_space(void) {
    oled_write_ln_P(PSTR("     "), false);
}

// Render separator lines for oled display
void render_separator(void) {
    switch (get_highest_layer(layer_state)){
        default:
            //oled_write_ln_P(PSTR("++++++++++++++++++++"), false);
            oled_write_ln_P(PSTR("===================="), false);
    }
}

// Render current layer state
void render_layer_state(void){
	// If you want to change the display of OLED, you need to change here
    switch (get_highest_layer(layer_state)){
        case _COLEMAK:
            oled_write_ln_P(PSTR("[ MODE | COLEMAK   ]"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("[ MODE | QWRTY     ]"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("[ MODE | NUMBERS   ]"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("[ MODE | SYMBOLS   ]"), false);
            break;
        case _ADJ:
            oled_write_ln_P(PSTR("[ MODE | ADJUST    ]"), false);
            break;
        default:
            oled_write_ln_P(PSTR("[ MODE | UNDEF     ]"), false);
    }
}

// Render USB State
void render_usb_state(void) {
    switch (USB_DeviceState) {
      case DEVICE_STATE_Unattached:
          oled_write_ln_P(PSTR("[ USB  | FREE      ]"), false);
          break;
      case DEVICE_STATE_Suspended:
          oled_write_ln_P(PSTR("[ USB  | SLEEP     ]"), false);
          break;
      case DEVICE_STATE_Configured:
          oled_write_ln_P(PSTR("[ USB  | READY     ]"), false);
          break;
      case DEVICE_STATE_Powered:
          oled_write_ln_P(PSTR("[ USB  | PWRD      ]"), false);
          break;
      case DEVICE_STATE_Default:
          oled_write_ln_P(PSTR("[ USB  | DFLT      ]"), false);
          break;
      case DEVICE_STATE_Addressed:
          oled_write_ln_P(PSTR("[ USB  | ADDRS     ]"), false);
          break;
      default:
          oled_write_ln_P(PSTR("[ USB  | INVALID   ]"), false);
    }
}
