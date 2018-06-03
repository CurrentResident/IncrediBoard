#ifndef TEENSY_USB_STACK_DESCRIPTOR_DEFINITIONS_H_
#define TEENSY_USB_STACK_DESCRIPTOR_DEFINITIONS_H_

// The following was crafted using the guidance given in Teensyduino's usb_desc.h.
//

#define VENDOR_ID           0x16C0
#define PRODUCT_ID          0x204E

#define MANUFACTURER_NAME       {'J','i','m',' ','T','h','o','e','n','e','n'}
#define MANUFACTURER_NAME_LEN   11
#define PRODUCT_NAME            {'I','n','c','r','e','d','i','B','o','a','r','d',' ','T','3','T','e','s','t'}
#define PRODUCT_NAME_LEN        19

#define EP0_SIZE        64
#define NUM_ENDPOINTS   2
#define NUM_USB_BUFFERS 6       // 3 per endpoint because why not..  see if this goes okay.
#define NUM_INTERFACE   2

    #define KEYBOARD_INTERFACE  0    // Keyboard
    #define KEYBOARD_ENDPOINT   1
    #define KEYBOARD_SIZE       8
    #define KEYBOARD_INTERVAL   1

    #define MOUSE_INTERFACE       1    // Mouse
    #define MOUSE_ENDPOINT        2
    #define MOUSE_SIZE            8
    #define MOUSE_INTERVAL        1

// TODO: Determine why/how KEYMEDIA_INTERFACE is different from KEYBOARD in Teensyduino.
//#define KEYMEDIA_INTERFACE    4    // Keyboard Media Keys
//#define KEYMEDIA_ENDPOINT     6
//#define KEYMEDIA_SIZE         8
//#define KEYMEDIA_INTERVAL     4

#define ENDPOINT1_CONFIG    ENDPOINT_TRANSIMIT_ONLY  //(sic)
#define ENDPOINT2_CONFIG    ENDPOINT_TRANSIMIT_ONLY

#endif
