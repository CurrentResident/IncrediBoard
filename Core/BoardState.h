#ifndef BOARD_STATE_H_
#define BOARD_STATE_H_

#include <stdint.h>

#include "FixedArray.h"

struct BoardState
{
    // Keyboard state
    // ------------------------------------------------------------------------------
    uint8_t m_functionKey;                ///< The function key state.
    uint8_t m_modifiers;                  ///< USB modifier report byte

    /// USB report array.
    /// Only track up to 10 keys because really, how often do people have more than 10 keys pressed at a time?
    /// Also, I don't know how I want to deal with NKRO yet.
    typedef FixedArray<uint8_t, 10, 0> ReportType;
    ReportType m_keyReportArray;

    /// Key truth state.
    FixedArray<uint8_t, 256, 0> m_activeKeyTable;

    BoardState() :
        m_functionKey(0),
        m_modifiers  (0)
    {
    }

    // The following template parameters can be changed to function parameters to get a decent code-size savings.

    template <uint8_t T_KEY_CODE>
    void ChangeKeyState(const uint8_t i_value)
    {
        m_activeKeyTable[T_KEY_CODE] = i_value;

        switch (i_value)
        {
            case 0:
                m_keyReportArray.DeleteElement(T_KEY_CODE);
                break;
            default:
                m_keyReportArray.PushElement(T_KEY_CODE);
                break;
        }
    }

    template <uint8_t T_KEY_CODE, uint8_t T_MODIFIER>
    void ChangeModifierState(const uint8_t i_value)
    {
        m_activeKeyTable[T_KEY_CODE] = i_value;

        switch (i_value)
        {
            case 0:
                m_modifiers &= ~T_MODIFIER;
                break;
            default:
                m_modifiers |= T_MODIFIER;
                break;
        }
    }

    void SetFunctionKey(const uint8_t i_state)
    {
        m_functionKey = i_state;
    }
};

#endif
