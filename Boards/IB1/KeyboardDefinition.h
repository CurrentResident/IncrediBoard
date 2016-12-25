#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/include/vector.hpp>

#include "Board.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "UsbComponent.h"

typedef Board<
            boost::fusion::vector<
                MatrixComponent<Matrix>,
                UsbComponent
                >
            KeyboardType;

#endif
