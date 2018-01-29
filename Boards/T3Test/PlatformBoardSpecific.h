#ifndef INSIDE_PLATFORM_SPECIFIC_H_
#error "Do not include this file directly!!!"
#endif

#include <boost/utility/binary.hpp>

#include "Arduino.h"

namespace Platform
{
    // Needed by Board.
    typedef uint8_t InputElementType;

    template <uint8_t pin>
    void ConfigureRow()
    {
        // For ARM open drain outputs, LOW == asserted (connected to ground), HIGH == deasserted (open).
        // Start with open.
        digitalWriteFast(pin, HIGH);
        pinMode(pin, OUTPUT_OPENDRAIN);
    }

    inline void ConfigurePins()
    {
        ConfigureRow<5>();
        ConfigureRow<7>();

        pinMode(12, INPUT_PULLUP);
        pinMode(11, INPUT_PULLUP);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 2>(uint8_t (& o_inputs)[2])
    {
        o_inputs[0] = (digitalReadFast(12) == 0);
        o_inputs[1] = (digitalReadFast(11) == 0);
    }

    template <> inline void SetRow<0>  () { digitalWriteFast(5, LOW);  }
    template <> inline void ClearRow<0>() { digitalWriteFast(5, HIGH); }

    template <> inline void SetRow<1>  () { digitalWriteFast(7, LOW);  }
    template <> inline void ClearRow<1>() { digitalWriteFast(7, HIGH); }
}
