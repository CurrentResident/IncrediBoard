#ifndef IB_KEY_CODES_H_
#define IB_KEY_CODES_H_

// The following keycodes are from the USB HID Usage Table spec 1.12, section 10

#define IB_KEY_NONE    0x00

#define IB_KEY_A       0x04
#define IB_KEY_B       0x05
#define IB_KEY_C       0x06
#define IB_KEY_D       0x07
#define IB_KEY_E       0x08
#define IB_KEY_F       0x09
#define IB_KEY_G       0x0A
#define IB_KEY_H       0x0B
#define IB_KEY_I       0x0C
#define IB_KEY_J       0x0D
#define IB_KEY_K       0x0E
#define IB_KEY_L       0x0F
#define IB_KEY_M       0x10
#define IB_KEY_N       0x11
#define IB_KEY_O       0x12
#define IB_KEY_P       0x13
#define IB_KEY_Q       0x14
#define IB_KEY_R       0x15
#define IB_KEY_S       0x16
#define IB_KEY_T       0x17
#define IB_KEY_U       0x18
#define IB_KEY_V       0x19
#define IB_KEY_W       0x1A
#define IB_KEY_X       0x1B
#define IB_KEY_Y       0x1C
#define IB_KEY_Z       0x1D
#define IB_KEY_1       0x1E
#define IB_KEY_2       0x1F
#define IB_KEY_3       0x20
#define IB_KEY_4       0x21
#define IB_KEY_5       0x22
#define IB_KEY_6       0x23
#define IB_KEY_7       0x24
#define IB_KEY_8       0x25
#define IB_KEY_9       0x26
#define IB_KEY_0       0x27

#define IB_KEY_ENTER       0x28
#define IB_KEY_ESCAPE      0x29
#define IB_KEY_BACKSPACE   0x2A
#define IB_KEY_TAB         0x2B
#define IB_KEY_SPACE       0x2C
#define IB_KEY_MINUS       0x2D
#define IB_KEY_EQUALS      0x2E
#define IB_KEY_LEFT_BRACE  0x2F
#define IB_KEY_RIGHT_BRACE 0x30
#define IB_KEY_BACKSLASH   0x31
#define IB_KEY_NUMBER      0x32
#define IB_KEY_SEMICOLON   0x33
#define IB_KEY_QUOTE       0x34
#define IB_KEY_TILDE       0x35
#define IB_KEY_COMMA       0x36
#define IB_KEY_PERIOD      0x37
#define IB_KEY_SLASH       0x38
#define IB_KEY_CAPS_LOCK   0x39
#define IB_KEY_F1          0x3A
#define IB_KEY_F2          0x3B
#define IB_KEY_F3          0x3C
#define IB_KEY_F4          0x3D
#define IB_KEY_F5          0x3E
#define IB_KEY_F6          0x3F
#define IB_KEY_F7          0x40
#define IB_KEY_F8          0x41
#define IB_KEY_F9          0x42
#define IB_KEY_F10         0x43
#define IB_KEY_F11         0x44
#define IB_KEY_F12         0x45
#define IB_KEY_PRINTSCREEN 0x46
#define IB_KEY_SCROLL_LOCK 0x47
#define IB_KEY_PAUSE       0x48
#define IB_KEY_INSERT      0x49
#define IB_KEY_HOME        0x4A
#define IB_KEY_PAGE_UP     0x4B
#define IB_KEY_DELETE      0x4C
#define IB_KEY_END         0x4D
#define IB_KEY_PAGE_DOWN   0x4E
#define IB_KEY_RIGHT       0x4F
#define IB_KEY_LEFT        0x50
#define IB_KEY_DOWN        0x51
#define IB_KEY_UP          0x52

#define IB_KEY_KP_NUM_LOCK 0x53
#define IB_KEY_KP_SLASH    0x54
#define IB_KEY_KP_ASTERISK 0x55
#define IB_KEY_KP_MINUS    0x56
#define IB_KEY_KP_PLUS     0x57
#define IB_KEY_KP_ENTER    0x58
#define IB_KEY_KP_1        0x59
#define IB_KEY_KP_2        0x5A
#define IB_KEY_KP_3        0x5B
#define IB_KEY_KP_4        0x5C
#define IB_KEY_KP_5        0x5D
#define IB_KEY_KP_6        0x5E
#define IB_KEY_KP_7        0x5F
#define IB_KEY_KP_8        0x60
#define IB_KEY_KP_9        0x61
#define IB_KEY_KP_0        0x62
#define IB_KEY_KP_PERIOD   0x63

// TODO:  Fill out tons of other keycodes.

// The modifier keys do actually have their own keycodes.  They aren't reported in the normal USB keyboard
// keycode array, but rather have modifier values that get or'd into a dedicated modifier byte.  However, we
// still use the keycodes for internal bookkeeping purposes.
#define IB_KEY_LEFT_CTRL   0xE0
#define IB_KEY_LEFT_SHIFT  0xE1
#define IB_KEY_LEFT_ALT    0xE2
#define IB_KEY_LEFT_GUI    0xE3
#define IB_KEY_RIGHT_CTRL  0xE4
#define IB_KEY_RIGHT_SHIFT 0xE5
#define IB_KEY_RIGHT_ALT   0xE6
#define IB_KEY_RIGHT_GUI   0xE7

// The modifier values get or'd into a modifier byte.
#define IB_KEY_MOD_LEFT_CTRL   0x01
#define IB_KEY_MOD_LEFT_SHIFT  0x02
#define IB_KEY_MOD_LEFT_ALT    0x04
#define IB_KEY_MOD_LEFT_GUI    0x08
#define IB_KEY_MOD_RIGHT_CTRL  0x10
#define IB_KEY_MOD_RIGHT_SHIFT 0x20
#define IB_KEY_MOD_RIGHT_ALT   0x40
#define IB_KEY_MOD_RIGHT_GUI   0x80

#endif
