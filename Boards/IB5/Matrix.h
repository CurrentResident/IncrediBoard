#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"

typedef boost::fusion::vector<KeyESCAPE, KeyF1,   KeyF2,   KeyF3,   KeyF4,   KeyF5,    KeyF6,   KeyF7,   KeyF8,    KeyF9,   KeyF10,   KeyF11,       KeyF12,        KeyPRTSCR,      KeyHOME,      KeyEND>       Row0;
typedef boost::fusion::vector<KeyTILDE,  Key1,    Key2,    Key3,    Key4,    Key5,     Key6,    Key7,    Key8,     Key9,    Key0,     KeyMINUS,     KeyEQUALS,     KeyNONE,        KeyBACKSPACE, KeyINSERT>    Row1;
typedef boost::fusion::vector<KeyTAB,    KeyQ,    KeyW,    KeyE,    KeyR,    KeyT,     KeyY,    KeyNONE, KeyU,     KeyI,    KeyO,     KeyP,         KeyLEFT_BRACE, KeyRIGHT_BRACE, KeyBACKSLASH, KeyDELETE>    Row2;
typedef boost::fusion::vector<KeyCAPS,   KeyA,    KeyS,    KeyD,    KeyF,    KeyG,     KeyH,    KeyNONE, KeyJ,     KeyK,    KeyL,     KeySEMICOLON, KeyQUOTE,      KeyNONE,        KeyENTER,     KeyPAGE_UP>   Row3;
typedef boost::fusion::vector<KeyLSHIFT, KeyZ,    KeyX,    KeyC,    KeyV,    KeyB,     KeyN,    KeyNONE, KeyN,     KeyM,    KeyCOMMA, KeyPERIOD,    KeySLASH,      KeyRSHIFT,      KeyUP,        KeyPAGE_DOWN> Row4;
typedef boost::fusion::vector<KeyLCTRL,  KeyLGUI, KeyLALT, KeyNONE, KeyNONE, KeySPACE, KeyNONE, KeyNONE, KeyNONE,  KeyNONE, KeyRALT,  KeyFn,        KeyRCTRL,      KeyLEFT,        KeyDOWN,      KeyRIGHT>     Row5;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4, Row5> Matrix;

#endif
