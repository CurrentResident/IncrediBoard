#ifndef KEY_VALUES_LUFA_H_
#define KEY_VALUES_LUFA_H_

#include "Key.h"

#define KEY_NONE    0

#define KEY_A		4
#define KEY_B		5
#define KEY_C		6
#define KEY_D		7
#define KEY_E		8
#define KEY_F		9
#define KEY_G		10
#define KEY_H		11
#define KEY_I		12


typedef Key<0>     KeyNONE;

typedef Key<KEY_A> KeyA;
typedef Key<KEY_B> KeyB;
typedef Key<KEY_C> KeyC;
typedef Key<KEY_D> KeyD;
typedef Key<KEY_E> KeyE;
typedef Key<KEY_F> KeyF;
typedef Key<KEY_G> KeyG;
typedef Key<KEY_H> KeyH;
typedef Key<KEY_I> KeyI;

#endif
