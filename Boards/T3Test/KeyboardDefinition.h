#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/algorithm.hpp>   // Needed to ensure the F template parameters don't conflict with Arduino's
#include <boost/fusion/container.hpp>   // F() macro

#include "Board.h"
#include "BootloaderJumpComponent.h"
#include "ConsoleComponent.h"
#include "FlasherComponent.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "UsbComponent.h"
#include "UsbMouseComponent.h"

typedef Board
        <
            boost::fusion::vector
            <
                MatrixComponent<Matrix>,
                BootloaderJumpComponent,
                UsbMouseComponent,
                ConsoleComponent,
                FlasherComponent,
                UsbComponent
            >
        >
        KeyboardType;

#endif
