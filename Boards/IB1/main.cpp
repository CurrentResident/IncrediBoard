
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

        enum StateEnum
        {
            IDLE,
            FLASH_ON,
            FLASH_OFF,
            WAITING
        };

        unsigned long   m_nextTime;
        uint8_t         m_pulseCount;
        StateEnum       m_state;

    public:
        Flasher(): m_nextTime(0),
                   m_pulseCount(0),
                   m_state(IDLE) { }

        void SetPulseCount(uint8_t i_count)
        {
            if (m_state == IDLE)
            {
                m_pulseCount = i_count;
            }
        }

        void StrobeAndSetState(StateEnum i_state)
        {
            m_state = i_state;
            PIND |= (1 << 6);
            m_nextTime += 100;
        }

        void Process(unsigned long now)
        {
            switch (m_state)
            {
                case IDLE:

                    if (m_pulseCount > 0)
                    {
                        m_nextTime = now;
                        StrobeAndSetState(FLASH_ON);
                    }
                    break;

                case FLASH_ON:

                    if (m_nextTime < now)
                    {
                        StrobeAndSetState(FLASH_OFF);
                    }
                    break;

                case FLASH_OFF:

                    if (m_nextTime < now)
                    {
                        --m_pulseCount;
                        if (m_pulseCount == 0)
                        {
                            m_state     = WAITING;
                            m_nextTime += 1000;
                        }
                        else
                        {
                            StrobeAndSetState(FLASH_ON);
                        }
                    }
                    break;

                case WAITING:

                    if (m_nextTime < now)
                    {
                        m_state = IDLE;
                    }
                    break;

                default:
                    m_state = IDLE;
                    break;
            }
/*
            if (now > m_nextTime)
            {
                m_nextTime += 500;
                PIND |= (1 << 6);
            }
*/
        }
};

int main (void)
{
    Platform::Init();
    UsbInterface::Init();

    Platform::DelayMicrosecs<1000>();

    Flasher flash;
    unsigned long startTime;
    unsigned long endTime;
    while(1)
    {
        startTime = Platform::GetMsec();
        keyboard.Process();
        endTime = Platform::GetMsec();

        flash.SetPulseCount(static_cast<uint8_t>(endTime - startTime));
        flash.Process(endTime);
    }

    return 0;
}
