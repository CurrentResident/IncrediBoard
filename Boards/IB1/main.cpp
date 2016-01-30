
#include "PlatformTeensy.h"

#include "Matrix.h"

#include "Board.h"

#include "UsbInterface.h"

namespace
{
    Board<Matrix> keyboard;
}

class Flasher
{
    private:
        unsigned long m_nextTime;

    public:
        Flasher(): m_nextTime(0) { }

        void Process()
        {
            unsigned long now = Platform::GetMsec();
            if (now > m_nextTime)
            {
                m_nextTime += 500;
                PIND |= (1 << 6);
            }
        }
};

int main (void)
{
    Platform::Init();
    UsbInterface::Init();

    Platform::DelayMicrosecs<1000000>();

    Flasher flash;
    while(1)
    {
        keyboard.Process();
        //flash.Process();
    }

    return 0;
}
