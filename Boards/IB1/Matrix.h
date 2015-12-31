#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "Key.h"
#include "KeyValues.h"

#include "Column.h"

typedef boost::fusion::vector<KeyESCAPE,KeyTILDE, KeyTAB,   KeyCAPS_LOCK,   KeyMOD_LEFT_SHIFT,  KeyMOD_LEFT_CTRL> Column0Keys;
typedef boost::fusion::vector<KeyNONE,  Key1,     KeyQ,     KeyA,           KeyZ,               KeyMOD_LEFT_GUI>  Column1Keys;
typedef boost::fusion::vector<KeyF1,    Key2,     KeyW,     KeyS,           KeyX,               KeyMOD_LEFT_ALT>  Column2Keys;
typedef boost::fusion::vector<KeyF2,    Key3,     KeyE,     KeyD,           KeyC,               KeyNONE>          Column3Keys;
typedef boost::fusion::vector<KeyF3,    Key4,     KeyR,     KeyF,           KeyV,               KeyNONE>          Column4Keys;
typedef boost::fusion::vector<KeyF4,    Key5,     KeyT,     KeyG,           KeyB,               KeySPACE>         Column5Keys;
typedef boost::fusion::vector<KeyF5,    Key6,     KeyY,     KeyH,           KeyN,               KeyNONE>          Column6Keys;
typedef boost::fusion::vector<KeyF6,    Key7,     KeyU,     KeyNONE,        KeyNONE,            KeyNONE>          Column7Keys;
typedef boost::fusion::vector<KeyF7,    Key8,     KeyI,     KeyJ,           KeyNONE,            KeyNONE>          Column8Keys;
typedef boost::fusion::vector<KeyF8,    Key9,     KeyO,     KeyK,           KeyM,               KeyNONE>          Column9Keys;
typedef boost::fusion::vector<KeyF9,    Key0,     KeyP,     KeyL,           KeyCOMMA,           KeyMOD_RIGHT_ALT> Column10Keys;

typedef boost::fusion::vector<KeyF10, KeyMINUS,     KeyLEFT_BRACE,  KeySEMICOLON, KeyPERIOD,          KeyMOD_RIGHT_GUI>  Column11Keys;
typedef boost::fusion::vector<KeyF11, KeyEQUALS,    KeyRIGHT_BRACE, KeyQUOTE,     KeySLASH,           KeyNONE>           Column12Keys;
typedef boost::fusion::vector<KeyF12, KeyBACKSPACE, KeyBACKSLASH,   KeyENTER,     KeyMOD_RIGHT_SHIFT, KeyMOD_RIGHT_CTRL> Column13Keys;

typedef boost::fusion::vector<KeyPRINTSCREEN, KeyINSERT,  KeyDELETE,    KeyNONE, KeyNONE, KeyLEFT>  Column14Keys;
typedef boost::fusion::vector<KeySCROLL_LOCK, KeyHOME,    KeyEND,       KeyNONE, KeyUP,   KeyDOWN>  Column15Keys;
typedef boost::fusion::vector<KeyPAUSE,       KeyPAGE_UP, KeyPAGE_DOWN, KeyNONE, KeyNONE, KeyRIGHT> Column16Keys;

typedef boost::fusion::vector<KeyNONE, KeyKP_NUM_LOCK, KeyKP_7,    KeyKP_4, KeyKP_1,     KeyNONE>      Column17Keys;
typedef boost::fusion::vector<KeyNONE, KeyKP_SLASH,    KeyKP_8,    KeyKP_5, KeyKP_2,     KeyKP_0>      Column18Keys;
typedef boost::fusion::vector<KeyNONE, KeyKP_ASTERISK, KeyKP_9,    KeyKP_6, KeyKP_3,     KeyKP_PERIOD> Column19Keys;
typedef boost::fusion::vector<KeyNONE, KeyKP_MINUS,    KeyKP_PLUS, KeyNONE, KeyKP_ENTER, KeyNONE>      Column20Keys;


typedef Column <Platform::SetColumn< 0>, Column0Keys,  Platform::ResetColumn< 0> > Column0;
typedef Column <Platform::SetColumn< 1>, Column1Keys,  Platform::ResetColumn< 1> > Column1;
typedef Column <Platform::SetColumn< 2>, Column2Keys,  Platform::ResetColumn< 2> > Column2;
typedef Column <Platform::SetColumn< 3>, Column3Keys,  Platform::ResetColumn< 3> > Column3;
typedef Column <Platform::SetColumn< 4>, Column4Keys,  Platform::ResetColumn< 4> > Column4;
typedef Column <Platform::SetColumn< 5>, Column5Keys,  Platform::ResetColumn< 5> > Column5;
typedef Column <Platform::SetColumn< 6>, Column6Keys,  Platform::ResetColumn< 6> > Column6;
typedef Column <Platform::SetColumn< 7>, Column7Keys,  Platform::ResetColumn< 7> > Column7;
typedef Column <Platform::SetColumn< 8>, Column8Keys,  Platform::ResetColumn< 8> > Column8;
typedef Column <Platform::SetColumn< 9>, Column9Keys,  Platform::ResetColumn< 9> > Column9;
typedef Column <Platform::SetColumn<10>, Column10Keys, Platform::ResetColumn<10> > Column10;
typedef Column <Platform::SetColumn<11>, Column11Keys, Platform::ResetColumn<11> > Column11;
typedef Column <Platform::SetColumn<12>, Column12Keys, Platform::ResetColumn<12> > Column12;
typedef Column <Platform::SetColumn<13>, Column13Keys, Platform::ResetColumn<13> > Column13;
typedef Column <Platform::SetColumn<14>, Column14Keys, Platform::ResetColumn<14> > Column14;
typedef Column <Platform::SetColumn<15>, Column15Keys, Platform::ResetColumn<15> > Column15;
typedef Column <Platform::SetColumn<16>, Column16Keys, Platform::ResetColumn<16> > Column16;
typedef Column <Platform::SetColumn<17>, Column17Keys, Platform::ResetColumn<17> > Column17;
typedef Column <Platform::SetColumn<18>, Column18Keys, Platform::ResetColumn<18> > Column18;
typedef Column <Platform::SetColumn<19>, Column19Keys, Platform::ResetColumn<19> > Column19;
typedef Column <Platform::SetColumn<20>, Column20Keys, Platform::ResetColumn<20> > Column20;

typedef boost::fusion::vector
<
    Column0,
    Column1,
    Column2,
    Column3,
    Column4,
    Column5,
    Column6,
    Column7,
    Column8,
    Column9,
    Column10,
    Column11,
    Column12,
    Column13,
    Column14,
    Column15,
    Column16,
    Column17,
    Column18,
    Column19,
    Column20
> Matrix;

#endif
