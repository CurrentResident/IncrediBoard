#ifndef FLASHER_COMPONENT_H_
#define FLASHER_COMPONENT_H_

#include <stdint.h>

#include "BoardState.h"
#include "KeyCodes.h"
#include "Platform.h"

class FlasherComponent
{
    public:

        FlasherComponent() :
            m_flashState(WAITING_FOR_KEY),
            m_flashCount(0),
            m_nextFlash (0)
        {
            pinMode(LED_PIN, OUTPUT);        // Integrated LED.
            digitalWriteFast(LED_PIN, LOW);
        }

        void Process(BoardState& io_state)
        {
            switch (m_flashState)
            {
                case WAITING_FOR_KEY:

                    if (io_state.m_activeKeyTable[IB_KEY_A])
                    {
                        m_flashCount = 1;
                        m_flashState = TURN_ON;
                    }
                    else if (io_state.m_activeKeyTable[IB_KEY_B])
                    {
                        m_flashCount = 2;
                        m_flashState = TURN_ON;
                    }
                    else if (io_state.m_activeKeyTable[IB_KEY_C])
                    {
                        m_flashCount = 3;
                        m_flashState = TURN_ON;
                    }
                    else if (io_state.m_activeKeyTable[IB_KEY_D])
                    {
                        m_flashCount = 4;
                        m_flashState = TURN_ON;
                    }
                    break;

                case TURN_ON:

                    if (m_flashCount > 0)
                    {
                        digitalWriteFast(LED_PIN, HIGH);

                        m_flashState = KEEP_LED_ON;
                        m_nextFlash  = Platform::GetMsec() + 500;
                    }
                    else
                    {
                        m_flashState = WAITING_FOR_KEY;
                    }
                    break;

                case KEEP_LED_ON:

                    if (Platform::GetMsec() > m_nextFlash)
                    {
                        m_flashState = TURN_OFF;
                    }
                    break;

                case TURN_OFF:

                    digitalWriteFast(LED_PIN, LOW);

                    --m_flashCount;

                    if (m_flashCount > 0)
                    {
                        m_flashState = WAIT_FOR_NEXT_FLASH;
                        m_nextFlash  = Platform::GetMsec() + 200;
                    }
                    else
                    {
                        m_flashState = WAITING_FOR_KEY;
                    }
                    break;

                case WAIT_FOR_NEXT_FLASH:

                    if (Platform::GetMsec() > m_nextFlash)
                    {
                        m_flashState = TURN_ON;
                    }
                    break;

                default:
                    m_flashState = WAITING_FOR_KEY;
                    break;
            }
        }

    private:

        enum FlashStateEnum
        {
            WAITING_FOR_KEY,
            TURN_ON,
            KEEP_LED_ON,
            TURN_OFF,
            WAIT_FOR_NEXT_FLASH,
        };

        static const uint8_t LED_PIN = 13;

        FlashStateEnum  m_flashState;
        uint8_t         m_flashCount;
        unsigned long   m_nextFlash;
};

#endif
