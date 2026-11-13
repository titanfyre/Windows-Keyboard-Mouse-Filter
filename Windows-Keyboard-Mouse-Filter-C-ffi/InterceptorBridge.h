#ifndef WINDOWS_KEYBOARD_MOUSE_FILTER_BRIDGE_H
#define WINDOWS_KEYBOARD_MOUSE_FILTER_BRIDGE_H
#include <stdint.h>
#ifdef IC_BRIDGE_EXPORTS
#define WINDOWS_KEYBOARD_MOUSE_FILTER_API __declspec(dllexport)
#else
#define WINDOWS_KEYBOARD_MOUSE_FILTER_API __declspec(dllimport)
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* Windows x64, cdecl, natural alignment. Never free borrowed pointers.
   Receive views remain valid until the next receive or close. Copy data before
   another thread calls either. Every function catches C++ exceptions. */
enum {
    WINDOWS_KEYBOARD_MOUSE_FILTER_KEYBOARD = 1,
    WINDOWS_KEYBOARD_MOUSE_FILTER_MOUSE = 2,
    WINDOWS_KEYBOARD_MOUSE_FILTER_HID = 3,
    WINDOWS_KEYBOARD_MOUSE_FILTER_XINPUT = 4,
    WINDOWS_KEYBOARD_MOUSE_FILTER_XINPUTHID = 5,
    WINDOWS_KEYBOARD_MOUSE_FILTER_GIP = 6
};
enum {
    WINDOWS_KEYBOARD_MOUSE_FILTER_STATE = 0,
    WINDOWS_KEYBOARD_MOUSE_FILTER_AXIS = 1,
    WINDOWS_KEYBOARD_MOUSE_FILTER_TRIGGER = 2,
    WINDOWS_KEYBOARD_MOUSE_FILTER_HAT = 3,
    WINDOWS_KEYBOARD_MOUSE_FILTER_VALUE = 4,
    WINDOWS_KEYBOARD_MOUSE_FILTER_BUTTON = 5,
    WINDOWS_KEYBOARD_MOUSE_FILTER_BINARY = 6,
    WINDOWS_KEYBOARD_MOUSE_FILTER_REPORT = 7
};
enum {
    WINDOWS_KEYBOARD_MOUSE_FILTER_NORMALIZED = 1,
    WINDOWS_KEYBOARD_MOUSE_FILTER_RELATIVE = 2,
    WINDOWS_KEYBOARD_MOUSE_FILTER_HAS_NULL = 4,
    WINDOWS_KEYBOARD_MOUSE_FILTER_IS_NULL = 8,
    WINDOWS_KEYBOARD_MOUSE_FILTER_IS_TRIGGER = 16,
    WINDOWS_KEYBOARD_MOUSE_FILTER_READ_ONLY = 32
};
#pragma pack(push, 8)
typedef struct windows_keyboard_mouse_filter_error {
    uint32_t code, accepted;
    char message[768];
} windows_keyboard_mouse_filter_error;
typedef struct windows_keyboard_mouse_filter_field {
    const char *name;
    int64_t value, minimum, maximum, physical_minimum, physical_maximum;
    double normalized;
    uint32_t group, index, usage_page, usage, collection, report_id, data_index, element;
    uint32_t flags, units, units_exponent, bit_size;
    uint8_t *data;
    uint32_t length, reserved;
} windows_keyboard_mouse_filter_field;
typedef struct windows_keyboard_mouse_filter_event {
    uint32_t kind, blocked;
    uint64_t sequence, timestamp;
    const char *token;
    windows_keyboard_mouse_filter_field *fields;
    uint32_t field_count, decode_error, decode_complete, parser_status, device, reserved;
} windows_keyboard_mouse_filter_event;
typedef struct windows_keyboard_mouse_filter_batch {
    uint64_t id;
    uint32_t count, reserved;
    windows_keyboard_mouse_filter_event *events;
} windows_keyboard_mouse_filter_batch;
typedef struct windows_keyboard_mouse_filter_device {
    uint32_t kind, id;
    uint16_t vid, pid, usage_page, usage;
    const char *token;
    const char *name;
    const char *hardware_id;
} windows_keyboard_mouse_filter_device;
typedef struct windows_keyboard_mouse_filter_devices {
    uint32_t count, reserved;
    const windows_keyboard_mouse_filter_device *items;
} windows_keyboard_mouse_filter_devices;
typedef struct windows_keyboard_mouse_filter_blob {
    uint32_t applicable, format, length, reserved;
    const uint8_t *data;
} windows_keyboard_mouse_filter_blob;
typedef struct windows_keyboard_mouse_filter_init {
    uint32_t ready, reboot_required, associated, already_associated, skipped, reserved;
} windows_keyboard_mouse_filter_init;
typedef struct windows_keyboard_mouse_filter_info {
    uint32_t installed, active, trial_state, input_mask, controller_mask, device_count, queued,
        last_reset;
    uint64_t remaining_ms, timestamp_frequency, generation;
} windows_keyboard_mouse_filter_info;
#pragma pack(pop)
WINDOWS_KEYBOARD_MOUSE_FILTER_API const char* windows_keyboard_mouse_filter_product_name(void);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_input_mask(void);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_controller_mask(void);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_version(void);
/* sizeof: 1 field, 2 event, 3 batch, 4 device, 5 error, 6 info. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_sizeof(uint32_t type);
/* Open is lazy: no driver capture, installation, timer or worker thread. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_open(uint64_t *session, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_close(uint64_t session, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_initialize(uint64_t session, windows_keyboard_mouse_filter_init *result, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_info_get(uint64_t session, windows_keyboard_mouse_filter_info *result, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_devices_get(uint64_t session, const windows_keyboard_mouse_filter_devices **result, windows_keyboard_mouse_filter_error *error);
/* timeout in milliseconds, UINT32_MAX means infinite. Cancel returns empty. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_receive(uint64_t session, uint32_t timeout, const windows_keyboard_mouse_filter_batch **result,
                             windows_keyboard_mouse_filter_error *error);
/* Counts inferred from ticket. Retry forwards only the unaccepted remainder. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_send(uint64_t session, uint64_t ticket, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_discard(uint64_t session, uint64_t ticket, windows_keyboard_mouse_filter_error *error);
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_cancel(uint64_t session, windows_keyboard_mouse_filter_error *error);
/* Native HID report: report=1; common descriptor: report=0. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_descriptor(uint64_t session, const char *token, uint32_t report,
                                windows_keyboard_mouse_filter_blob *result, windows_keyboard_mouse_filter_error *error);
/* Synthetic input: kind and capture token select an existing source. Named
   STATE fields plus REPORT bytes use the same representation as receive.
   Input and field counts belong only to this low-level FFI; wrappers infer them. */
WINDOWS_KEYBOARD_MOUSE_FILTER_API uint32_t windows_keyboard_mouse_filter_inject(uint64_t session, const windows_keyboard_mouse_filter_event *inputs, uint32_t count,
                            windows_keyboard_mouse_filter_error *error);
#ifdef __cplusplus
}
static_assert(sizeof(windows_keyboard_mouse_filter_field) == 120 && sizeof(windows_keyboard_mouse_filter_event) == 64 && sizeof(windows_keyboard_mouse_filter_batch) == 24,
              "C ABI layout");
static_assert(sizeof(windows_keyboard_mouse_filter_device) == 40 && sizeof(windows_keyboard_mouse_filter_error) == 776 && sizeof(windows_keyboard_mouse_filter_info) == 56,
              "C ABI layout");
#endif
#endif
