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

        uint8_t       m_modifiers;                  ///< USB modifier report byte
        bool          m_isRebootingToBootloader;    ///< Indicates we're going to the bootloader shortly.
        unsigned long m_bootLoaderJumpTime;         ///< The time in msec that we'll make the actual jump.

        // TODO: NKRO.  Until then, keep things really simple...

        /// USB report array.
        /// Only track up to 10 keys because really, how often do people have more than 10 keys pressed at a time?
        /// Also, I don't know how I want to deal with NKRO yet.
        FixedArray<uint8_t, 10, 0> m_keyReportArray;

        /// Key truth state.
        FixedArray<uint8_t, 256, 0> m_activeKeyTable;

    public:

        BoardController() :
            m_modifiers               (0),
            m_isRebootingToBootloader (false),
            m_bootLoaderJumpTime      (0)
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

            // Four-finger salute to put the keyboard into the bootloader.  Not concerned about latching this.
            // Once all four keys are down, the keyboard reports all keys cleared/reset, and the reboot happens
            // some amount time after the keys are physically released, much like a proper reset button's behavior.
            if (m_activeKeyTable[KEY_LEFT_CTRL]  and
                m_activeKeyTable[KEY_LEFT_SHIFT] and
                m_activeKeyTable[KEY_TAB]        and
                m_activeKeyTable[KEY_BACKSPACE])
            {
                // Don't jump immediately.  Allow a second to pass so that we can reset the key reports.
                // Otherwise the OS thinks the board is just holding down the keys when really it's in the
                // bootloader.
                m_isRebootingToBootloader = true;
                m_bootLoaderJumpTime      = Platform::GetMsec() + 1000;
            }

            if (m_isRebootingToBootloader)
            {
                m_keyReportArray.clear();
                m_modifiers = 0;

                if (Platform::GetMsec() > m_bootLoaderJumpTime)
                {
                    // No return!
                    Platform::JumpToBootloader();
                }
            }

            UsbInterface::Process(m_keyReportArray.Get(),
                                  m_keyReportArray.size(),
                                  m_modifiers);
        }
};

#endif
