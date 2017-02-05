#ifndef INSIDE_PLATFORM_H_
#error "Do not include this file directly!!!"
#endif

#include "Arduino.h"

namespace Platform
{
    template<uint32_t usec>
    void DelayMicrosecs()
    {
        delayMicroseconds(usec);
    }

    template<uint32_t msec>
    void DelayMillisecs()
    {
        delay(msec);
    }
}

#define INSIDE_PLATFORM_SPECIFIC_H_
#include "PlatformBoardSpecific.h"
#undef INSIDE_PLATFORM_SPECIFIC_H_

