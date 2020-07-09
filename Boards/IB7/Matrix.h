#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"

typedef boost::fusion::vector<KeyESCAPE, KeyNONE, KeyF1,   KeyF2,   KeyF3,   KeyF4,    KeyF5,   KeyF6,   KeyF7,    KeyF8,   KeyF9,    KeyF10,        KeyF11,         KeyF12,       KeyPRTSCR, KeySCRLK, KeyPAUSE,     KeyNONE,     KeyNONE,     KeyNONE,        KeyNONE>     Row0;
typedef boost::fusion::vector<KeyTILDE,  Key1,    Key2,    Key3,    Key4,    Key5,     Key6,    Key7,    Key8,     Key9,    Key0,     KeyMINUS,      KeyEQUALS,      KeyBACKSPACE, KeyINSERT, KeyHOME,  KeyPAGE_UP,   KeyKP_NUMLK, KeyKP_SLASH, KeyKP_ASTERISK, KeyKP_MINUS> Row1;
typedef boost::fusion::vector<KeyTAB,    KeyQ,    KeyW,    KeyE,    KeyR,    KeyT,     KeyY,    KeyU,    KeyI,     KeyO,    KeyP,     KeyLEFT_BRACE, KeyRIGHT_BRACE, KeyBACKSLASH, KeyDELETE, KeyEND,   KeyPAGE_DOWN, KeyKP_7,     KeyKP_8,     KeyKP_9,        KeyKP_PLUS>  Row2;
typedef boost::fusion::vector<KeyCAPS,   KeyA,    KeyS,    KeyD,    KeyF,    KeyG,     KeyNONE, KeyH,    KeyJ,     KeyK,    KeyL,     KeySEMICOLON,  KeyQUOTE,       KeyENTER,     KeyNONE,   KeyNONE,  KeyNONE,      KeyKP_4,     KeyKP_5,     KeyKP_6,        KeyNONE>     Row3;
typedef boost::fusion::vector<KeyLSHIFT, KeyZ,    KeyX,    KeyC,    KeyV,    KeyB,     KeyNONE, KeyNONE, KeyN,     KeyM,    KeyCOMMA, KeyPERIOD,     KeySLASH,       KeyRSHIFT,    KeyNONE,   KeyUP,    KeyNONE,      KeyKP_1,     KeyKP_2,     KeyKP_3,        KeyKP_ENTER> Row4;
typedef boost::fusion::vector<KeyLCTRL,  KeyLGUI, KeyLALT, KeyNONE, KeyNONE, KeySPACE, KeyNONE, KeyNONE, KeyNONE,  KeyNONE, KeyRALT,  KeyRGUI,       KeyFn,          KeyRCTRL,     KeyLEFT,   KeyDOWN,  KeyRIGHT,     KeyKP_0,     KeyNONE,     KeyKP_PERIOD,   KeyNONE>     Row5;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4, Row5> Matrix;

#endif
