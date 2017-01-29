#ifndef CONSOLE_COMPONENT_H_
#define CONSOLE_COMPONENT_H_

#include "BoardState.h"
#include "Console.h"
#include "Decorators.h"
#include "KeyCodes.h"

class ConsoleComponent : NeedsAllComponents
{
    public:

        ConsoleComponent() :
            m_consoleState (CONSOLE_OFF),
            m_magicSequenceWasActive(false)
        {
        }

        template <typename ComponentCollectionType>
        void Process(BoardState& io_state, ComponentCollectionType& io_components)
        {
            const bool magicSequenceIsActive = io_state.m_activeKeyTable[KEY_LEFT_CTRL] and
                                               io_state.m_activeKeyTable[KEY_RIGHT_CTRL] and
                                               io_state.m_activeKeyTable[KEY_RIGHT_SHIFT];

            const bool magicSequenceActivate = magicSequenceIsActive and not m_magicSequenceWasActive;

            m_magicSequenceWasActive = magicSequenceIsActive;

            switch (m_consoleState)
            {
                case CONSOLE_OFF:
                    if (magicSequenceActivate)
                    {
                        m_consoleState = CONSOLE_PUSH_PROMPT;
                    }
                    break;

                case CONSOLE_PUSH_PROMPT:

                    m_console.PushOutput("IncrediBoard ");
                    m_consoleState = CONSOLE_EMITTING_PROMPT;
                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }

                    break;

                case CONSOLE_EMITTING_PROMPT:

                    m_console.FlushOutput();
                    m_consoleState = CONSOLE_COLLECTING_INPUT;

                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }
                    break;

                case CONSOLE_COLLECTING_INPUT:

                    if (m_console.AddInput(io_state))
                    {
                        m_consoleState = CONSOLE_EMITTING_OUTPUT;
                    }

                    if (magicSequenceActivate)
                    {
                        DeactivateConsole();
                    }
                    break;

                case CONSOLE_EMITTING_OUTPUT:

                    m_console.FlushOutput();
                    m_consoleState = CONSOLE_PUSH_PROMPT;

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
            m_console.Reset();
        }

        enum ConsoleStateEnum
        {
            CONSOLE_OFF,
            CONSOLE_PUSH_PROMPT,
            CONSOLE_EMITTING_PROMPT,
            CONSOLE_COLLECTING_INPUT,
            CONSOLE_EMITTING_OUTPUT
        };

        Console          m_console;
        ConsoleStateEnum m_consoleState;
        bool             m_magicSequenceWasActive;
};

#endif
