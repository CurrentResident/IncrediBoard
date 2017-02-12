#ifndef BOOTLOADER_JUMP_COMPONENT_H_
#define BOOTLOADER_JUMP_COMPONENT_H_

#include "BoardState.h"
#include "KeyCodes.h"
#include "Platform.h"

class BootloaderJumpComponent
{
    public:

        BootloaderJumpComponent() :
            m_isRebootingToBootloader (false),
            m_bootLoaderJumpTime      (0)
        {
        }

        void Process(BoardState& io_state)
        {
            // Four-finger salute to put the keyboard into the bootloader.  Not concerned about latching this.
            // Once all four keys are down, the keyboard reports all keys cleared/reset, and the reboot happens
            // some amount time after the keys are physically released, much like a proper reset button's behavior.
            if (io_state.m_activeKeyTable[IB_KEY_LEFT_CTRL]  and
                io_state.m_activeKeyTable[IB_KEY_LEFT_SHIFT] and
                io_state.m_activeKeyTable[IB_KEY_TAB]        and
                io_state.m_activeKeyTable[IB_KEY_BACKSPACE])
            {
                // Don't jump immediately.  Allow a second to pass so that we can reset the key reports.
                // Otherwise the OS thinks the board is just holding down the keys when really it's in the
                // bootloader.
                m_isRebootingToBootloader = true;
                m_bootLoaderJumpTime      = Platform::GetMsec() + 1000;
            }

            if (m_isRebootingToBootloader)
            {
                io_state.m_keyReportArray.clear();
                io_state.m_modifiers = 0;

                if (Platform::GetMsec() > m_bootLoaderJumpTime)
                {
                    // No return!
                    Platform::JumpToBootloader();
                }
            }
        }

    private:

        // Reboot state
        // ------------------------------------------------------------------------------
        bool          m_isRebootingToBootloader;    ///< Indicates we're going to the bootloader shortly.
        unsigned long m_bootLoaderJumpTime;         ///< The time in msec that we'll make the actual jump.
};

#endif
