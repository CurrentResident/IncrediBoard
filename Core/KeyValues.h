#ifndef KEY_VALUES_H_
#define KEY_VALUES_H_

#include "Key.h"

// The following keycodes are from the USB HID Usage Table spec 1.12, section 10

#define KEY_NONE    0x00

#define KEY_A       0x04
#define KEY_B       0x05
#define KEY_C       0x06
#define KEY_D       0x07
#define KEY_E       0x08
#define KEY_F       0x09
#define KEY_G       0x0A
#define KEY_H       0x0B
#define KEY_I       0x0C
#define KEY_J       0x0D
#define KEY_K       0x0E
#define KEY_L       0x0F
#define KEY_M       0x10
#define KEY_N       0x11
#define KEY_O       0x12
#define KEY_P       0x13
#define KEY_Q       0x14
#define KEY_R       0x15
#define KEY_S       0x16
#define KEY_T       0x17
#define KEY_U       0x18
#define KEY_V       0x19
#define KEY_W       0x1A
#define KEY_X       0x1B
#define KEY_Y       0x1C
#define KEY_Z       0x1D
#define KEY_1       0x1E
#define KEY_2       0x1F
#define KEY_3       0x20
#define KEY_4       0x21
#define KEY_5       0x22
#define KEY_6       0x23
#define KEY_7       0x24
#define KEY_8       0x25
#define KEY_9       0x26
#define KEY_0       0x27

#define KEY_ENTER       0x28
#define KEY_ESCAPE      0x29
#define KEY_BACKSPACE   0x2A
#define KEY_TAB         0x2B
#define KEY_SPACE       0x2C
#define KEY_MINUS       0x2D
#define KEY_EQUALS      0x2E
#define KEY_LEFT_BRACE  0x2F
#define KEY_RIGHT_BRACE 0x30
#define KEY_BACKSLASH   0x31
#define KEY_NUMBER      0x32
#define KEY_SEMICOLON   0x33
#define KEY_QUOTE       0x34
#define KEY_TILDE       0x35
#define KEY_COMMA       0x36
#define KEY_PERIOD      0x37
#define KEY_SLASH       0x38
#define KEY_CAPS_LOCK   0x39
#define KEY_F1          0x3A
#define KEY_F2          0x3B
#define KEY_F3          0x3C
#define KEY_F4          0x3D
#define KEY_F5          0x3E
#define KEY_F6          0x4F
#define KEY_F7          0x40
#define KEY_F8          0x41
#define KEY_F9          0x42
#define KEY_F10         0x43
#define KEY_F11         0x44
#define KEY_F12         0x45
#define KEY_PRINTSCREEN 0x46
#define KEY_SCROLL_LOCK 0x47
#define KEY_PAUSE       0x48
#define KEY_INSERT      0x49
#define KEY_HOME        0x4A
#define KEY_PAGE_UP     0x4B
#define KEY_DELETE      0x4C
#define KEY_END         0x4D
#define KEY_PAGE_DOWN   0x4E
#define KEY_RIGHT       0x4F
#define KEY_LEFT        0x50
#define KEY_DOWN        0x51
#define KEY_UP          0x52

#define KEY_KP_NUM_LOCK 0x53
#define KEY_KP_SLASH    0x54
#define KEY_KP_ASTERISK 0x55
#define KEY_KP_MINUS    0x56
#define KEY_KP_PLUS     0x57
#define KEY_KP_ENTER    0x58
#define KEY_KP_1        0x59
#define KEY_KP_2        0x5A
#define KEY_KP_3        0x5B
#define KEY_KP_4        0x5C
#define KEY_KP_5        0x5D
#define KEY_KP_6        0x5E
#define KEY_KP_7        0x5F
#define KEY_KP_8        0x60
#define KEY_KP_9        0x61
#define KEY_KP_0        0x62
#define KEY_KP_PERIOD   0x63

// TODO:  Fill out tons of other keycodes.

#define KEY_MOD_LEFT_CTRL   0x01
#define KEY_MOD_LEFT_SHIFT  0x02
#define KEY_MOD_LEFT_ALT    0x04
#define KEY_MOD_LEFT_GUI    0x08
#define KEY_MOD_RIGHT_CTRL  0x10
#define KEY_MOD_RIGHT_SHIFT 0x20
#define KEY_MOD_RIGHT_ALT   0x40
#define KEY_MOD_RIGHT_GUI   0x80

typedef Key <KEY_NONE> KeyNONE;

typedef Key <KEY_A> KeyA;
typedef Key <KEY_B> KeyB;
typedef Key <KEY_C> KeyC;
typedef Key <KEY_D> KeyD;
typedef Key <KEY_E> KeyE;
typedef Key <KEY_F> KeyF;
typedef Key <KEY_G> KeyG;
typedef Key <KEY_H> KeyH;
typedef Key <KEY_I> KeyI;
typedef Key <KEY_J> KeyJ;
typedef Key <KEY_K> KeyK;
typedef Key <KEY_L> KeyL;
typedef Key <KEY_M> KeyM;
typedef Key <KEY_N> KeyN;
typedef Key <KEY_O> KeyO;
typedef Key <KEY_P> KeyP;
typedef Key <KEY_Q> KeyQ;
typedef Key <KEY_R> KeyR;
typedef Key <KEY_S> KeyS;
typedef Key <KEY_T> KeyT;
typedef Key <KEY_U> KeyU;
typedef Key <KEY_V> KeyV;
typedef Key <KEY_W> KeyW;
typedef Key <KEY_X> KeyX;
typedef Key <KEY_Y> KeyY;
typedef Key <KEY_Z> KeyZ;
typedef Key <KEY_1> Key1;
typedef Key <KEY_2> Key2;
typedef Key <KEY_3> Key3;
typedef Key <KEY_4> Key4;
typedef Key <KEY_5> Key5;
typedef Key <KEY_6> Key6;
typedef Key <KEY_7> Key7;
typedef Key <KEY_8> Key8;
typedef Key <KEY_9> Key9;
typedef Key <KEY_0> Key0;

typedef Key <KEY_ENTER>       KeyENTER;
typedef Key <KEY_ESCAPE>      KeyESCAPE;
typedef Key <KEY_BACKSPACE>   KeyBACKSPACE;
typedef Key <KEY_TAB>         KeyTAB;
typedef Key <KEY_SPACE>       KeySPACE;
typedef Key <KEY_MINUS>       KeyMINUS;
typedef Key <KEY_EQUALS>      KeyEQUALS;
typedef Key <KEY_LEFT_BRACE>  KeyLEFT_BRACE;
typedef Key <KEY_RIGHT_BRACE> KeyRIGHT_BRACE;
typedef Key <KEY_BACKSLASH>   KeyBACKSLASH;
typedef Key <KEY_NUMBER>      KeyNUMBER;
typedef Key <KEY_SEMICOLON>   KeySEMICOLON;
typedef Key <KEY_QUOTE>       KeyQUOTE;
typedef Key <KEY_TILDE>       KeyTILDE;
typedef Key <KEY_COMMA>       KeyCOMMA;
typedef Key <KEY_PERIOD>      KeyPERIOD;
typedef Key <KEY_SLASH>       KeySLASH;
typedef Key <KEY_CAPS_LOCK>   KeyCAPS_LOCK;
typedef Key <KEY_F1>          KeyF1;
typedef Key <KEY_F2>          KeyF2;
typedef Key <KEY_F3>          KeyF3;
typedef Key <KEY_F4>          KeyF4;
typedef Key <KEY_F5>          KeyF5;
typedef Key <KEY_F6>          KeyF6;
typedef Key <KEY_F7>          KeyF7;
typedef Key <KEY_F8>          KeyF8;
typedef Key <KEY_F9>          KeyF9;
typedef Key <KEY_F10>         KeyF10;
typedef Key <KEY_F11>         KeyF11;
typedef Key <KEY_F12>         KeyF12;
typedef Key <KEY_PRINTSCREEN> KeyPRINTSCREEN;
typedef Key <KEY_SCROLL_LOCK> KeySCROLL_LOCK;
typedef Key <KEY_PAUSE>       KeyPAUSE;
typedef Key <KEY_INSERT>      KeyINSERT;
typedef Key <KEY_HOME>        KeyHOME;
typedef Key <KEY_PAGE_UP>     KeyPAGE_UP;
typedef Key <KEY_DELETE>      KeyDELETE;
typedef Key <KEY_END>         KeyEND;
typedef Key <KEY_PAGE_DOWN>   KeyPAGE_DOWN;
typedef Key <KEY_RIGHT>       KeyRIGHT;
typedef Key <KEY_LEFT>        KeyLEFT;
typedef Key <KEY_DOWN>        KeyDOWN;
typedef Key <KEY_UP>          KeyUP;

typedef Key <KEY_KP_NUM_LOCK> KeyKP_NUM_LOCK;
typedef Key <KEY_KP_SLASH>    KeyKP_SLASH;
typedef Key <KEY_KP_ASTERISK> KeyKP_ASTERISK;
typedef Key <KEY_KP_MINUS>    KeyKP_MINUS;
typedef Key <KEY_KP_PLUS>     KeyKP_PLUS;
typedef Key <KEY_KP_ENTER>    KeyKP_ENTER;
typedef Key <KEY_KP_1>        KeyKP_1;
typedef Key <KEY_KP_2>        KeyKP_2;
typedef Key <KEY_KP_3>        KeyKP_3;
typedef Key <KEY_KP_4>        KeyKP_4;
typedef Key <KEY_KP_5>        KeyKP_5;
typedef Key <KEY_KP_6>        KeyKP_6;
typedef Key <KEY_KP_7>        KeyKP_7;
typedef Key <KEY_KP_8>        KeyKP_8;
typedef Key <KEY_KP_9>        KeyKP_9;
typedef Key <KEY_KP_0>        KeyKP_0;

#endif
