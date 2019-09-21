#ifndef INSIDE_PLATFORM_SPECIFIC_H_
#error "Do not include this file directly!!!"
#endif

#include <boost/utility/binary.hpp>

#include "Platform.h"

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
        ConfigureRow< 2>();
        ConfigureRow< 3>();
        ConfigureRow<11>();
        ConfigureRow<12>();
        ConfigureRow< 1>();
        ConfigureRow<23>();

        pinMode(20, INPUT_PULLUP);
        pinMode(21, INPUT_PULLUP);
        pinMode(22, INPUT_PULLUP);
        pinMode( 4, INPUT_PULLUP);
        pinMode( 5, INPUT_PULLUP);
        pinMode( 6, INPUT_PULLUP);
        pinMode( 7, INPUT_PULLUP);
        pinMode( 8, INPUT_PULLUP);
        pinMode( 9, INPUT_PULLUP);
        pinMode(10, INPUT_PULLUP);
        pinMode(19, INPUT_PULLUP);
        pinMode(18, INPUT_PULLUP);
        pinMode(17, INPUT_PULLUP);
        pinMode(16, INPUT_PULLUP);
        pinMode(15, INPUT_PULLUP);
        pinMode(14, INPUT_PULLUP);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 16>(uint8_t (& o_inputs)[16])
    {
        o_inputs[0]  = (digitalReadFast(20) == 0);
        o_inputs[1]  = (digitalReadFast(21) == 0);
        o_inputs[2]  = (digitalReadFast(22) == 0);
        o_inputs[3]  = (digitalReadFast( 4) == 0);
        o_inputs[4]  = (digitalReadFast( 5) == 0);
        o_inputs[5]  = (digitalReadFast( 6) == 0);
        o_inputs[6]  = (digitalReadFast( 7) == 0);
        o_inputs[7]  = (digitalReadFast( 8) == 0);
        o_inputs[8]  = (digitalReadFast( 9) == 0);
        o_inputs[9]  = (digitalReadFast(10) == 0);
        o_inputs[10] = (digitalReadFast(19) == 0);
        o_inputs[11] = (digitalReadFast(18) == 0);
        o_inputs[12] = (digitalReadFast(17) == 0);
        o_inputs[13] = (digitalReadFast(16) == 0);
        o_inputs[14] = (digitalReadFast(15) == 0);
        o_inputs[15] = (digitalReadFast(14) == 0);
    }

    template <> inline void SetRow<0>  () { digitalWriteFast( 2, LOW);  }
    template <> inline void ClearRow<0>() { digitalWriteFast( 2, HIGH); }
    template <> inline void SetRow<1>  () { digitalWriteFast( 3, LOW);  }
    template <> inline void ClearRow<1>() { digitalWriteFast( 3, HIGH); }
    template <> inline void SetRow<2>  () { digitalWriteFast(11, LOW);  }
    template <> inline void ClearRow<2>() { digitalWriteFast(11, HIGH); }
    template <> inline void SetRow<3>  () { digitalWriteFast(12, LOW);  }
    template <> inline void ClearRow<3>() { digitalWriteFast(12, HIGH); }
    template <> inline void SetRow<4>  () { digitalWriteFast( 1, LOW);  }
    template <> inline void ClearRow<4>() { digitalWriteFast( 1, HIGH); }
    template <> inline void SetRow<5>  () { digitalWriteFast(23, LOW);  }
    template <> inline void ClearRow<5>() { digitalWriteFast(23, HIGH); }
}
