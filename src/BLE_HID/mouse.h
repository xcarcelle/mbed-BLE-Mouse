#include "mbed.h"

#include "HIDServiceBase.h"

#define MOUSE_BUTTON_LEFT    0x01
#define MOUSE_BUTTON_RIGHT   0x02
#define MOUSE_BUTTON_MIDDLE  0x04

report_map_t MOUSE_REPORT_MAP = {
    USAGE_PAGE(1),      0x01,         // Generic Desktop
    USAGE(1),           0x02,         // Mouse
    COLLECTION(1),      0x01,         // Application
    USAGE(1),           0x01,         //  Pointer
    COLLECTION(1),      0x00,         //  Physical
    USAGE_PAGE(1),      0x09,         //   Buttons
    USAGE_MINIMUM(1),   0x01,
    USAGE_MAXIMUM(1),   0x03,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_COUNT(1),    0x03,         //   3 bits (Buttons)
    REPORT_SIZE(1),     0x01,
    INPUT(1),           0x02,         //   Data, Variable, Absolute
    REPORT_COUNT(1),    0x01,         //   5 bits (Padding)
    REPORT_SIZE(1),     0x05,
    INPUT(1),           0x01,         //   Constant
    USAGE_PAGE(1),      0x01,         //   Generic Desktop
    USAGE(1),           0x30,         //   X
    USAGE(1),           0x31,         //   Y
    // USAGE(1),           0x38,         //   Wheel
    PHYSICAL_MINIMUM(2), 0x00, 0x00,         //  0 
    PHYSICAL_MAXIMUM(2), 0xff, 0x7f,   //  32767 
    LOGICAL_MINIMUM(2), 0x01, 0x80,    //  -32767 
    LOGICAL_MAXIMUM(2), 0xff, 0x7f,    //  32767
    //UNIT(2), 0x00, 0x00,         //  No unit 
    REPORT_SIZE(1),     0x10,         //   Three bytes
    REPORT_COUNT(1),    0x02,
    INPUT(1),           0x06,         //   Data, Variable, Relative
    END_COLLECTION(0),
    END_COLLECTION(0),
/*
0x05, 0x0d,       //USAGE_PAGE (Digitizers) 
0x09, 0x01,       //USAGE (Digitizers) 
//+4 
0xa1, 0x01,       //COLLECTION (Application) 
0x09, 0x02,       //USAGE (pen) 
//+4 
0xa1, 0x00,       //COLLECTION (Physical) 
//+2 
0x09, 0x42,       // USAGE (Tip Switch) 
0x15, 0x00,       // LOGICAL_MINIMUM (0) 
0x25, 0x01,       // LOGICAL_MAXIMUM (1) 
0x75, 0x01,       // REPORT_SIZE (1) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x81, 0x02,       // INPUT (Data,Var,Abs) 
//+12 
0x09, 0x00,       // USAGE (Undefined/Padding) 
0x75, 0x03,       // REPORT_SIZE (3) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x81, 0x03,       // INPUT (Cnst,Var,Abs) 
//+8 
0x09, 0x32,       // USAGE (In Range) 
0x75, 0x01,       // REPORT_SIZE (1) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x81, 0x02,       // INPUT (Data,Var,Abs) 
//+8 
0x09, 0x00,       // USAGE (Undefined/Padding) 
0x75, 0x03,       // REPORT_SIZE (3) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x81, 0x03,       // INPUT (Cnst,Var,Abs) 
//+8 
//X TILT 
0x09, 0x3d,       // USAGE (X tilt) 
0x16, 0xd8, 0xdc,     // LOGICAL_MINIMUM (-9000) 
0x26, 0x28, 0x23,     // LOGICAL_MAXIMUM (9000) 
0x75, 0x10,       // REPORT_SIZE (16) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x55, 0x0E,       // UNIT_EXPONENT (-2) 
0x65, 0x14,       // UNIT (en dg) 
0x36, 0xd8, 0xdc,     // PHYSICAL_MINIMUM (-9000) 
0x46, 0x28, 0x23,     // PHYSICAL_MAXIMUM (9000) 
0x81, 0x02,       // INPUT (Data,Var,Abs) 
//+24 
//Y TILT 
0x09, 0x3e,       // USAGE (Y tilt) 
0x16, 0xd8, 0xdc,     // LOGICAL_MINIMUM (-9000) 
0x26, 0x28, 0x23,     // LOGICAL_MAXIMUM (9000) 
0x75, 0x10,       // REPORT_SIZE (16) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x55, 0x0E,       // UNIT_EXPONENT (-2) 
0x65, 0x14,       // UNIT (en dg) 
0x36, 0xd8, 0xdc,     // PHYSICAL_MINIMUM (-9000) 
0x46, 0x28, 0x23,     // PHYSICAL_MAXIMUM (9000) 
0x81, 0x02,       // INPUT (Data,Var,Abs) 
//+24 
0x05, 0x01,       // USAGE_PAGE (Generic Desktop) 
0x15, 0x00,       // LOGICAL_MINIMUM (0) 
0x26, 0x08, 0x52,     // LOGICAL_MAXIMUM (21000) ///0x08, 0x52, = 21000 
0x75, 0x10,       // REPORT_SIZE (16) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x55, 0x0d,       // UNIT_EXPONENT (-3) 
0x65, 0x11,       // UNIT (en cm) 
0x09, 0x30,       // USAGE (X) 
0x35, 0x00,       // PHYSICAL_MINIMUM (0) 
0x46, 0x08, 0x52,     // PHYSICAL_MAXIMUM (21000) 
0x81, 0x02,       // INPUT (Data,Var,Abs) 
//+24 
0x15, 0x00,       // LOGICAL_MINIMUM (0) 
0x26, 0xd0, 0x39,     // LOGICAL_MAXIMUM (14800) ///0xd0, 0x39, = 14800 
0x75, 0x10,       // REPORT_SIZE (16) 
0x95, 0x01,       // REPORT_COUNT (1) 
0x55, 0x0d,       // UNIT_EXPONENT (-3) 
0x65, 0x11,       // UNIT (en cm) 
0x09, 0x31,       // USAGE (Y) 
0x35, 0x00,       // PHYSICAL_MINIMUM (0) 
0x46, 0xd0, 0x39,     // PHYSICAL_MAXIMUM (14800) 
0x81, 0x06,       // INPUT (Data,Var,Abs) 
//+22 
0xc0,        //END_COLLECTION 
0xc0,        //END_COLLECTION
*/
};

class BLEMouse : public HIDServiceBase
{
    public:
    BLEMouse(BLE &ble);

    void click(uint8_t b = MOUSE_BUTTON_LEFT);
    //void move(signed char x, signed char y, signed char wheel = 0);
    //void move(uint16_t x, uint16_t y, signed char wheel = 0);
    void move(int x, int y, signed char wheel = 0);
    void press(uint8_t b = MOUSE_BUTTON_LEFT);
    void release(uint8_t b = MOUSE_BUTTON_LEFT);
    bool isPressed(uint8_t b = MOUSE_BUTTON_LEFT);

    private:
    unsigned char _button;
};
