#ifndef KEY_VALUES_H_
#define KEY_VALUES_H_

#include "KeyCodes.h"
#include "Key.h"

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
typedef Key <KEY_CAPS_LOCK>   KeyCAPS;
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
typedef Key <KEY_PRINTSCREEN> KeyPRTSCR;
typedef Key <KEY_SCROLL_LOCK> KeySCRLK;
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

typedef Key <KEY_KP_NUM_LOCK> KeyKP_NUMLK;
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
typedef Key <KEY_KP_PERIOD>   KeyKP_PERIOD;

typedef KeyModifier<KEY_LEFT_CTRL,   KEY_MOD_LEFT_CTRL>   KeyLCTRL;
typedef KeyModifier<KEY_LEFT_SHIFT,  KEY_MOD_LEFT_SHIFT>  KeyLSHIFT;
typedef KeyModifier<KEY_LEFT_ALT,    KEY_MOD_LEFT_ALT>    KeyLALT;
typedef KeyModifier<KEY_LEFT_GUI,    KEY_MOD_LEFT_GUI>    KeyLGUI;
typedef KeyModifier<KEY_RIGHT_CTRL,  KEY_MOD_RIGHT_CTRL>  KeyRCTRL;
typedef KeyModifier<KEY_RIGHT_SHIFT, KEY_MOD_RIGHT_SHIFT> KeyRSHIFT;
typedef KeyModifier<KEY_RIGHT_ALT,   KEY_MOD_RIGHT_ALT>   KeyRALT;
typedef KeyModifier<KEY_RIGHT_GUI,   KEY_MOD_RIGHT_GUI>   KeyRGUI;

#endif
