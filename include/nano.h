#ifndef NANO_C_API_H
#define NANO_C_API_H

#include "core.pb-c.h"
#include "accounts.pb-c.h"
#include "util.pb-c.h"

#define PREAMBLE_1 'N'
#define PREAMBLE_2 0x0
#define PREAMBLE_VERSION_MAJOR 1
#define PREAMBLE_VERSION_MINOR 0

#if __cplusplus
extern "C" {
#endif

/** Opaque type representing a session with the Nano node */
struct nano_session;

/**
 * Connect to the node over the give transport address
 * @param connection Connection string starting with local://, tcp:// or mem://
 * @returns Opaque session, or NULL if an error occurs. If NULL, use nano_last_error(_string) to obtain the error.
 */
struct nano_session* nano_connect (const char* connection);

/**
 * Disconnect from the node
 * @param session Session previously retrived from nano_connect()
 * @returns 0 on success. If non-zero, use nano_last_error(_string) to obtain the error.
 */
int nano_disconnect (struct nano_session* session);

/**
 * Send request and await response 
 * @param request Request buffer
 * @param request_size Request buffer size in bytes.
 * @param response Pointer to response buffer. This must be freed by the caller after unpacking with protobuf.
 * @param response_size Size of the response buffer in bytes. 
 * @returns 0 on success. If non-zero, use nano_last_error(_string) to obtain the error.
 */
int nano_request(struct nano_session* session, RequestType type, void* request, size_t request_size, void** response, size_t* response_size);

/**
 * @returns The last error, or zero if there is no error.
 */
int nano_last_error (struct nano_session* session);

/**
 * Returns the string representation of the last error, or an empty string if there is no string mapping available or
 * there is no current error state.
 * 
 * The returned string is invalidated by any other call to the nano api, except nano_last_error. Make a copy of the
 * string if needed.
 * 
 * The error state is reset by this call.
 * @returns The error string. Do not deallocate this, memory for error strings are managed by the API.
 */
const char* nano_last_error_string (struct nano_session* session);

/**
 * Returns the category of the last error, or an empty string if there is no category mapping available or
 * there is no current error state.
 * @returns The error category. Do not deallocate this, memory for error string are managed by the API. 
 */
const char* nano_last_error_category (struct nano_session* session);

/**
 * Clears the error state by setting the error code to zero and the error string to an empty string.
 */
void nano_last_error_clear (struct nano_session* session);

#define nano_optional_string Google__Protobuf__StringValue
#define nano_optional_string_init google__protobuf__string_value__init
#define nano_optional_double Google__Protobuf__DoubleValue;
#define nano_optional_double_init google__protobuf__double_value_init;
#define nano_optional_float Google__Protobuf__FloatValue;
#define nano_optional_float_init google__protobuf__float_value_init;
#define nano_optional_int64 Google__Protobuf__Int64Value;
#define nano_optional_int64_init google__protobuf__int64_value_init;
#define nano_optional_uint64 Google__Protobuf__UInt64Value;
#define nano_optional_uint64_init google__protobuf__uint64_value_init;
#define nano_optional_int32 Google__Protobuf__Int32Value;
#define nano_optional_int32_init google__protobuf__int32_value_init;
#define nano_optional_uint32 Google__Protobuf__UInt32Value;
#define nano_optional_uint32_init google__protobuf__uint32_value_init;
#define nano_optional_bool Google__Protobuf__BoolValue;
#define nano_optional_bool_init google__protobuf__bool_value_init;
#define nano_optional_bytes Google__Protobuf__BytesValue;
#define nano_optional_bytes_init google__protobuf__bytes_value_init;

#if __cplusplus
} // extern "C"
#endif

#endif // NANO_C_API_H
