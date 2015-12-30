#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include "Descriptors.h"

#include "PlatformTeensy.h"

#include "TestBoard.h"

#include "Board.h"

namespace
{
    uint8_t s_previousKeyboardReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

    /** LUFA HID Class driver interface configuration and state information. This structure is
     *  passed to all HID Class driver functions, so that multiple instances of the same class
     *  within a device can be differentiated from one another.
     */
    USB_ClassInfo_HID_Device_t Keyboard_HID_Interface; 
    
    // Please note that the initialization of this structure was moved to an assignment because
    // of a gcc error: "sorry, unimplemented: non-trivial designated initializers not supported"

    void InitHIDs()
    {
        Keyboard_HID_Interface.Config.InterfaceNumber        = INTERFACE_ID_Keyboard;
        Keyboard_HID_Interface.Config.PrevReportINBuffer     = &s_previousKeyboardReportBuffer[0];
        Keyboard_HID_Interface.Config.PrevReportINBufferSize = sizeof(s_previousKeyboardReportBuffer);

        Keyboard_HID_Interface.Config.ReportINEndpoint.Address              = KEYBOARD_EPADDR;
        Keyboard_HID_Interface.Config.ReportINEndpoint.Size                 = KEYBOARD_EPSIZE;
        Keyboard_HID_Interface.Config.ReportINEndpoint.Banks                = 1;
    }

    Board<Matrix> keyboard;
}

extern "C"
{
    void EVENT_USB_Device_Connect(void)
    {
    }

    void EVENT_USB_Device_Disconnect(void)
    {
    }

    void EVENT_USB_Device_ConfigurationChanged(void)
    {
        HID_Device_ConfigureEndpoints(& Keyboard_HID_Interface);
        USB_Device_EnableSOFEvents();
    }

    void EVENT_USB_Device_ControlRequest(void)
    {
        HID_Device_ProcessControlRequest(& Keyboard_HID_Interface);
    }

    void EVENT_USB_Device_StartOfFrame(void)
    {
        HID_Device_MillisecondElapsed(& Keyboard_HID_Interface);
    }

    /** HID class driver callback function for the creation of HID reports to the host.
     *
     *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
     *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
     *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
     *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
     *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
     *
     *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
     */
    bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const  HIDInterfaceInfo,
                                             uint8_t* const                     ReportID,
                                             const uint8_t                      ReportType,
                                             void*                              ReportData,
                                             uint16_t* const                    ReportSize)
    {
        USB_KeyboardReport_Data_t* KeyboardReport = static_cast<USB_KeyboardReport_Data_t*>(ReportData);

        *ReportSize = sizeof(USB_KeyboardReport_Data_t);
        return false;
    }

    /** HID class driver callback function for the processing of HID reports from the host.
     *
     *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
     *  \param[in] ReportID    Report ID of the received report from the host
     *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
     *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
     *  \param[in] ReportSize  Size in bytes of the received HID report
     */
    void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                              const uint8_t                     ReportID,
                                              const uint8_t                     ReportType,
                                              const void*                       ReportData,
                                              const uint16_t                    ReportSize)
    {
    }
}

int main (void)
{
    Platform::Init();

    InitHIDs();
    USB_Init();

    GlobalInterruptEnable();

    while(1)
    {
        keyboard.Process();
        HID_Device_USBTask(& Keyboard_HID_Interface);
        USB_USBTask();
    }

    return 0;
}
