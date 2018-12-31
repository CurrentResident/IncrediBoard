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
        ConfigureRow<10>();
        ConfigureRow<11>();
        ConfigureRow<14>();
        ConfigureRow<12>();
        ConfigureRow<16>();
        ConfigureRow<15>();

        pinMode(0,  INPUT_PULLUP);
        pinMode(1,  INPUT_PULLUP);
        pinMode(2,  INPUT_PULLUP);
        pinMode(3,  INPUT_PULLUP);
        pinMode(4,  INPUT_PULLUP);
        pinMode(5,  INPUT_PULLUP);
        pinMode(6,  INPUT_PULLUP);
        pinMode(7,  INPUT_PULLUP);
        pinMode(23, INPUT_PULLUP);
        pinMode(22, INPUT_PULLUP);
        pinMode(21, INPUT_PULLUP);
        pinMode(20, INPUT_PULLUP);
        pinMode(8,  INPUT_PULLUP);
        pinMode(9,  INPUT_PULLUP);
        pinMode(19, INPUT_PULLUP);
        pinMode(18, INPUT_PULLUP);
        pinMode(17, INPUT_PULLUP);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 17>(uint8_t (& o_inputs)[17])
    {
        o_inputs[0]  = (digitalReadFast(0) == 0);
        o_inputs[1]  = (digitalReadFast(1) == 0);
        o_inputs[2]  = (digitalReadFast(2) == 0);
        o_inputs[3]  = (digitalReadFast(3) == 0);
        o_inputs[4]  = (digitalReadFast(4) == 0);
        o_inputs[5]  = (digitalReadFast(5) == 0);
        o_inputs[6]  = (digitalReadFast(6) == 0);
        o_inputs[7]  = (digitalReadFast(7) == 0);
        o_inputs[8]  = (digitalReadFast(23) == 0);
        o_inputs[9]  = (digitalReadFast(22) == 0);
        o_inputs[10] = (digitalReadFast(21) == 0);
        o_inputs[11] = (digitalReadFast(20) == 0);
        o_inputs[12] = (digitalReadFast(8) == 0);
        o_inputs[13] = (digitalReadFast(9) == 0);
        o_inputs[14] = (digitalReadFast(19) == 0);
        o_inputs[15] = (digitalReadFast(18) == 0);
        o_inputs[16] = (digitalReadFast(17) == 0);
    }

    template <> inline void SetRow<0>  () { digitalWriteFast(10, LOW);  }
    template <> inline void ClearRow<0>() { digitalWriteFast(10, HIGH); }
    template <> inline void SetRow<1>  () { digitalWriteFast(11, LOW);  }
    template <> inline void ClearRow<1>() { digitalWriteFast(11, HIGH); }
    template <> inline void SetRow<2>  () { digitalWriteFast(14, LOW);  }
    template <> inline void ClearRow<2>() { digitalWriteFast(14, HIGH); }
    template <> inline void SetRow<3>  () { digitalWriteFast(12, LOW);  }
    template <> inline void ClearRow<3>() { digitalWriteFast(12, HIGH); }
    template <> inline void SetRow<4>  () { digitalWriteFast(16, LOW);  }
    template <> inline void ClearRow<4>() { digitalWriteFast(16, HIGH); }
    template <> inline void SetRow<5>  () { digitalWriteFast(15, LOW);  }
    template <> inline void ClearRow<5>() { digitalWriteFast(15, HIGH); }
}
