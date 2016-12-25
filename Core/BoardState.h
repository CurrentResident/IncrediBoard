#ifndef BOARD_STATE_H_
#define BOARD_STATE_H_

struct BoardState
{
    // Keyboard state
    // ------------------------------------------------------------------------------
    uint8_t m_functionKey;                ///< The function key state.
    uint8_t m_modifiers;                  ///< USB modifier report byte

    /// USB report array.
    /// Only track up to 10 keys because really, how often do people have more than 10 keys pressed at a time?
    /// Also, I don't know how I want to deal with NKRO yet.
    FixedArray<uint8_t, 10, 0> m_keyReportArray;

    /// Key truth state.
    FixedArray<uint8_t, 256, 0> m_activeKeyTable;
};

#endif
