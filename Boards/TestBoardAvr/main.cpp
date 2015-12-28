
#include "PlatformTeensy.h"

#include "TestBoard.h"

#include "Board.h"

namespace
{
    Board<Matrix> keyboard;
}

int main (void)
{
    Platform::Init();

    keyboard.Process();
    keyboard.Process();

    return 0;
}
