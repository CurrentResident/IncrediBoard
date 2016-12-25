#ifndef USB_COMPONENT_H_
#define USB_COMPONENT_H_

#include "BoardState.h"
#include "UsbInterface.h"

class UsbComponent
{
    public:

        void Process(BoardState& io_state)
        {
            UsbInterface::Process(io_state.m_keyReportArray.Get(),
                                  io_state.m_keyReportArray.size(),
                                  io_state.m_modifiers);
        }

};

#endif
