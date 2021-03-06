// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: util.proto

#ifndef PROTOBUF_util_2eproto__INCLUDED
#define PROTOBUF_util_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_util_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsreq_address_validImpl();
void InitDefaultsreq_address_valid();
void InitDefaultsres_address_validImpl();
void InitDefaultsres_address_valid();
inline void InitDefaults() {
  InitDefaultsreq_address_valid();
  InitDefaultsres_address_valid();
}
}  // namespace protobuf_util_2eproto
namespace nano {
namespace api {
class req_address_valid;
class req_address_validDefaultTypeInternal;
extern req_address_validDefaultTypeInternal _req_address_valid_default_instance_;
class res_address_valid;
class res_address_validDefaultTypeInternal;
extern res_address_validDefaultTypeInternal _res_address_valid_default_instance_;
}  // namespace api
}  // namespace nano
namespace nano {
namespace api {

// ===================================================================

class req_address_valid : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nano.api.req_address_valid) */ {
 public:
  req_address_valid();
  virtual ~req_address_valid();

  req_address_valid(const req_address_valid& from);

  inline req_address_valid& operator=(const req_address_valid& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  req_address_valid(req_address_valid&& from) noexcept
    : req_address_valid() {
    *this = ::std::move(from);
  }

  inline req_address_valid& operator=(req_address_valid&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const req_address_valid& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const req_address_valid* internal_default_instance() {
    return reinterpret_cast<const req_address_valid*>(
               &_req_address_valid_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(req_address_valid* other);
  friend void swap(req_address_valid& a, req_address_valid& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline req_address_valid* New() const PROTOBUF_FINAL { return New(NULL); }

  req_address_valid* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const req_address_valid& from);
  void MergeFrom(const req_address_valid& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(req_address_valid* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string address = 1;
  void clear_address();
  static const int kAddressFieldNumber = 1;
  const ::std::string& address() const;
  void set_address(const ::std::string& value);
  #if LANG_CXX11
  void set_address(::std::string&& value);
  #endif
  void set_address(const char* value);
  void set_address(const char* value, size_t size);
  ::std::string* mutable_address();
  ::std::string* release_address();
  void set_allocated_address(::std::string* address);

  // @@protoc_insertion_point(class_scope:nano.api.req_address_valid)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr address_;
  mutable int _cached_size_;
  friend struct ::protobuf_util_2eproto::TableStruct;
  friend void ::protobuf_util_2eproto::InitDefaultsreq_address_validImpl();
};
// -------------------------------------------------------------------

class res_address_valid : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nano.api.res_address_valid) */ {
 public:
  res_address_valid();
  virtual ~res_address_valid();

  res_address_valid(const res_address_valid& from);

  inline res_address_valid& operator=(const res_address_valid& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  res_address_valid(res_address_valid&& from) noexcept
    : res_address_valid() {
    *this = ::std::move(from);
  }

  inline res_address_valid& operator=(res_address_valid&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const res_address_valid& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const res_address_valid* internal_default_instance() {
    return reinterpret_cast<const res_address_valid*>(
               &_res_address_valid_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(res_address_valid* other);
  friend void swap(res_address_valid& a, res_address_valid& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline res_address_valid* New() const PROTOBUF_FINAL { return New(NULL); }

  res_address_valid* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const res_address_valid& from);
  void MergeFrom(const res_address_valid& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(res_address_valid* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string reason = 2;
  void clear_reason();
  static const int kReasonFieldNumber = 2;
  const ::std::string& reason() const;
  void set_reason(const ::std::string& value);
  #if LANG_CXX11
  void set_reason(::std::string&& value);
  #endif
  void set_reason(const char* value);
  void set_reason(const char* value, size_t size);
  ::std::string* mutable_reason();
  ::std::string* release_reason();
  void set_allocated_reason(::std::string* reason);

  // bool valid = 1;
  void clear_valid();
  static const int kValidFieldNumber = 1;
  bool valid() const;
  void set_valid(bool value);

  // @@protoc_insertion_point(class_scope:nano.api.res_address_valid)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr reason_;
  bool valid_;
  mutable int _cached_size_;
  friend struct ::protobuf_util_2eproto::TableStruct;
  friend void ::protobuf_util_2eproto::InitDefaultsres_address_validImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// req_address_valid

// string address = 1;
inline void req_address_valid::clear_address() {
  address_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& req_address_valid::address() const {
  // @@protoc_insertion_point(field_get:nano.api.req_address_valid.address)
  return address_.GetNoArena();
}
inline void req_address_valid::set_address(const ::std::string& value) {
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:nano.api.req_address_valid.address)
}
#if LANG_CXX11
inline void req_address_valid::set_address(::std::string&& value) {
  
  address_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:nano.api.req_address_valid.address)
}
#endif
inline void req_address_valid::set_address(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:nano.api.req_address_valid.address)
}
inline void req_address_valid::set_address(const char* value, size_t size) {
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:nano.api.req_address_valid.address)
}
inline ::std::string* req_address_valid::mutable_address() {
  
  // @@protoc_insertion_point(field_mutable:nano.api.req_address_valid.address)
  return address_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* req_address_valid::release_address() {
  // @@protoc_insertion_point(field_release:nano.api.req_address_valid.address)
  
  return address_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void req_address_valid::set_allocated_address(::std::string* address) {
  if (address != NULL) {
    
  } else {
    
  }
  address_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), address);
  // @@protoc_insertion_point(field_set_allocated:nano.api.req_address_valid.address)
}

// -------------------------------------------------------------------

// res_address_valid

// bool valid = 1;
inline void res_address_valid::clear_valid() {
  valid_ = false;
}
inline bool res_address_valid::valid() const {
  // @@protoc_insertion_point(field_get:nano.api.res_address_valid.valid)
  return valid_;
}
inline void res_address_valid::set_valid(bool value) {
  
  valid_ = value;
  // @@protoc_insertion_point(field_set:nano.api.res_address_valid.valid)
}

// string reason = 2;
inline void res_address_valid::clear_reason() {
  reason_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& res_address_valid::reason() const {
  // @@protoc_insertion_point(field_get:nano.api.res_address_valid.reason)
  return reason_.GetNoArena();
}
inline void res_address_valid::set_reason(const ::std::string& value) {
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:nano.api.res_address_valid.reason)
}
#if LANG_CXX11
inline void res_address_valid::set_reason(::std::string&& value) {
  
  reason_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:nano.api.res_address_valid.reason)
}
#endif
inline void res_address_valid::set_reason(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:nano.api.res_address_valid.reason)
}
inline void res_address_valid::set_reason(const char* value, size_t size) {
  
  reason_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:nano.api.res_address_valid.reason)
}
inline ::std::string* res_address_valid::mutable_reason() {
  
  // @@protoc_insertion_point(field_mutable:nano.api.res_address_valid.reason)
  return reason_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* res_address_valid::release_reason() {
  // @@protoc_insertion_point(field_release:nano.api.res_address_valid.reason)
  
  return reason_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void res_address_valid::set_allocated_reason(::std::string* reason) {
  if (reason != NULL) {
    
  } else {
    
  }
  reason_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), reason);
  // @@protoc_insertion_point(field_set_allocated:nano.api.res_address_valid.reason)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace api
}  // namespace nano

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_util_2eproto__INCLUDED
