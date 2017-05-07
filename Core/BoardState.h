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

    void ChangeKeyState(const uint8_t i_key, const uint8_t i_value)
    {
        m_activeKeyTable[i_key] = i_value;

        switch (i_value)
        {
            case 0:
                m_keyReportArray.DeleteElement(i_key);
                break;
            default:
                m_keyReportArray.PushElement(i_key);
                break;
        }
    }

    void ChangeModifierState(const uint8_t i_key,
                             const uint8_t i_modifier,
                             const uint8_t i_value)
    {
        m_activeKeyTable[i_key] = i_value;

        switch (i_value)
        {
            case 0:
                m_modifiers &= ~i_modifier;
                break;
            default:
                m_modifiers |= i_modifier;
                break;
        }
    }

    void SetFunctionKey(const uint8_t i_state)
    {
        m_functionKey = i_state;
    }
};

#endif
