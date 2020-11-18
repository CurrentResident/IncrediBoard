#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/container.hpp>

#include "Board.h"
#include "BootloaderJumpComponent.h"
#include "ConsoleComponent.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "UsbComponent.h"

typedef Board
        <
            boost::fusion::vector
            <
                MatrixComponent<Matrix>,
                BootloaderJumpComponent,
                ConsoleComponent,
                UsbComponent
            >
        >
        KeyboardType;

#endif
