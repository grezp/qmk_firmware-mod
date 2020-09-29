#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"

// [Init Variables] ----------------------------------------------------------//
extern uint8_t is_master;
// Oled timer similar to Drashna's
static uint32_t oled_timer = 0;
// Boolean to store the master LED clear so it only runs once.
bool master_oled_cleared = false;

#define _____    KC_TRNS
#define XXXXX    KC_NO
#define M_NUM    MO(_NUM)
#define M_SYM    MO(_SYM)
#define M_ADJ    MO(_ADJ)
#define T_QWER   TG(_QWERTY)

// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT( \
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TAB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_LALT,\
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LGUI,   M_SYM,  KC_SPC,    KC_LSFT,   M_NUM,  KC_ENT \
                                      //`--------------------------'  `--------------------------'
    ),

    [_QWERTY] = LAYOUT( \
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         _____,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    _____,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   _____,\
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _____,   _____,   _____,      _____,   _____,   _____ \
                                      //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT( \
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         _____,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   XXXXX,   XXXXX,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,  KC_F10,   KC_F9,   KC_F8,   KC_F7,   KC_F6,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,   XXXXX,   _____,\
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _____,   M_ADJ,   _____,      _____,   _____,   _____ \
                                      //`--------------------------'  `--------------------------'
    ),

    [_SYM] = LAYOUT( \
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         _____, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   _____,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,   XXXXX, KC_MPLY, KC_VOLU, KC_MNXT, KC_TILD,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,   XXXXX,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         _____,   XXXXX, KC_MUTE, KC_VOLD, KC_MPRV,  KC_GRV,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,   _____,\
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             _____,   _____,   _____,      _____,   M_ADJ,   _____ \
                                      //`--------------------------'  `--------------------------'
    ),

    [_ADJ] = LAYOUT( \
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         RESET,  T_QWER,   XXXXX, KC_MS_U,   XXXXX,   XXXXX,                        XXXXX, KC_WH_D,   XXXXX,   XXXXX,  KC_F11,  KC_F12,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         XXXXX,   XXXXX, KC_MS_L, KC_MS_D, KC_MS_R,   XXXXX,                        XXXXX, KC_BTN1, KC_BTN2, KC_BTN3,   XXXXX,   XXXXX,\
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                        XXXXX, KC_WH_U,   XXXXX,   XXXXX,   XXXXX,   XXXXX,\
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             XXXXX,   _____,   XXXXX,      XXXXX,   _____,   XXXXX \
                                      //`--------------------------'  `--------------------------'
    )
};

// [Process User Input] ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      #ifdef OLED_DRIVER_ENABLE
          oled_timer = timer_read32();
      #endif
    }
    return true;
}

// [Matrix Scan] ------------------------------------------------------------//
void matrix_scan_user(void) {
     // Iddle timer to return to default layer if left on game layer
     if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 479999) {
         return;
     }
}

// [OLED Configuration] ------------------------------------------------------//
#ifdef OLED_DRIVER_ENABLE
// Init Oled and Rotate....
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!has_usb())
      return OLED_ROTATION_180;  // flips the display 180 to see it from my side
    return rotation;
}

// Read logo from font file
const char *read_logo(void);

// {OLED helpers} -----------------------------------------------//
// Render Logo
void render_logo(void) {
    oled_write(read_logo(), false);
}

// Master OLED Screen (Left Hand )
void render_master_oled(void) {
    render_separator();
    render_usb_state();
    render_separator();
    render_layer_state();
}

// Slave OLED scren (Right Hand)
void render_slave_oled(void) {
    render_logo();
}

// {OLED Task} -----------------------------------------------//
void oled_task_user(void) {
    // First time out switches to logo as first indication of iddle.
    if (timer_elapsed32(oled_timer) > 100000 && timer_elapsed32(oled_timer) < 479999) {
        // Render logo on both halves before full timeout
        if (is_master && !master_oled_cleared) {
            // Clear master OLED once so the logo renders properly
            oled_clear();
            master_oled_cleared = true;
        }
        render_logo();
        return;
    }
    // Drashna style timeout for LED and OLED Roughly 8mins
    else if (timer_elapsed32(oled_timer) > 480000) {
        oled_off();
        return;
    }
    else {
        oled_on();
        // Reset OLED Clear flag
        master_oled_cleared = false;
        // Show logo when USB dormant
        switch (USB_DeviceState) {
            case DEVICE_STATE_Unattached:
            case DEVICE_STATE_Powered:
            case DEVICE_STATE_Suspended:
                render_logo();
                break;
            default:
                if (is_master) {
                    render_master_oled();
                } else {
                    render_slave_oled();
                }
        }
    }
}
#endif
