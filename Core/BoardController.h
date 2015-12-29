#ifndef BOARD_CONTROLLER_H_
#define BOARD_CONTROLLER_H_

#include <stdint.h>

class BoardController
{
    private:
        BoardController() :
            m_modifiers(0)
        {
        }

        uint8_t m_modifiers;

        static BoardController s_instance;

    public:
        // So, I wanted to do a Meyers singleton, but the compiler is required to insert synchronization code
        // for runtime initialization of local statics, which Meyers singletons need.  This is problematic on
        // avr-gcc, which does not provide the sync primitives.  So I'm copping out with a static member variable,
        // which works without sync, is less lazy about initialization, but is more vulnerable to elaboration order
        // issues.  In this case, I am not worried about that because I know that it won't be accessed during
        // elaboration.
        //
        // static BoardController& Get()
        // {
        //     static BoardController s_instance;
        //     return s_instance;
        // }

        static BoardController& Get()
        {
            return s_instance;
        }

        void SetModifier(const uint8_t i_modifier)
        {
            m_modifiers |= i_modifier;
        }

        void ClearModifier(const uint8_t i_modifier)
        {
            m_modifiers &= ~i_modifier;
        }
};

#endif
