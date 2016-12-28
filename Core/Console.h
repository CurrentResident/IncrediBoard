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
            uint8_t inputCharacter = 0;
            std::size_t writerI = 0;
            std::size_t readerI = 0;

            uint8_t inputKeycode;
            uint8_t outputReportKeycode;

            for (; readerI < i_state.m_keyReportArray.size(); ++readerI)
            {
                inputKeycode        = i_state.m_keyReportArray[readerI];
                outputReportKeycode = m_consoleOutputReport[writerI];

                if (inputKeycode != outputReportKeycode)
                {
                    // Important details:  The key report array always has "new" keypresses show up at the end of
                    // the report.  When a key is released, the subsequent entries in the report are shifted down.

                    // Because key report array is a copy of our report from last time, if we see different values
                    // and our report is not 0, we know it is because the user lifted off the key.
                    //
                    // If it is 0, it is because they hit a new key.
                    if (outputReportKeycode != 0)
                    {
                        m_consoleOutputReport.DeleteElement(outputReportKeycode);
                    }
                    else
                    {
                        bool result = false;

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

                        if (result)
                        {
                            m_consoleOutputReport.PushElement(inputKeycode);
                            ++writerI;
                        }
                    }
                }
                else
                {
                    ++writerI;
                }
            }

            i_state.m_keyReportArray = m_consoleOutputReport;

            return false;
        }

        void Reset()
        {
            m_lastInputKeycode = 0;
            m_inputArray.clear();
            m_consoleOutputReport.clear();
        }

    private:

        FixedArray<uint8_t, BoardState::ReportType::CAPACITY, 0> m_consoleOutputReport;   ///< Our outgoing USB report.

        FixedArray<uint8_t, 20, 0> m_inputArray;            ///< The actual input string
        uint8_t                    m_lastInputKeycode;
};

#endif
