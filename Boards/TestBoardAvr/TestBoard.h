#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include <boost/fusion/include/vector.hpp>

#include "Key.h"
#include "KeyValues.h"

#include "Row.h"

typedef boost::fusion::vector<KeyA,     KeyE, KeyE,     KeyNONE,            KeyA> Row0Keys;
typedef boost::fusion::vector<KeyB,     KeyF, KeyF,     KeyMOD_LEFT_SHIFT,  KeyB> Row1Keys;
typedef boost::fusion::vector<KeyC,     KeyG, KeyNONE,  KeyNONE,            KeyC> Row2Keys;
typedef boost::fusion::vector<KeyD,     KeyH, KeyNONE,  KeyH,               KeyD> Row3Keys;
typedef boost::fusion::vector<KeyNONE,  KeyI, KeyNONE,  KeyI,               KeyE> Row4Keys;

typedef Row <Platform::SetRow<0>, Row0Keys, Platform::ResetRow<0> > Row0;
typedef Row <Platform::SetRow<1>, Row1Keys, Platform::ResetRow<1> > Row1;
typedef Row <Platform::SetRow<2>, Row2Keys, Platform::ResetRow<2> > Row2;
typedef Row <Platform::SetRow<3>, Row3Keys, Platform::ResetRow<3> > Row3;
typedef Row <Platform::SetRow<4>, Row4Keys, Platform::ResetRow<4> > Row4;

typedef boost::fusion::vector<Row0, Row1, Row2, Row3, Row4> Matrix;

/*
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
*/

#endif
