#ifndef IB1_MATRIX_H_
#define IB1_MATRIX_H_

#include <boost/fusion/include/vector.hpp>

#include "KeyClasses.h"

typedef boost::fusion::vector<KeyA, KeyC> Row0;
typedef boost::fusion::vector<KeyB, KeyD> Row1;

typedef boost::fusion::vector<Row0, Row1> Matrix;

#endif
