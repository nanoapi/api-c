/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: util.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "util.pb-c.h"
void   req_address_valid__init
                     (ReqAddressValid         *message)
{
  static const ReqAddressValid init_value = REQ_ADDRESS_VALID__INIT;
  *message = init_value;
}
size_t req_address_valid__get_packed_size
                     (const ReqAddressValid *message)
{
  assert(message->base.descriptor == &req_address_valid__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t req_address_valid__pack
                     (const ReqAddressValid *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &req_address_valid__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t req_address_valid__pack_to_buffer
                     (const ReqAddressValid *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &req_address_valid__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ReqAddressValid *
       req_address_valid__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ReqAddressValid *)
     protobuf_c_message_unpack (&req_address_valid__descriptor,
                                allocator, len, data);
}
void   req_address_valid__free_unpacked
                     (ReqAddressValid *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &req_address_valid__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   res_address_valid__init
                     (ResAddressValid         *message)
{
  static const ResAddressValid init_value = RES_ADDRESS_VALID__INIT;
  *message = init_value;
}
size_t res_address_valid__get_packed_size
                     (const ResAddressValid *message)
{
  assert(message->base.descriptor == &res_address_valid__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t res_address_valid__pack
                     (const ResAddressValid *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &res_address_valid__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t res_address_valid__pack_to_buffer
                     (const ResAddressValid *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &res_address_valid__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ResAddressValid *
       res_address_valid__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ResAddressValid *)
     protobuf_c_message_unpack (&res_address_valid__descriptor,
                                allocator, len, data);
}
void   res_address_valid__free_unpacked
                     (ResAddressValid *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &res_address_valid__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor req_address_valid__field_descriptors[1] =
{
  {
    "address",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ReqAddressValid, address),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned req_address_valid__field_indices_by_name[] = {
  0,   /* field[0] = address */
};
static const ProtobufCIntRange req_address_valid__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor req_address_valid__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "req_address_valid",
  "ReqAddressValid",
  "ReqAddressValid",
  "",
  sizeof(ReqAddressValid),
  1,
  req_address_valid__field_descriptors,
  req_address_valid__field_indices_by_name,
  1,  req_address_valid__number_ranges,
  (ProtobufCMessageInit) req_address_valid__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor res_address_valid__field_descriptors[2] =
{
  {
    "valid",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(ResAddressValid, valid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "reason",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ResAddressValid, reason),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned res_address_valid__field_indices_by_name[] = {
  1,   /* field[1] = reason */
  0,   /* field[0] = valid */
};
static const ProtobufCIntRange res_address_valid__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor res_address_valid__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "res_address_valid",
  "ResAddressValid",
  "ResAddressValid",
  "",
  sizeof(ResAddressValid),
  2,
  res_address_valid__field_descriptors,
  res_address_valid__field_indices_by_name,
  1,  res_address_valid__number_ranges,
  (ProtobufCMessageInit) res_address_valid__init,
  NULL,NULL,NULL    /* reserved[123] */
};