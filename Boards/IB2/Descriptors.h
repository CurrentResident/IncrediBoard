#ifndef LUFA_DESCRIPTORS_H_
#define LUFA_DESCRIPTORS_H_

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    USB_Descriptor_Configuration_Header_t Config;

    // Keyboard HID Interface
    USB_Descriptor_Interface_t            HID_KeyboardInterface;
    USB_HID_Descriptor_HID_t              HID_KeyboardHID;
    USB_Descriptor_Endpoint_t             HID_KeyboardReportINEndpoint;

    // Mouse
    USB_Descriptor_Interface_t            HID_MouseInterface;
    USB_HID_Descriptor_HID_t              HID_MouseHID;
    USB_Descriptor_Endpoint_t             HID_MousetReportINEndpoint;

} USB_Descriptor_Configuration_t;

enum InterfaceDescriptors_t
{
    INTERFACE_ID_Keyboard = 0,
    INTERFACE_ID_Mouse
};

enum StringDescriptors_t
{
    STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
    STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
    STRING_ID_Product      = 2, /**< Product string ID */
};

#define KEYBOARD_EPADDR (ENDPOINT_DIR_IN | 1)
#define MOUSE_EPADDR    (ENDPOINT_DIR_IN | 3)

// Size in bytes of either HID reporting IN endpoints.
#define EPSIZE              8

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#ifdef __cplusplus
}
#endif

#endif
