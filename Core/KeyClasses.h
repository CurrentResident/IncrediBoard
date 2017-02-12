#ifndef IB_KEY_CLASSES_H_
#define IB_KEY_CLASSES_H_

#include "KeyCodes.h"
#include "Key.h"

typedef Key <IB_KEY_NONE> KeyNONE;

typedef Key <IB_KEY_A> KeyA;
typedef Key <IB_KEY_B> KeyB;
typedef Key <IB_KEY_C> KeyC;
typedef Key <IB_KEY_D> KeyD;
typedef Key <IB_KEY_E> KeyE;
typedef Key <IB_KEY_F> KeyF;
typedef Key <IB_KEY_G> KeyG;
typedef Key <IB_KEY_H> KeyH;
typedef Key <IB_KEY_I> KeyI;
typedef Key <IB_KEY_J> KeyJ;
typedef Key <IB_KEY_K> KeyK;
typedef Key <IB_KEY_L> KeyL;
typedef Key <IB_KEY_M> KeyM;
typedef Key <IB_KEY_N> KeyN;
typedef Key <IB_KEY_O> KeyO;
typedef Key <IB_KEY_P> KeyP;
typedef Key <IB_KEY_Q> KeyQ;
typedef Key <IB_KEY_R> KeyR;
typedef Key <IB_KEY_S> KeyS;
typedef Key <IB_KEY_T> KeyT;
typedef Key <IB_KEY_U> KeyU;
typedef Key <IB_KEY_V> KeyV;
typedef Key <IB_KEY_W> KeyW;
typedef Key <IB_KEY_X> KeyX;
typedef Key <IB_KEY_Y> KeyY;
typedef Key <IB_KEY_Z> KeyZ;
typedef Key <IB_KEY_1> Key1;
typedef Key <IB_KEY_2> Key2;
typedef Key <IB_KEY_3> Key3;
typedef Key <IB_KEY_4> Key4;
typedef Key <IB_KEY_5> Key5;
typedef Key <IB_KEY_6> Key6;
typedef Key <IB_KEY_7> Key7;
typedef Key <IB_KEY_8> Key8;
typedef Key <IB_KEY_9> Key9;
typedef Key <IB_KEY_0> Key0;

typedef Key <IB_KEY_ENTER>       KeyENTER;
typedef Key <IB_KEY_ESCAPE>      KeyESCAPE;
typedef Key <IB_KEY_BACKSPACE>   KeyBACKSPACE;
typedef Key <IB_KEY_TAB>         KeyTAB;
typedef Key <IB_KEY_SPACE>       KeySPACE;
typedef Key <IB_KEY_MINUS>       KeyMINUS;
typedef Key <IB_KEY_EQUALS>      KeyEQUALS;
typedef Key <IB_KEY_LEFT_BRACE>  KeyLEFT_BRACE;
typedef Key <IB_KEY_RIGHT_BRACE> KeyRIGHT_BRACE;
typedef Key <IB_KEY_BACKSLASH>   KeyBACKSLASH;
typedef Key <IB_KEY_NUMBER>      KeyNUMBER;
typedef Key <IB_KEY_SEMICOLON>   KeySEMICOLON;
typedef Key <IB_KEY_QUOTE>       KeyQUOTE;
typedef Key <IB_KEY_TILDE>       KeyTILDE;
typedef Key <IB_KEY_COMMA>       KeyCOMMA;
typedef Key <IB_KEY_PERIOD>      KeyPERIOD;
typedef Key <IB_KEY_SLASH>       KeySLASH;
typedef Key <IB_KEY_CAPS_LOCK>   KeyCAPS;
typedef Key <IB_KEY_F1>          KeyF1;
typedef Key <IB_KEY_F2>          KeyF2;
typedef Key <IB_KEY_F3>          KeyF3;
typedef Key <IB_KEY_F4>          KeyF4;
typedef Key <IB_KEY_F5>          KeyF5;
typedef Key <IB_KEY_F6>          KeyF6;
typedef Key <IB_KEY_F7>          KeyF7;
typedef Key <IB_KEY_F8>          KeyF8;
typedef Key <IB_KEY_F9>          KeyF9;
typedef Key <IB_KEY_F10>         KeyF10;
typedef Key <IB_KEY_F11>         KeyF11;
typedef Key <IB_KEY_F12>         KeyF12;
typedef Key <IB_KEY_PRINTSCREEN> KeyPRTSCR;
typedef Key <IB_KEY_SCROLL_LOCK> KeySCRLK;
typedef Key <IB_KEY_PAUSE>       KeyPAUSE;
typedef Key <IB_KEY_INSERT>      KeyINSERT;
typedef Key <IB_KEY_HOME>        KeyHOME;
typedef Key <IB_KEY_PAGE_UP>     KeyPAGE_UP;
typedef Key <IB_KEY_DELETE>      KeyDELETE;
typedef Key <IB_KEY_END>         KeyEND;
typedef Key <IB_KEY_PAGE_DOWN>   KeyPAGE_DOWN;
typedef Key <IB_KEY_RIGHT>       KeyRIGHT;
typedef Key <IB_KEY_LEFT>        KeyLEFT;
typedef Key <IB_KEY_DOWN>        KeyDOWN;
typedef Key <IB_KEY_UP>          KeyUP;

typedef Key <IB_KEY_KP_NUM_LOCK> KeyKP_NUMLK;
typedef Key <IB_KEY_KP_SLASH>    KeyKP_SLASH;
typedef Key <IB_KEY_KP_ASTERISK> KeyKP_ASTERISK;
typedef Key <IB_KEY_KP_MINUS>    KeyKP_MINUS;
typedef Key <IB_KEY_KP_PLUS>     KeyKP_PLUS;
typedef Key <IB_KEY_KP_ENTER>    KeyKP_ENTER;
typedef Key <IB_KEY_KP_1>        KeyKP_1;
typedef Key <IB_KEY_KP_2>        KeyKP_2;
typedef Key <IB_KEY_KP_3>        KeyKP_3;
typedef Key <IB_KEY_KP_4>        KeyKP_4;
typedef Key <IB_KEY_KP_5>        KeyKP_5;
typedef Key <IB_KEY_KP_6>        KeyKP_6;
typedef Key <IB_KEY_KP_7>        KeyKP_7;
typedef Key <IB_KEY_KP_8>        KeyKP_8;
typedef Key <IB_KEY_KP_9>        KeyKP_9;
typedef Key <IB_KEY_KP_0>        KeyKP_0;
typedef Key <IB_KEY_KP_PERIOD>   KeyKP_PERIOD;

typedef KeyModifier<IB_KEY_LEFT_CTRL,   IB_KEY_MOD_LEFT_CTRL>   KeyLCTRL;
typedef KeyModifier<IB_KEY_LEFT_SHIFT,  IB_KEY_MOD_LEFT_SHIFT>  KeyLSHIFT;
typedef KeyModifier<IB_KEY_LEFT_ALT,    IB_KEY_MOD_LEFT_ALT>    KeyLALT;
typedef KeyModifier<IB_KEY_LEFT_GUI,    IB_KEY_MOD_LEFT_GUI>    KeyLGUI;
typedef KeyModifier<IB_KEY_RIGHT_CTRL,  IB_KEY_MOD_RIGHT_CTRL>  KeyRCTRL;
typedef KeyModifier<IB_KEY_RIGHT_SHIFT, IB_KEY_MOD_RIGHT_SHIFT> KeyRSHIFT;
typedef KeyModifier<IB_KEY_RIGHT_ALT,   IB_KEY_MOD_RIGHT_ALT>   KeyRALT;
typedef KeyModifier<IB_KEY_RIGHT_GUI,   IB_KEY_MOD_RIGHT_GUI>   KeyRGUI;

#endif
