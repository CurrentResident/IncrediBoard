
#include "KeyboardDefinition.h"
#include "Platform.h"
#include "UsbInterface.h"

namespace
{
    KeyboardType keyboard;
}

int main (void)
{
    Platform::Init();
    UsbInterface::Init();

    Platform::DelayMicrosecs<1000000>();

    while(1)
    {
        keyboard.Process();
    }

    return 0;
}
