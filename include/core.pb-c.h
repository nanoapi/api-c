/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: core.proto */

#ifndef PROTOBUF_C_core_2eproto__INCLUDED
#define PROTOBUF_C_core_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "google/protobuf/wrappers.pb-c.h"

typedef struct _Query Query;
typedef struct _Response Response;
typedef struct _QueryClientConnect QueryClientConnect;
typedef struct _ResClientConnect ResClientConnect;
typedef struct _QueryPing QueryPing;
typedef struct _ResPing ResPing;
typedef struct _QueryAccountPending QueryAccountPending;
typedef struct _ResAccountPending ResAccountPending;
typedef struct _AccountPending AccountPending;
typedef struct _AccountPendingBlockInfo AccountPendingBlockInfo;


/* --- enums --- */

typedef enum _QueryType {
  QUERY_TYPE__UNKOWN = 0,
  QUERY_TYPE__REGISTER_CALLBACK = 1,
  QUERY_TYPE__PING = 2,
  QUERY_TYPE__ACCOUNT_BALANCE = 3,
  QUERY_TYPE__ACCOUNT_BLOCK_COUNT = 4,
  QUERY_TYPE__ACCOUNT_PENDING = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(QUERY_TYPE)
} QueryType;
typedef enum _Result {
  RESULT__OK = 0,
  RESULT__GENERIC_ERROR = 1,
  RESULT__INVALID_INPUT = 2,
  RESULT__IO_ERROR = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(RESULT)
} Result;

/* --- messages --- */

/*
 ** 
 * This is serialized before the actual query to tell the node what message to expect next.
 * Other query meta data may be added in the future.
 */
struct  _Query
{
  ProtobufCMessage base;
  /*
   ** Query type 
   */
  QueryType type;
};
#define QUERY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query__descriptor) \
    , QUERY_TYPE__UNKOWN }


/*
 **
 * This is serialized before the actual response. 
 * In the future, this will also be sent on callback connections.
 */
struct  _Response
{
  ProtobufCMessage base;
  /*
   ** Result#OK on success 
   */
  Result result;
  /*
   ** 
   * For which query is this a response? This flag allows future support for clients 
   * issuing multiple concurrent queries, as well as push callbacks.
   */
  QueryType type;
  /*
   ** Error message. Only set if result is not Result::OK 
   */
  char *error;
  /*
   **
   * Context dependent error code. For instance, if IO_ERROR occurs, the error_code
   * may contain a more specific, system depended error code.
   */
  int32_t error_code;
};
#define RESPONSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&response__descriptor) \
    , RESULT__OK, QUERY_TYPE__UNKOWN, (char *)protobuf_c_empty_string, 0 }


/*
 ** 
 * Establish a session with the node. This is optional if the node doesn't check api keys.
 * A client will typically send this if it supports multiple node or api versions. 
 * The node may reject clients if the version is too old.
 */
struct  _QueryClientConnect
{
  ProtobufCMessage base;
  /*
   ** Client's API version 
   */
  uint32_t api_version;
  /*
   ** Printable name. This shows up in node logs. 
   */
  char *api_client_id;
  /*
   ** API key. The node may be configured to require this. 
   */
  char *api_key;
};
#define QUERY_CLIENT_CONNECT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query_client_connect__descriptor) \
    , 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/*
 ** Connect response 
 */
struct  _ResClientConnect
{
  ProtobufCMessage base;
  uint32_t api_version;
  uint32_t node_version_major;
  uint32_t node_version_patch;
};
#define RES_CLIENT_CONNECT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&res_client_connect__descriptor) \
    , 0, 0, 0 }


/*
 ** Send ping to the node 
 */
struct  _QueryPing
{
  ProtobufCMessage base;
  /*
   ** Ping ID. The node will respond with the same ID. 
   */
  uint32_t id;
};
#define QUERY_PING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query_ping__descriptor) \
    , 0 }


/*
 ** Ping response 
 */
struct  _ResPing
{
  ProtobufCMessage base;
  /*
   ** The same ID as sent in the ping query 
   */
  uint32_t id;
};
#define RES_PING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&res_ping__descriptor) \
    , 0 }


/*
 ** Returns a list of block hashes which have not yet been received by these accounts 
 */
struct  _QueryAccountPending
{
  ProtobufCMessage base;
  /*
   ** List of accounts to query 
   */
  size_t n_accounts;
  char **accounts;
  /*
   ** Maximum number of blocks to return 
   */
  uint64_t count;
  /*
   ** If true, include source account 
   */
  protobuf_c_boolean source;
  /*
   ** Optional threshold. Returns a list of pending block hashes with amount more or equal to the threshold. 
   */
  Google__Protobuf__StringValue *threshold;
};
#define QUERY_ACCOUNT_PENDING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query_account_pending__descriptor) \
    , 0,NULL, 0, 0, NULL }


/*
 ** query_account_pending result 
 */
struct  _ResAccountPending
{
  ProtobufCMessage base;
  /*
   ** List of accounts, each with a list of pending blocks 
   */
  size_t n_pending;
  AccountPending **pending;
};
#define RES_ACCOUNT_PENDING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&res_account_pending__descriptor) \
    , 0,NULL }


/*
 ** Blocks per account 
 */
struct  _AccountPending
{
  ProtobufCMessage base;
  /*
   ** The account 
   */
  char *account;
  /*
   ** List of blocks with details 
   */
  size_t n_block_info;
  AccountPendingBlockInfo **block_info;
};
#define ACCOUNT_PENDING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&account_pending__descriptor) \
    , (char *)protobuf_c_empty_string, 0,NULL }


/*
 ** Information supplied for each account in query_account_pending 
 */
struct  _AccountPendingBlockInfo
{
  ProtobufCMessage base;
  char *hash;
  char *amount;
  char *source;
};
#define ACCOUNT_PENDING_BLOCK_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&account_pending_block_info__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/* Query methods */
void   query__init
                     (Query         *message);
size_t query__get_packed_size
                     (const Query   *message);
size_t query__pack
                     (const Query   *message,
                      uint8_t             *out);
size_t query__pack_to_buffer
                     (const Query   *message,
                      ProtobufCBuffer     *buffer);
Query *
       query__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query__free_unpacked
                     (Query *message,
                      ProtobufCAllocator *allocator);
/* Response methods */
void   response__init
                     (Response         *message);
size_t response__get_packed_size
                     (const Response   *message);
size_t response__pack
                     (const Response   *message,
                      uint8_t             *out);
size_t response__pack_to_buffer
                     (const Response   *message,
                      ProtobufCBuffer     *buffer);
Response *
       response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   response__free_unpacked
                     (Response *message,
                      ProtobufCAllocator *allocator);
/* QueryClientConnect methods */
void   query_client_connect__init
                     (QueryClientConnect         *message);
size_t query_client_connect__get_packed_size
                     (const QueryClientConnect   *message);
size_t query_client_connect__pack
                     (const QueryClientConnect   *message,
                      uint8_t             *out);
size_t query_client_connect__pack_to_buffer
                     (const QueryClientConnect   *message,
                      ProtobufCBuffer     *buffer);
QueryClientConnect *
       query_client_connect__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query_client_connect__free_unpacked
                     (QueryClientConnect *message,
                      ProtobufCAllocator *allocator);
/* ResClientConnect methods */
void   res_client_connect__init
                     (ResClientConnect         *message);
size_t res_client_connect__get_packed_size
                     (const ResClientConnect   *message);
size_t res_client_connect__pack
                     (const ResClientConnect   *message,
                      uint8_t             *out);
size_t res_client_connect__pack_to_buffer
                     (const ResClientConnect   *message,
                      ProtobufCBuffer     *buffer);
ResClientConnect *
       res_client_connect__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   res_client_connect__free_unpacked
                     (ResClientConnect *message,
                      ProtobufCAllocator *allocator);
/* QueryPing methods */
void   query_ping__init
                     (QueryPing         *message);
size_t query_ping__get_packed_size
                     (const QueryPing   *message);
size_t query_ping__pack
                     (const QueryPing   *message,
                      uint8_t             *out);
size_t query_ping__pack_to_buffer
                     (const QueryPing   *message,
                      ProtobufCBuffer     *buffer);
QueryPing *
       query_ping__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query_ping__free_unpacked
                     (QueryPing *message,
                      ProtobufCAllocator *allocator);
/* ResPing methods */
void   res_ping__init
                     (ResPing         *message);
size_t res_ping__get_packed_size
                     (const ResPing   *message);
size_t res_ping__pack
                     (const ResPing   *message,
                      uint8_t             *out);
size_t res_ping__pack_to_buffer
                     (const ResPing   *message,
                      ProtobufCBuffer     *buffer);
ResPing *
       res_ping__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   res_ping__free_unpacked
                     (ResPing *message,
                      ProtobufCAllocator *allocator);
/* QueryAccountPending methods */
void   query_account_pending__init
                     (QueryAccountPending         *message);
size_t query_account_pending__get_packed_size
                     (const QueryAccountPending   *message);
size_t query_account_pending__pack
                     (const QueryAccountPending   *message,
                      uint8_t             *out);
size_t query_account_pending__pack_to_buffer
                     (const QueryAccountPending   *message,
                      ProtobufCBuffer     *buffer);
QueryAccountPending *
       query_account_pending__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query_account_pending__free_unpacked
                     (QueryAccountPending *message,
                      ProtobufCAllocator *allocator);
/* ResAccountPending methods */
void   res_account_pending__init
                     (ResAccountPending         *message);
size_t res_account_pending__get_packed_size
                     (const ResAccountPending   *message);
size_t res_account_pending__pack
                     (const ResAccountPending   *message,
                      uint8_t             *out);
size_t res_account_pending__pack_to_buffer
                     (const ResAccountPending   *message,
                      ProtobufCBuffer     *buffer);
ResAccountPending *
       res_account_pending__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   res_account_pending__free_unpacked
                     (ResAccountPending *message,
                      ProtobufCAllocator *allocator);
/* AccountPending methods */
void   account_pending__init
                     (AccountPending         *message);
size_t account_pending__get_packed_size
                     (const AccountPending   *message);
size_t account_pending__pack
                     (const AccountPending   *message,
                      uint8_t             *out);
size_t account_pending__pack_to_buffer
                     (const AccountPending   *message,
                      ProtobufCBuffer     *buffer);
AccountPending *
       account_pending__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   account_pending__free_unpacked
                     (AccountPending *message,
                      ProtobufCAllocator *allocator);
/* AccountPendingBlockInfo methods */
void   account_pending_block_info__init
                     (AccountPendingBlockInfo         *message);
size_t account_pending_block_info__get_packed_size
                     (const AccountPendingBlockInfo   *message);
size_t account_pending_block_info__pack
                     (const AccountPendingBlockInfo   *message,
                      uint8_t             *out);
size_t account_pending_block_info__pack_to_buffer
                     (const AccountPendingBlockInfo   *message,
                      ProtobufCBuffer     *buffer);
AccountPendingBlockInfo *
       account_pending_block_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   account_pending_block_info__free_unpacked
                     (AccountPendingBlockInfo *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Query_Closure)
                 (const Query *message,
                  void *closure_data);
typedef void (*Response_Closure)
                 (const Response *message,
                  void *closure_data);
typedef void (*QueryClientConnect_Closure)
                 (const QueryClientConnect *message,
                  void *closure_data);
typedef void (*ResClientConnect_Closure)
                 (const ResClientConnect *message,
                  void *closure_data);
typedef void (*QueryPing_Closure)
                 (const QueryPing *message,
                  void *closure_data);
typedef void (*ResPing_Closure)
                 (const ResPing *message,
                  void *closure_data);
typedef void (*QueryAccountPending_Closure)
                 (const QueryAccountPending *message,
                  void *closure_data);
typedef void (*ResAccountPending_Closure)
                 (const ResAccountPending *message,
                  void *closure_data);
typedef void (*AccountPending_Closure)
                 (const AccountPending *message,
                  void *closure_data);
typedef void (*AccountPendingBlockInfo_Closure)
                 (const AccountPendingBlockInfo *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    query_type__descriptor;
extern const ProtobufCEnumDescriptor    result__descriptor;
extern const ProtobufCMessageDescriptor query__descriptor;
extern const ProtobufCMessageDescriptor response__descriptor;
extern const ProtobufCMessageDescriptor query_client_connect__descriptor;
extern const ProtobufCMessageDescriptor res_client_connect__descriptor;
extern const ProtobufCMessageDescriptor query_ping__descriptor;
extern const ProtobufCMessageDescriptor res_ping__descriptor;
extern const ProtobufCMessageDescriptor query_account_pending__descriptor;
extern const ProtobufCMessageDescriptor res_account_pending__descriptor;
extern const ProtobufCMessageDescriptor account_pending__descriptor;
extern const ProtobufCMessageDescriptor account_pending_block_info__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_core_2eproto__INCLUDED */
