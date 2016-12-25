#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/container.hpp>

#include "Board.h"
#include "BootloaderJumpComponent.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "UsbComponent.h"
#include "UsbMouseComponent.h"

typedef Board<
            boost::fusion::vector<
                MatrixComponent<Matrix>,
                BootloaderJumpComponent,
                UsbMouseComponent,
                UsbComponent
                >
            >
            KeyboardType;

#endif
