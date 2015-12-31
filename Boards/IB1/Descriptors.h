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
    USB_Descriptor_Interface_t            HID_Interface;
    USB_HID_Descriptor_HID_t              HID_KeyboardHID;
    USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
} USB_Descriptor_Configuration_t;

enum InterfaceDescriptors_t
{
    INTERFACE_ID_Keyboard = 0, /**< Keyboard interface descriptor ID */
};

enum StringDescriptors_t
{
    STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
    STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
    STRING_ID_Product      = 2, /**< Product string ID */
};

#define KEYBOARD_EPADDR              (ENDPOINT_DIR_IN | 1)

// Size in bytes of the Keyboard HID reporting IN endpoint.
#define KEYBOARD_EPSIZE              8

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#ifdef __cplusplus
}
#endif

#endif
