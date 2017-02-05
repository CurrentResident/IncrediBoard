#ifndef INSIDE_PLATFORM_H_
#error "Do not include this file directly!!!"
#endif

#include <util/delay.h>

namespace Platform
{
    template<uint32_t usec>
    void DelayMicrosecs()
    {
        _delay_us(usec);
    }
}

#define INSIDE_PLATFORM_SPECIFIC_H_
#include "PlatformBoardSpecific.h"
#undef INSIDE_PLATFORM_SPECIFIC_H_

