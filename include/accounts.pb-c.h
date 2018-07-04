/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: accounts.proto */

#ifndef PROTOBUF_C_accounts_2eproto__INCLUDED
#define PROTOBUF_C_accounts_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "google/protobuf/wrappers.pb-c.h"

typedef struct _ReqAccountPending ReqAccountPending;
typedef struct _ResAccountPending ResAccountPending;
typedef struct _AccountPending AccountPending;
typedef struct _AccountPendingBlockInfo AccountPendingBlockInfo;


/* --- enums --- */


/* --- messages --- */

/*
 ** Returns a list of block hashes which have not yet been received by these accounts 
 */
struct  _ReqAccountPending
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
#define REQ_ACCOUNT_PENDING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&req_account_pending__descriptor) \
    , 0,NULL, 0, 0, NULL }


/*
 ** account_pending result 
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
 ** Information supplied for each account in req_account_pending 
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


/* ReqAccountPending methods */
void   req_account_pending__init
                     (ReqAccountPending         *message);
size_t req_account_pending__get_packed_size
                     (const ReqAccountPending   *message);
size_t req_account_pending__pack
                     (const ReqAccountPending   *message,
                      uint8_t             *out);
size_t req_account_pending__pack_to_buffer
                     (const ReqAccountPending   *message,
                      ProtobufCBuffer     *buffer);
ReqAccountPending *
       req_account_pending__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   req_account_pending__free_unpacked
                     (ReqAccountPending *message,
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

typedef void (*ReqAccountPending_Closure)
                 (const ReqAccountPending *message,
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

extern const ProtobufCMessageDescriptor req_account_pending__descriptor;
extern const ProtobufCMessageDescriptor res_account_pending__descriptor;
extern const ProtobufCMessageDescriptor account_pending__descriptor;
extern const ProtobufCMessageDescriptor account_pending_block_info__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_accounts_2eproto__INCLUDED */