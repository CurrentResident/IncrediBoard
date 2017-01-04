#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "BoardState.h"
#include "FixedArray.h"
#include "KeyCodes.h"
#include "Platform.h"
#include "UsbInterface.h"

class Console
{
    public:
        Console() :
            m_outputReader(m_outputArray.end() - 1),
            m_outputWriter(m_outputArray.begin()),
            m_nextLiftoffTime(0),
            m_lastInputKeycode(0)
        {
            Reset();
        }

        bool AddInput(BoardState& io_state)
        {
            bool        commandEntered = false;
            std::size_t writerI        = 0;
            std::size_t readerI        = 0;

            uint8_t inputKeycode;
            uint8_t outputReportKeycode;

            for (; readerI < io_state.m_keyReportArray.size(); ++readerI)
            {
                inputKeycode        = io_state.m_keyReportArray[readerI];
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
                            m_consoleOutputReport.clear();
                            m_nextLiftoffTime = 0;

                            // TODO:  Lookup command, run it downstream.
                            m_inputArray.clear();

                            PushOutput('\n');
                            result = true;
                            commandEntered = true;
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

                        if (result and not commandEntered)
                        {
                            m_consoleOutputReport.PushElement(inputKeycode);
                            m_nextLiftoffTime = Platform::GetMsec() + 10;
                            ++writerI;
                        }
                    }
                }
                else
                {
                    ++writerI;
                }
            }

            if (0 < m_nextLiftoffTime and m_nextLiftoffTime < Platform::GetMsec())
            {
                m_consoleOutputReport.DeleteElement(m_consoleOutputReport[0]);
                m_nextLiftoffTime = (m_consoleOutputReport.size() > 0 ? m_nextLiftoffTime + 10 : 0);
            }

            io_state.m_keyReportArray = m_consoleOutputReport;
            io_state.m_modifiers      = 0;

            return commandEntered;
        }

        void Reset()
        {
            m_lastInputKeycode = 0;
            m_nextLiftoffTime = 0;
            m_inputArray.clear();
            m_outputArray.clear();
            m_outputReader = m_outputArray.end() - 1;
            m_outputWriter = m_outputArray.begin();
            m_consoleOutputReport.clear();
        }

        void PushOutput(const char c)
        {
            if (m_outputWriter == m_outputReader)
            {
                FlushOutput();
            }

            *m_outputWriter = c;

            m_outputWriter = AdvanceOutput(m_outputWriter);
        }

        void PushOutput(const char* i_out)
        {
            const char* outPtr = i_out;

            for (char c = *outPtr; c != '\0'; c = *outPtr)
            {
                ++outPtr;
                PushOutput(c);
            }
        }

        void FlushOutput()
        {
            BoardState::ReportType localReport;
            m_nextLiftoffTime = 0;

            for (OutputBuffer::iterator nextChar = AdvanceOutput(m_outputReader); nextChar != m_outputWriter; nextChar = AdvanceOutput(m_outputReader))
            {
                m_outputReader = nextChar;

                localReport[0] = CharToCode(*m_outputReader);
                m_nextLiftoffTime = Platform::GetMsec() + 10;

                while (m_nextLiftoffTime > Platform::GetMsec())
                {
                    UsbInterface::Process(localReport.Get(), 1, 0);
                }
            }
        }
/*
            // We always clear because the upstream matrix component could have pushed more codes
            // due to actual user input.
            //
            io_state.m_keyReportArray.clear();
            io_state.m_modifiers = 0;

            if (m_nextLiftoffTime > 0)
            {
                if (m_nextLiftoffTime < Platform::GetMsec())
                {
                    m_nextLiftoffTime = 0;
                }
                else
                {
                    io_state.m_keyReportArray.PushElement(CharToCode(*m_outputReader));
                }

                result = true;
            }
            else
            {
                if (not atEndOfOutput)
                {
                    result = true;
                    m_outputReader = nextChar;

                    io_state.m_keyReportArray.PushElement(CharToCode(*m_outputReader));
                    m_nextLiftoffTime = Platform::GetMsec() + 10;
                }
            }

            return result;
        }
*/
    private:

        typedef FixedArray<uint8_t, 3, 0> OutputBuffer;

        uint8_t CharToCode(uint8_t i_char)
        {
            uint8_t result = KEY_SPACE;

            if ('a' <= i_char and i_char <= 'z')
            {
                result = KEY_A + (i_char - 'a');
            }
            else if ('A' <= i_char and i_char <= 'Z')
            {
                result = KEY_A + (i_char - 'A');
            }
            else if ('1' <= i_char and i_char <= '9')
            {
                result = KEY_1 + (i_char - KEY_1);
            }
            else if ('0' == i_char)
            {
                result = KEY_0;
            }
            else if ('\n' == i_char)
            {
                result = KEY_ENTER;
            }

            return result;
        }

        Console::OutputBuffer::iterator AdvanceOutput(OutputBuffer::iterator i_iterator)
        {
            OutputBuffer::iterator result = i_iterator + 1;

            if (result == m_outputArray.end())
            {
                return m_outputArray.begin();
            }
            return result;
        }

        FixedArray<uint8_t, BoardState::ReportType::CAPACITY, 0> m_consoleOutputReport;   ///< Our outgoing USB report.

        FixedArray<uint8_t, 20, 0> m_inputArray;            ///< The actual input string
        OutputBuffer               m_outputArray;
        OutputBuffer::iterator     m_outputReader;
        OutputBuffer::iterator     m_outputWriter;
        unsigned long              m_nextLiftoffTime;
        uint8_t                    m_lastInputKeycode;
};

#endif
