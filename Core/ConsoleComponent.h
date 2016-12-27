#ifndef CONSOLE_COMPONENT_H_
#define CONSOLE_COMPONENT_H_

#include "BoardState.h"
#include "KeyCodes.h"

class ConsoleComponent
{
    public:

        ConsoleComponent() :
            m_consoleState (CONSOLE_OFF),
            m_magicSequenceWasActive(false)
        {
        }

        void Process(BoardState& io_state)
        {
            const bool magicSequenceIsActive = io_state.m_activeKeyTable[KEY_LEFT_CTRL] and
                                               io_state.m_activeKeyTable[KEY_RIGHT_CTRL] and
                                               io_state.m_activeKeyTable[KEY_P];

            const bool magicSequenceActivate = magicSequenceIsActive and not m_magicSequenceWasActive;

            m_magicSequenceWasActive = magicSequenceIsActive;

            switch (m_consoleState)
            {
                case CONSOLE_OFF:
                    if (magicSequenceActivate)
                    {
                        m_consoleState = CONSOLE_EMITTING_PROMPT;
                    }
                    break;

                case CONSOLE_EMITTING_PROMPT:

                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }
                    break;

                case CONSOLE_COLLECTING_INPUT:

                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }
                    break;

                case CONSOLE_EMITTING_OUTPUT:

                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }
                    break;

                default:
                    DeactivateConsole();
                    break;
            }
        }

    private:

        void DeactivateConsole()
        {
            m_consoleState = CONSOLE_OFF;

            //TODO: Clear output buffer
            //TODO: Throw away saved stack contexts
        }

        enum ConsoleStateEnum
        {
            CONSOLE_OFF,
            CONSOLE_EMITTING_PROMPT,
            CONSOLE_COLLECTING_INPUT,
            CONSOLE_EMITTING_OUTPUT
        };

        ConsoleStateEnum m_consoleState;
        bool             m_magicSequenceWasActive;
};

#endif
