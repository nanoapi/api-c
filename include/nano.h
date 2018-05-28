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

#if __cplusplus
} // extern "C"
#endif

#endif // NANO_C_API_H
