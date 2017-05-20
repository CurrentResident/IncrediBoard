#ifndef KEYBOARD_DEFINITION_H_
#define KEYBOARD_DEFINITION_H_

#include <boost/fusion/container.hpp>

#include "Board.h"
#include "BootloaderJumpComponent.h"
#include "ConsoleComponent.h"
#include "KeyClasses.h"
#include "Matrix.h"
#include "MatrixComponent.h"
#include "SuperModifier.h"
#include "UsbComponent.h"
#include "UsbMouseComponent.h"

typedef Board
        <
            boost::fusion::vector
            <
                MatrixComponent<Matrix>,
                SuperModifierComponent<boost::fusion::vector<SuperModifier::Keys<KeyLSHIFT, boost::fusion::vector<KeyLSHIFT, KeyLEFT_BRACE> > > >,
                BootloaderJumpComponent,
                UsbMouseComponent,
                ConsoleComponent,
                UsbComponent
            >
        >
        KeyboardType;

#endif
