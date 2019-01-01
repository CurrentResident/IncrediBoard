#include "UsbInterface.h"

#include <cstring>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include "Descriptors.h"

namespace
{
    uint8_t s_previousKeyboardReportBuffer[sizeof(USB_KeyboardReport_Data_t)];
    uint8_t s_previousMouseReportBuffer   [sizeof(USB_MouseReport_Data_t)];

    // Keyboard bookkeeping
    const uint8_t   s_keycodesRollOverError[6] = {1, 1, 1, 1, 1, 1};
    const uint8_t*  s_keycodesPointer;
    uint8_t         s_keycodesCount;
    uint8_t         s_modifiers;

    // Mouse bookkeeping
    uint8_t s_mouseButtons;
    int8_t  s_mouseX;
    int8_t  s_mouseY;

    /** LUFA HID Class driver interface configuration and state information. This structure is
     *  passed to all HID Class driver functions, so that multiple instances of the same class
     *  within a device can be differentiated from one another.
     */
    USB_ClassInfo_HID_Device_t Keyboard_HID_Interface; 
    USB_ClassInfo_HID_Device_t Mouse_HID_Interface; 
    
    // Please note that the initialization of this structure was moved to an assignment because
    // of a gcc error: "sorry, unimplemented: non-trivial designated initializers not supported"
    //
    // It works in C, but not C++ apparently.  Huh.

    void InitHIDs() __attribute__((constructor));
    void InitHIDs()
    {
        Keyboard_HID_Interface.Config.InterfaceNumber        = INTERFACE_ID_Keyboard;
        Keyboard_HID_Interface.Config.PrevReportINBuffer     = &s_previousKeyboardReportBuffer[0];
        Keyboard_HID_Interface.Config.PrevReportINBufferSize = sizeof(s_previousKeyboardReportBuffer);

        Keyboard_HID_Interface.Config.ReportINEndpoint.Address = KEYBOARD_EPADDR;
        Keyboard_HID_Interface.Config.ReportINEndpoint.Size    = EPSIZE;
        Keyboard_HID_Interface.Config.ReportINEndpoint.Banks   = 1;
        Keyboard_HID_Interface.Config.ReportINEndpoint.Type    = EP_TYPE_INTERRUPT;

        Mouse_HID_Interface.Config.InterfaceNumber          = INTERFACE_ID_Mouse;
        Mouse_HID_Interface.Config.PrevReportINBuffer       = &s_previousMouseReportBuffer[0];
        Mouse_HID_Interface.Config.PrevReportINBufferSize   = sizeof(s_previousMouseReportBuffer);
        Mouse_HID_Interface.Config.ReportINEndpoint.Address = MOUSE_EPADDR;
        Mouse_HID_Interface.Config.ReportINEndpoint.Banks   = 1;
        Mouse_HID_Interface.Config.ReportINEndpoint.Size    = EPSIZE;
        Mouse_HID_Interface.Config.ReportINEndpoint.Type    = EP_TYPE_INTERRUPT;
    }
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
        HID_Device_ConfigureEndpoints(& Mouse_HID_Interface);
        USB_Device_EnableSOFEvents();
    }

    void EVENT_USB_Device_ControlRequest(void)
    {
        HID_Device_ProcessControlRequest(& Keyboard_HID_Interface);
        HID_Device_ProcessControlRequest(& Mouse_HID_Interface);
    }

    void EVENT_USB_Device_StartOfFrame(void)
    {
        HID_Device_MillisecondElapsed(& Keyboard_HID_Interface);
        HID_Device_MillisecondElapsed(& Mouse_HID_Interface);
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
        bool forceSend = false;

        if (HIDInterfaceInfo == & Keyboard_HID_Interface)
        {
            USB_KeyboardReport_Data_t* KeyboardReport = static_cast<USB_KeyboardReport_Data_t*>(ReportData);
    
            if (s_keycodesCount > 6)
            {
                std::memcpy(KeyboardReport->KeyCode, s_keycodesRollOverError, 6);
            }
            else
            {
                // The FixedArray class that we used to generate the keycode array is setup to fill empty
                // elements with 0, so it is safe to do this here.  It would be nice to figure out a more
                // explicit way of showing that here.
                //
                std::memcpy(KeyboardReport->KeyCode, s_keycodesPointer, 6);
            }
    
            KeyboardReport->Modifier = s_modifiers;
    
            *ReportSize = sizeof(USB_KeyboardReport_Data_t);
        }
        else
        {
            USB_MouseReport_Data_t* mouseReport = static_cast<USB_MouseReport_Data_t*>(ReportData);

            mouseReport->Button = s_mouseButtons;
            mouseReport->X      = s_mouseX;
            mouseReport->Y      = s_mouseY;

            *ReportSize = sizeof(USB_MouseReport_Data_t);

            // If we're not doing anything with the mouse controls, no need to force the mouse report.
            forceSend = s_mouseButtons or s_mouseX or s_mouseY;
        }

        return forceSend;
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

namespace UsbInterface
{
    void Init()
    {
        USB_Init();

        GlobalInterruptEnable();
    }

    void MouseSetButtons(uint8_t i_buttonBitset)
    {
        s_mouseButtons = i_buttonBitset;
    }

    void MouseMove(int8_t i_mouseX, int8_t i_mouseY)
    {
        s_mouseX = i_mouseX;
        s_mouseY = i_mouseY;
    }

    void Process(const uint8_t* i_keycodes, uint8_t i_keycodeCount, uint8_t i_modifiers)
    {
        s_keycodesPointer = i_keycodes;
        s_keycodesCount   = i_keycodeCount;
        s_modifiers       = i_modifiers;

        HID_Device_USBTask(& Keyboard_HID_Interface);
        HID_Device_USBTask(& Mouse_HID_Interface);
        USB_USBTask();
    }
}
