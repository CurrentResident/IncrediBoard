#include "Platform.h"

#include "Arduino.h"

namespace Platform
{
    void Init()
    {
        // TODO:  Automate the initialization of IOs and tie in with IO functions in header.
        //
        ConfigurePins();
    }

    unsigned long GetMsec()
    {
        return millis();
    }

    void JumpToBootloader()
    {
        _reboot_Teensyduino_();
    }
}
