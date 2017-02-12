
#include "KeyboardDefinition.h"
#include "UsbInterface.h"
#include "Platform.h"

namespace
{
    KeyboardType keyboard;
}

int main (void)
{
    Platform::Init();
    UsbInterface::Init();

    keyboard.Init();

    Platform::DelayMillisecs<1000>();

    while(1)
    {
        keyboard.Process();
    }

    return 0;
}
