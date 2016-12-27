#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "BoardState.h"
#include "FixedArray.h"
#include "KeyCodes.h"

class Console
{
    public:
        Console() :
            m_lastInputKeycode(0)
        {
        }

        bool AddInput(BoardState& i_state)
        {
            bool result = false;
            const uint8_t inputKeycode = i_state.m_keyReportArray[0];

            if (inputKeycode != m_lastInputKeycode)
            {
                if (inputKeycode != KEY_NONE)
                {
                    // Special knowledge: USB keycodes are ranged from a thru z, 1 thru 9, like ASCII, but 0 is not.
                    if (KEY_A <= inputKeycode and inputKeycode <= KEY_Z)
                    {
                        result = m_inputArray.PushElement('a' + (inputKeycode - KEY_A));
                    }
                    else if (inputKeycode == KEY_ENTER or inputKeycode == KEY_KP_ENTER)
                    {
                        // TODO:  Lookup and dispatch command.
                        m_inputArray.clear();
                        result = true;
                    }
                    else if (inputKeycode == KEY_BACKSPACE)
                    {
                        result = m_inputArray.DeleteLastElement();
                    }
                    else if (inputKeycode == KEY_SPACE)
                    {
                        result = m_inputArray.PushElement(' ');
                    }
                    else if (KEY_1 <= inputKeycode and inputKeycode <= KEY_9)
                    {
                        result = m_inputArray.PushElement('1' + (inputKeycode - KEY_1));
                    }
                    else if (KEY_KP_1 <= inputKeycode and inputKeycode <= KEY_KP_9)
                    {
                        result = m_inputArray.PushElement('1' + (inputKeycode - KEY_KP_1));
                    }
                    else if (inputKeycode == KEY_0 or inputKeycode == KEY_KP_0)
                    {
                        result = m_inputArray.PushElement('0');
                    }
                    else
                    {
                        i_state.m_keyReportArray.DeleteElement(i_state.m_keyReportArray[0]);
                        result = true;
                    }

                    if (not result)
                    {
                        i_state.m_keyReportArray.clear();
                    }
                }

                m_lastInputKeycode = inputKeycode;
            }

            return result;
        }

        void Reset()
        {
            m_lastInputKeycode = 0;
            m_inputArray.clear();
        }

    private:

        FixedArray<uint8_t, 20, 0> m_inputArray;
        uint8_t                    m_lastInputKeycode;
};

#endif
