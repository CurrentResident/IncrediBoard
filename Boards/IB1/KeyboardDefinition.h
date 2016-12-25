#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/container/vector.hpp>

#include "Board.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "UsbComponent.h"

typedef Board<
            boost::fusion::vector<
                MatrixComponent<Matrix>,
                UsbComponent
                >
            >
            KeyboardType;

#endif
