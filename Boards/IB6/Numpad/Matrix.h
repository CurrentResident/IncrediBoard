#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"


typedef boost::fusion::vector<KeyKP_NUMLK, KeyKP_SLASH, KeyKP_ASTERISK, KeyKP_MINUS> Row0;
typedef boost::fusion::vector<KeyKP_7,     KeyKP_8,     KeyKP_9,        KeyKP_PLUS>  Row1;
typedef boost::fusion::vector<KeyKP_4,     KeyKP_5,     KeyKP_6,        KeyNONE>     Row2;
typedef boost::fusion::vector<KeyKP_1,     KeyKP_2,     KeyKP_3,        KeyKP_ENTER> Row3;
typedef boost::fusion::vector<KeyNONE,     KeyKP_0,     KeyKP_PERIOD,   KeyNONE>     Row4;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4> Matrix;

#endif
