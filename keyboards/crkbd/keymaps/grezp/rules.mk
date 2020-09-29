CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
MOUSEKEY_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
OLED_DRIVER_ENABLE = yes
EXTRAKEY_ENABLE = yes
BOOTLOADER = atmel-dfu

# If you want to change the display of OLED, you need to change here
SRC +=  logo_reader.c \
				layer.c
