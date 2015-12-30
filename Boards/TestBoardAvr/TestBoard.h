#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include <boost/fusion/include/vector.hpp>

#include "Key.h"
#include "KeyValues.h"

#include "Column.h"

typedef boost::fusion::vector<KeyA,    KeyB,              KeyC,    KeyD,    KeyNONE> Column1Keys;
typedef boost::fusion::vector<KeyE,    KeyF,              KeyG,    KeyH,    KeyI>    Column2Keys;
typedef boost::fusion::vector<KeyE,    KeyF,              KeyNONE, KeyNONE, KeyNONE> Column3Keys;
typedef boost::fusion::vector<KeyNONE, KeyMOD_LEFT_SHIFT, KeyNONE, KeyH,    KeyI>    Column4Keys;
typedef boost::fusion::vector<KeyA,    KeyB,              KeyC,    KeyD,    KeyE>    Column5Keys;

typedef Column <Platform::SetColumn<0>, Column1Keys, Platform::ResetColumn<0> > Column1;
typedef Column <Platform::SetColumn<1>, Column2Keys, Platform::ResetColumn<1> > Column2;
typedef Column <Platform::SetColumn<2>, Column3Keys, Platform::ResetColumn<2> > Column3;
typedef Column <Platform::SetColumn<3>, Column4Keys, Platform::ResetColumn<3> > Column4;
typedef Column <Platform::SetColumn<4>, Column5Keys, Platform::ResetColumn<4> > Column5;

typedef boost::fusion::vector<Column1, Column2, Column3, Column4, Column5> Matrix;

#endif
