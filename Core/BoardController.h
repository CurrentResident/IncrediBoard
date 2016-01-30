#ifndef BOARD_CONTROLLER_H_
#define BOARD_CONTROLLER_H_

#include <stdint.h>

#include "FixedArray.h"
#include "KeyCodes.h"
#include "Platform.h"
#include "UsbInterface.h"

class BoardController
{
    private:

        uint8_t m_modifiers;

        // TODO: NKRO.  Until then, keep things really simple...

        // Only track up to 10 keys because really, how often do people have more than 10 keys pressed at a time?
        FixedArray<uint8_t, 10, 0> m_keyReportArray;

        FixedArray<uint8_t, 256, 0> m_activeKeyTable;

    public:

        BoardController() :
            m_modifiers (0)
        {
        }

        void SetActive(const uint8_t i_key, const uint8_t i_value)
        {
            m_activeKeyTable[i_key] = i_value;
            // TODO:  Diagnostic flash?  PIND |= (1 << 6);
        }

        void SetModifier(const uint8_t i_modifier)
        {
            m_modifiers |= i_modifier;
        }

        void ClearModifier(const uint8_t i_modifier)
        {
            m_modifiers &= ~i_modifier;
        }

        void SetKey(const uint8_t i_key)
        {
            m_keyReportArray.PushElement(i_key);
        }

        void ClearKey(const uint8_t i_key)
        {
            m_keyReportArray.DeleteElement(i_key);
        }

        void Process()
        {
            //TODO:  Fancy features?
            //

            // TODO: Carve features off into a generic fusion collection defined in board-specific area.

            if (m_activeKeyTable[KEY_LEFT_CTRL]  and
                m_activeKeyTable[KEY_LEFT_SHIFT] and
                m_activeKeyTable[KEY_TAB]        and
                m_activeKeyTable[KEY_BACKSPACE])
            {
                Platform::JumpToBootloader();
            }

            UsbInterface::Process(m_keyReportArray.Get(),
                                  m_keyReportArray.size(),
                                  m_modifiers);
        }
};

#endif
