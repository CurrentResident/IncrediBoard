
#include "PlatformTeensy.h"

#include "Matrix.h"

#include "Board.h"

#include "UsbInterface.h"

namespace
{
    Board<Matrix> keyboard;
}


int main (void)
{
    Platform::Init();
    UsbInterface::Init();

    while(1)
    {
        keyboard.Process();
    }

    return 0;
}
