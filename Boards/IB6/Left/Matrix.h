#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"


typedef boost::fusion::vector<KeyESCAPE, KeyF1,   KeyF2,   KeyF3,   KeyF4,    KeyNONE, KeyNONE> Row0;
typedef boost::fusion::vector<KeyTILDE,  Key1,    Key2,    Key3,    Key4,     Key5,    Key6>    Row1;
typedef boost::fusion::vector<KeyTAB,    KeyNONE, KeyQ,    KeyW,    KeyE,     KeyR,    KeyT>    Row2;
typedef boost::fusion::vector<KeyCAPS,   KeyNONE, KeyA,    KeyS,    KeyD,     KeyF,    KeyG>    Row3;
typedef boost::fusion::vector<KeyLSHIFT, KeyNONE, KeyZ,    KeyX,    KeyC,     KeyV,    KeyB>    Row4;
typedef boost::fusion::vector<KeyLCTRL,  KeyNONE, KeyLGUI, KeyLALT, KeySPACE, KeyNONE, KeyNONE> Row5;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4, Row5> Matrix;

#endif
