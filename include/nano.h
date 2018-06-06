#ifndef NANO_C_API_H
#define NANO_C_API_H

#include "core.pb-c.h"

#if __cplusplus
extern "C" {
#endif

/** Opaque type representing a session with the Nano node */
struct nano_session;

/**
 * Connect to the node over the give transport address
 * @param connection Connection string starting with local://, tcp:// or mem://
 * @returns Opaque session, or NULL if an error occurs.
 */
struct nano_session* nano_connect (const char* connection);

/**
 * Disconnect from the node
 * @param session Session previously retrived from nano_connect()
 * @returns 0 on success
 */
int nano_disconnect (struct nano_session* session);

/**
 * Send query and await response 
 * @param query Query buffer
 * @param query_size Query buffer size in bytes.
 * @param response Pointer to response buffer. This must be freed by the caller after unpacking with protobuf.
 * @param response_size Size of the response buffer in bytes. 
 * @returns 0 on success, otherwise an error code according to the Result enum in the protobuffer specification
 */
int nano_query(struct nano_session* session, QueryType type, void* query, size_t query_size, void** response, size_t* response_size);

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
