#ifndef BOARD_CONTROLLER_H_
#define BOARD_CONTROLLER_H_

#include <stdint.h>

#include "FixedArray.h"

class BoardController
{
    private:

        uint8_t m_modifiers;

        // TODO: NKRO.  Until then, keep things really simple...

        FixedArray<uint8_t, 10, 0> m_testArray;

    public:

        BoardController() :
            m_modifiers (0)
        {
        }

        void SetModifier(const uint8_t i_modifier)
        {
            m_modifiers |= i_modifier;
        }

        void ClearModifier(const uint8_t i_modifier)
        {
            m_modifiers &= ~i_modifier;
        }
/*
        void SetKey(const uint8_t i_key)
        {
            if 
        }
*/
};

#endif
