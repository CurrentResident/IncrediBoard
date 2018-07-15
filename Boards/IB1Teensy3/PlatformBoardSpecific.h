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
        ConfigureRow<23>();
        ConfigureRow<45>();
        ConfigureRow<44>();
        ConfigureRow<38>();
        ConfigureRow<22>();
        ConfigureRow<21>();

        pinMode(27, INPUT_PULLUP);
        pinMode(0,  INPUT_PULLUP);
        pinMode(1,  INPUT_PULLUP);
        pinMode(2,  INPUT_PULLUP);
        pinMode(3,  INPUT_PULLUP);
        pinMode(4,  INPUT_PULLUP);
        pinMode(5,  INPUT_PULLUP);
        pinMode(7,  INPUT_PULLUP);
        pinMode(8,  INPUT_PULLUP);
        pinMode(9,  INPUT_PULLUP);
        pinMode(10, INPUT_PULLUP);
        pinMode(11, INPUT_PULLUP);
        pinMode(12, INPUT_PULLUP);
        pinMode(13, INPUT_PULLUP);
        pinMode(14, INPUT_PULLUP);
        pinMode(15, INPUT_PULLUP);
        pinMode(16, INPUT_PULLUP);
        pinMode(20, INPUT_PULLUP);
        pinMode(39, INPUT_PULLUP);
        pinMode(43, INPUT_PULLUP);
        pinMode(17, INPUT_PULLUP);        
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 21>(uint8_t (& o_inputs)[21])
    {
        o_inputs[0]  = (digitalReadFast(27) == 0);
        o_inputs[1]  = (digitalReadFast(0) == 0);
        o_inputs[2]  = (digitalReadFast(1) == 0);
        o_inputs[3]  = (digitalReadFast(2) == 0);
        o_inputs[4]  = (digitalReadFast(3) == 0);
        o_inputs[5]  = (digitalReadFast(4) == 0);
        o_inputs[6]  = (digitalReadFast(5) == 0);
        o_inputs[7]  = (digitalReadFast(7) == 0);
        o_inputs[8]  = (digitalReadFast(8) == 0);
        o_inputs[9]  = (digitalReadFast(9) == 0);
        o_inputs[10] = (digitalReadFast(10) == 0);
        o_inputs[11] = (digitalReadFast(11) == 0);
        o_inputs[12] = (digitalReadFast(12) == 0);
        o_inputs[13] = (digitalReadFast(13) == 0);
        o_inputs[14] = (digitalReadFast(14) == 0);
        o_inputs[15] = (digitalReadFast(15) == 0);
        o_inputs[16] = (digitalReadFast(16) == 0);
        o_inputs[17] = (digitalReadFast(20) == 0);
        o_inputs[18] = (digitalReadFast(39) == 0);
        o_inputs[19] = (digitalReadFast(43) == 0);
        o_inputs[20] = (digitalReadFast(17) == 0);
    }

    template <> inline void SetRow<0>  () { digitalWriteFast(23, LOW);  }
    template <> inline void ClearRow<0>() { digitalWriteFast(23, HIGH); }
    template <> inline void SetRow<1>  () { digitalWriteFast(45, LOW);  }
    template <> inline void ClearRow<1>() { digitalWriteFast(45, HIGH); }
    template <> inline void SetRow<2>  () { digitalWriteFast(44, LOW);  }
    template <> inline void ClearRow<2>() { digitalWriteFast(44, HIGH); }
    template <> inline void SetRow<3>  () { digitalWriteFast(38, LOW);  }
    template <> inline void ClearRow<3>() { digitalWriteFast(38, HIGH); }
    template <> inline void SetRow<4>  () { digitalWriteFast(22, LOW);  }
    template <> inline void ClearRow<4>() { digitalWriteFast(22, HIGH); }
    template <> inline void SetRow<5>  () { digitalWriteFast(21, LOW);  }
    template <> inline void ClearRow<5>() { digitalWriteFast(21, HIGH); }
}
