#include "Platform.h"

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

    void _reboot_Teensyduino_(void)
    {
        // TODO: initialize R0 with a code....
        __asm__ volatile("bkpt");
    }

    void JumpToBootloader()
    {
        _reboot_Teensyduino_();
    }
}
