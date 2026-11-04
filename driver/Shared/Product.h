#pragma once
// Build identity and immutable family boundary for this separate product.
// This header is also directly testable outside the kernel.
#define IC_PRODUCT_SERVICE L"WindowsKeyboardMouseFilter"
#define IC_PRODUCT_XUSB_HID_PARENT_VALUE L"WindowsKeyboardMouseFilterXusbHidParent"
#define IC_PRODUCT_XUSB_PARENT_VALUE L"WindowsKeyboardMouseFilterXusbParent"
#define IC_PRODUCT_CONTROL_HWID L"ROOT\\WindowsKeyboardMouseFilterControl"
#define IC_PRODUCT_NT_DEVICE L"\\Device\\WindowsKeyboardMouseFilter"
#define IC_PRODUCT_DOS_DEVICE L"\\DosDevices\\WindowsKeyboardMouseFilter"
#define IC_PRODUCT_TRIAL_SLOT 1u
#define IC_PRODUCT_TRIAL_KEY L"\\Registry\\Machine\\HARDWARE\\WindowsKeyboardMouseFilterTrial"
#ifndef IC_PRODUCT_INPUT_MASK
#define IC_PRODUCT_INPUT_MASK 3u
#endif
#ifndef IC_PRODUCT_CONTROLLER_MASK
#define IC_PRODUCT_CONTROLLER_MASK 0u
#endif
#ifndef IC_PRODUCT_HAS_KEYBOARD_MOUSE
#define IC_PRODUCT_HAS_KEYBOARD_MOUSE 1
#endif
#ifndef IC_PRODUCT_HAS_CONTROLLERS
#define IC_PRODUCT_HAS_CONTROLLERS 0
#endif
#define IC_PRODUCT_STREAM_MASK (IC_PRODUCT_INPUT_MASK | (IC_PRODUCT_CONTROLLER_MASK << 2))
#define IC_PRODUCT_HID_GUID {0x9501889e,0x03bc,0x5c86,{0xb1,0x05,0xaf,0xfd,0xdf,0x60,0x02,0x32}}
#define IC_PRODUCT_XUSB_GUID {0x71a1a2df,0x38e9,0x5561,{0xac,0x21,0xea,0xac,0xbc,0x4c,0xd2,0x67}}
#define IC_PRODUCT_XINPUTHID_GUID {0xc306ebb7,0x9732,0x5180,{0x81,0x55,0x57,0x6b,0xb1,0x6d,0x46,0xa4}}
#define IC_PRODUCT_GIP_GUID {0xdf661269,0x4589,0x5794,{0x88,0xf4,0xad,0x1b,0x4d,0x31,0x3f,0x93}}
#define IC_PRODUCT_XUSB_MIRROR_GUID {0x2920489e,0xf46f,0x5558,{0x96,0xe0,0x2a,0xb2,0x85,0xfe,0x41,0x96}}
static __inline int IcProductTypeAllowed(unsigned int type) {
    return type>=1 && type<=6 && (IC_PRODUCT_STREAM_MASK & (1u<<(type-1)))!=0;
}
static __inline int IcProductCreateMasksAllowed(unsigned int input,unsigned int controllers) {
    return !(input & ~IC_PRODUCT_INPUT_MASK) && !(controllers & ~IC_PRODUCT_CONTROLLER_MASK);
}
// Function numbers are the pointer-free protocol's CTL_CODE function field.
// Unknown/common functions keep the normal control dispatch validation.
static __inline int IcProductIoctlFunctionAllowed(unsigned int fn) {
    switch(fn) {
    case 0xA01:case 0xA03:case 0xA07:
        return (IC_PRODUCT_INPUT_MASK & 1u)!=0;
    case 0xA02:case 0xA04:case 0xA08:
        return (IC_PRODUCT_INPUT_MASK & 2u)!=0;
    case 0xA09:case 0xA0A:case 0xA0B:case 0xA0C:case 0xA0D:
        return (IC_PRODUCT_CONTROLLER_MASK & 1u)!=0;
    case 0xA10:case 0xA11:case 0xA12:case 0xA13:case 0xA14:case 0xA15:
        return (IC_PRODUCT_CONTROLLER_MASK & 2u)!=0;
    case 0xA17:case 0xA18:case 0xA19:case 0xA1A:case 0xA1B:
        return (IC_PRODUCT_CONTROLLER_MASK & 4u)!=0;
    case 0xA20:case 0xA21:case 0xA22:case 0xA23:case 0xA24:case 0xA25:
    case 0xA29:case 0xA2A:case 0xA2B:
        return (IC_PRODUCT_CONTROLLER_MASK & 8u)!=0;
    default:return 1;
    }
}

