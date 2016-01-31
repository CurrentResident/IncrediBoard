#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"

typedef boost::fusion::vector<KeyA,     KeyE, KeyE,     KeyNONE,   KeyA> Row0;
typedef boost::fusion::vector<KeyB,     KeyF, KeyF,     KeyLSHIFT, KeyB> Row1;
typedef boost::fusion::vector<KeyC,     KeyG, KeyNONE,  KeyNONE,   KeyC> Row2;
typedef boost::fusion::vector<KeyD,     KeyH, KeyNONE,  KeyH,      KeyD> Row3;
typedef boost::fusion::vector<KeyNONE,  KeyI, KeyNONE,  KeyI,      KeyE> Row4;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4> Matrix;

#endif
