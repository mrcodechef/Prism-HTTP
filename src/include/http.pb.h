// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: http.proto

#ifndef PROTOBUF_INCLUDED_http_2eproto
#define PROTOBUF_INCLUDED_http_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/extension_set.h> // IWYU pragma: export
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h> // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "tcp.pb.h"
#include "tls.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_http_2eproto

namespace protobuf_http_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable
      serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
} // namespace protobuf_http_2eproto
namespace prism {
class HTTPHandoffReply;
class HTTPHandoffReplyDefaultTypeInternal;
extern HTTPHandoffReplyDefaultTypeInternal _HTTPHandoffReply_default_instance_;
class HTTPHandoffReq;
class HTTPHandoffReqDefaultTypeInternal;
extern HTTPHandoffReqDefaultTypeInternal _HTTPHandoffReq_default_instance_;
class HTTPHeader;
class HTTPHeaderDefaultTypeInternal;
extern HTTPHeaderDefaultTypeInternal _HTTPHeader_default_instance_;
class HTTPReq;
class HTTPReqDefaultTypeInternal;
extern HTTPReqDefaultTypeInternal _HTTPReq_default_instance_;
} // namespace prism
namespace google {
namespace protobuf {
template <>
::prism::HTTPHandoffReply *
Arena::CreateMaybeMessage<::prism::HTTPHandoffReply>(Arena *);
template <>
::prism::HTTPHandoffReq *
Arena::CreateMaybeMessage<::prism::HTTPHandoffReq>(Arena *);
template <>
::prism::HTTPHeader *Arena::CreateMaybeMessage<::prism::HTTPHeader>(Arena *);
template <>
::prism::HTTPReq *Arena::CreateMaybeMessage<::prism::HTTPReq>(Arena *);
} // namespace protobuf
} // namespace google
namespace prism {

// ===================================================================

class HTTPHeader
    : public ::google::protobuf::
          Message /* @@protoc_insertion_point(class_definition:prism.HTTPHeader)
                   */
{
public:
  HTTPHeader();
  virtual ~HTTPHeader();

  HTTPHeader(const HTTPHeader &from);

  inline HTTPHeader &
  operator=(const HTTPHeader &from)
  {
    CopyFrom(from);
    return *this;
  }
#if LANG_CXX11
  HTTPHeader(HTTPHeader &&from) noexcept : HTTPHeader()
  {
    *this = ::std::move(from);
  }

  inline HTTPHeader &
  operator=(HTTPHeader &&from) noexcept
  {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from)
        InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
#endif
  static const ::google::protobuf::Descriptor *descriptor();
  static const HTTPHeader &default_instance();

  static void InitAsDefaultInstance(); // FOR INTERNAL USE ONLY
  static inline const HTTPHeader *
  internal_default_instance()
  {
    return reinterpret_cast<const HTTPHeader *>(&_HTTPHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;

  void Swap(HTTPHeader *other);
  friend void
  swap(HTTPHeader &a, HTTPHeader &b)
  {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HTTPHeader *
  New() const final
  {
    return CreateMaybeMessage<HTTPHeader>(NULL);
  }

  HTTPHeader *
  New(::google::protobuf::Arena *arena) const final
  {
    return CreateMaybeMessage<HTTPHeader>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message &from) final;
  void MergeFrom(const ::google::protobuf::Message &from) final;
  void CopyFrom(const HTTPHeader &from);
  void MergeFrom(const HTTPHeader &from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream *input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream *output) const final;
  ::google::protobuf::uint8 *InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8 *target) const final;
  int
  GetCachedSize() const final
  {
    return _cached_size_.Get();
  }

private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HTTPHeader *other);

private:
  inline ::google::protobuf::Arena *
  GetArenaNoVirtual() const
  {
    return NULL;
  }
  inline void *
  MaybeArenaPtr() const
  {
    return NULL;
  }

public:
  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 name_ofs = 1;
  void clear_name_ofs();
  static const int kNameOfsFieldNumber = 1;
  ::google::protobuf::uint64 name_ofs() const;
  void set_name_ofs(::google::protobuf::uint64 value);

  // uint64 name_len = 2;
  void clear_name_len();
  static const int kNameLenFieldNumber = 2;
  ::google::protobuf::uint64 name_len() const;
  void set_name_len(::google::protobuf::uint64 value);

  // uint64 val_ofs = 3;
  void clear_val_ofs();
  static const int kValOfsFieldNumber = 3;
  ::google::protobuf::uint64 val_ofs() const;
  void set_val_ofs(::google::protobuf::uint64 value);

  // uint64 val_len = 4;
  void clear_val_len();
  static const int kValLenFieldNumber = 4;
  ::google::protobuf::uint64 val_len() const;
  void set_val_len(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:prism.HTTPHeader)
private:
  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 name_ofs_;
  ::google::protobuf::uint64 name_len_;
  ::google::protobuf::uint64 val_ofs_;
  ::google::protobuf::uint64 val_len_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_http_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class HTTPReq
    : public ::google::protobuf::
          Message /* @@protoc_insertion_point(class_definition:prism.HTTPReq)
                   */
{
public:
  HTTPReq();
  virtual ~HTTPReq();

  HTTPReq(const HTTPReq &from);

  inline HTTPReq &
  operator=(const HTTPReq &from)
  {
    CopyFrom(from);
    return *this;
  }
#if LANG_CXX11
  HTTPReq(HTTPReq &&from) noexcept : HTTPReq() { *this = ::std::move(from); }

  inline HTTPReq &
  operator=(HTTPReq &&from) noexcept
  {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from)
        InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
#endif
  static const ::google::protobuf::Descriptor *descriptor();
  static const HTTPReq &default_instance();

  static void InitAsDefaultInstance(); // FOR INTERNAL USE ONLY
  static inline const HTTPReq *
  internal_default_instance()
  {
    return reinterpret_cast<const HTTPReq *>(&_HTTPReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;

  void Swap(HTTPReq *other);
  friend void
  swap(HTTPReq &a, HTTPReq &b)
  {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HTTPReq *
  New() const final
  {
    return CreateMaybeMessage<HTTPReq>(NULL);
  }

  HTTPReq *
  New(::google::protobuf::Arena *arena) const final
  {
    return CreateMaybeMessage<HTTPReq>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message &from) final;
  void MergeFrom(const ::google::protobuf::Message &from) final;
  void CopyFrom(const HTTPReq &from);
  void MergeFrom(const HTTPReq &from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream *input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream *output) const final;
  ::google::protobuf::uint8 *InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8 *target) const final;
  int
  GetCachedSize() const final
  {
    return _cached_size_.Get();
  }

private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HTTPReq *other);

private:
  inline ::google::protobuf::Arena *
  GetArenaNoVirtual() const
  {
    return NULL;
  }
  inline void *
  MaybeArenaPtr() const
  {
    return NULL;
  }

public:
  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .prism.HTTPHeader headers = 10;
  int headers_size() const;
  void clear_headers();
  static const int kHeadersFieldNumber = 10;
  ::prism::HTTPHeader *mutable_headers(int index);
  ::google::protobuf::RepeatedPtrField<::prism::HTTPHeader> *mutable_headers();
  const ::prism::HTTPHeader &headers(int index) const;
  ::prism::HTTPHeader *add_headers();
  const ::google::protobuf::RepeatedPtrField<::prism::HTTPHeader> &
  headers() const;

  // bytes buf = 1;
  void clear_buf();
  static const int kBufFieldNumber = 1;
  const ::std::string &buf() const;
  void set_buf(const ::std::string &value);
#if LANG_CXX11
  void set_buf(::std::string &&value);
#endif
  void set_buf(const char *value);
  void set_buf(const void *value, size_t size);
  ::std::string *mutable_buf();
  ::std::string *release_buf();
  void set_allocated_buf(::std::string *buf);

  // uint64 method_ofs = 3;
  void clear_method_ofs();
  static const int kMethodOfsFieldNumber = 3;
  ::google::protobuf::uint64 method_ofs() const;
  void set_method_ofs(::google::protobuf::uint64 value);

  // uint64 method_len = 4;
  void clear_method_len();
  static const int kMethodLenFieldNumber = 4;
  ::google::protobuf::uint64 method_len() const;
  void set_method_len(::google::protobuf::uint64 value);

  // uint64 path_ofs = 5;
  void clear_path_ofs();
  static const int kPathOfsFieldNumber = 5;
  ::google::protobuf::uint64 path_ofs() const;
  void set_path_ofs(::google::protobuf::uint64 value);

  // uint64 path_len = 6;
  void clear_path_len();
  static const int kPathLenFieldNumber = 6;
  ::google::protobuf::uint64 path_len() const;
  void set_path_len(::google::protobuf::uint64 value);

  // uint64 body_ofs = 7;
  void clear_body_ofs();
  static const int kBodyOfsFieldNumber = 7;
  ::google::protobuf::uint64 body_ofs() const;
  void set_body_ofs(::google::protobuf::uint64 value);

  // uint64 body_len = 8;
  void clear_body_len();
  static const int kBodyLenFieldNumber = 8;
  ::google::protobuf::uint64 body_len() const;
  void set_body_len(::google::protobuf::uint64 value);

  // uint64 nheaders = 9;
  void clear_nheaders();
  static const int kNheadersFieldNumber = 9;
  ::google::protobuf::uint64 nheaders() const;
  void set_nheaders(::google::protobuf::uint64 value);

  // uint32 minor_version = 2;
  void clear_minor_version();
  static const int kMinorVersionFieldNumber = 2;
  ::google::protobuf::uint32 minor_version() const;
  void set_minor_version(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:prism.HTTPReq)
private:
  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField<::prism::HTTPHeader> headers_;
  ::google::protobuf::internal::ArenaStringPtr buf_;
  ::google::protobuf::uint64 method_ofs_;
  ::google::protobuf::uint64 method_len_;
  ::google::protobuf::uint64 path_ofs_;
  ::google::protobuf::uint64 path_len_;
  ::google::protobuf::uint64 body_ofs_;
  ::google::protobuf::uint64 body_len_;
  ::google::protobuf::uint64 nheaders_;
  ::google::protobuf::uint32 minor_version_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_http_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class HTTPHandoffReq
    : public ::google::protobuf::
          Message /* @@protoc_insertion_point(class_definition:prism.HTTPHandoffReq)
                   */
{
public:
  HTTPHandoffReq();
  virtual ~HTTPHandoffReq();

  HTTPHandoffReq(const HTTPHandoffReq &from);

  inline HTTPHandoffReq &
  operator=(const HTTPHandoffReq &from)
  {
    CopyFrom(from);
    return *this;
  }
#if LANG_CXX11
  HTTPHandoffReq(HTTPHandoffReq &&from) noexcept : HTTPHandoffReq()
  {
    *this = ::std::move(from);
  }

  inline HTTPHandoffReq &
  operator=(HTTPHandoffReq &&from) noexcept
  {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from)
        InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
#endif
  static const ::google::protobuf::Descriptor *descriptor();
  static const HTTPHandoffReq &default_instance();

  static void InitAsDefaultInstance(); // FOR INTERNAL USE ONLY
  static inline const HTTPHandoffReq *
  internal_default_instance()
  {
    return reinterpret_cast<const HTTPHandoffReq *>(
        &_HTTPHandoffReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 2;

  void Swap(HTTPHandoffReq *other);
  friend void
  swap(HTTPHandoffReq &a, HTTPHandoffReq &b)
  {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HTTPHandoffReq *
  New() const final
  {
    return CreateMaybeMessage<HTTPHandoffReq>(NULL);
  }

  HTTPHandoffReq *
  New(::google::protobuf::Arena *arena) const final
  {
    return CreateMaybeMessage<HTTPHandoffReq>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message &from) final;
  void MergeFrom(const ::google::protobuf::Message &from) final;
  void CopyFrom(const HTTPHandoffReq &from);
  void MergeFrom(const HTTPHandoffReq &from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream *input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream *output) const final;
  ::google::protobuf::uint8 *InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8 *target) const final;
  int
  GetCachedSize() const final
  {
    return _cached_size_.Get();
  }

private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HTTPHandoffReq *other);

private:
  inline ::google::protobuf::Arena *
  GetArenaNoVirtual() const
  {
    return NULL;
  }
  inline void *
  MaybeArenaPtr() const
  {
    return NULL;
  }

public:
  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .prism.TCPState tcp = 1;
  bool has_tcp() const;
  void clear_tcp();
  static const int kTcpFieldNumber = 1;

private:
  const ::prism::TCPState &_internal_tcp() const;

public:
  const ::prism::TCPState &tcp() const;
  ::prism::TCPState *release_tcp();
  ::prism::TCPState *mutable_tcp();
  void set_allocated_tcp(::prism::TCPState *tcp);

  // .prism.TLSState tls = 2;
  bool has_tls() const;
  void clear_tls();
  static const int kTlsFieldNumber = 2;

private:
  const ::prism::TLSState &_internal_tls() const;

public:
  const ::prism::TLSState &tls() const;
  ::prism::TLSState *release_tls();
  ::prism::TLSState *mutable_tls();
  void set_allocated_tls(::prism::TLSState *tls);

  // .prism.HTTPReq http = 3;
  bool has_http() const;
  void clear_http();
  static const int kHttpFieldNumber = 3;

private:
  const ::prism::HTTPReq &_internal_http() const;

public:
  const ::prism::HTTPReq &http() const;
  ::prism::HTTPReq *release_http();
  ::prism::HTTPReq *mutable_http();
  void set_allocated_http(::prism::HTTPReq *http);

  // @@protoc_insertion_point(class_scope:prism.HTTPHandoffReq)
private:
  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::prism::TCPState *tcp_;
  ::prism::TLSState *tls_;
  ::prism::HTTPReq *http_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_http_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class HTTPHandoffReply
    : public ::google::protobuf::
          Message /* @@protoc_insertion_point(class_definition:prism.HTTPHandoffReply)
                   */
{
public:
  HTTPHandoffReply();
  virtual ~HTTPHandoffReply();

  HTTPHandoffReply(const HTTPHandoffReply &from);

  inline HTTPHandoffReply &
  operator=(const HTTPHandoffReply &from)
  {
    CopyFrom(from);
    return *this;
  }
#if LANG_CXX11
  HTTPHandoffReply(HTTPHandoffReply &&from) noexcept : HTTPHandoffReply()
  {
    *this = ::std::move(from);
  }

  inline HTTPHandoffReply &
  operator=(HTTPHandoffReply &&from) noexcept
  {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from)
        InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
#endif
  static const ::google::protobuf::Descriptor *descriptor();
  static const HTTPHandoffReply &default_instance();

  static void InitAsDefaultInstance(); // FOR INTERNAL USE ONLY
  static inline const HTTPHandoffReply *
  internal_default_instance()
  {
    return reinterpret_cast<const HTTPHandoffReply *>(
        &_HTTPHandoffReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 3;

  void Swap(HTTPHandoffReply *other);
  friend void
  swap(HTTPHandoffReply &a, HTTPHandoffReply &b)
  {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HTTPHandoffReply *
  New() const final
  {
    return CreateMaybeMessage<HTTPHandoffReply>(NULL);
  }

  HTTPHandoffReply *
  New(::google::protobuf::Arena *arena) const final
  {
    return CreateMaybeMessage<HTTPHandoffReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message &from) final;
  void MergeFrom(const ::google::protobuf::Message &from) final;
  void CopyFrom(const HTTPHandoffReply &from);
  void MergeFrom(const HTTPHandoffReply &from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream *input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream *output) const final;
  ::google::protobuf::uint8 *InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8 *target) const final;
  int
  GetCachedSize() const final
  {
    return _cached_size_.Get();
  }

private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HTTPHandoffReply *other);

private:
  inline ::google::protobuf::Arena *
  GetArenaNoVirtual() const
  {
    return NULL;
  }
  inline void *
  MaybeArenaPtr() const
  {
    return NULL;
  }

public:
  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 error = 1;
  void clear_error();
  static const int kErrorFieldNumber = 1;
  ::google::protobuf::int32 error() const;
  void set_error(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:prism.HTTPHandoffReply)
private:
  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 error_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_http_2eproto::TableStruct;
};
// ===================================================================

// ===================================================================

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif // __GNUC__
// HTTPHeader

// uint64 name_ofs = 1;
inline void
HTTPHeader::clear_name_ofs()
{
  name_ofs_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPHeader::name_ofs() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPHeader.name_ofs)
  return name_ofs_;
}
inline void
HTTPHeader::set_name_ofs(::google::protobuf::uint64 value)
{
  name_ofs_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPHeader.name_ofs)
}

// uint64 name_len = 2;
inline void
HTTPHeader::clear_name_len()
{
  name_len_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPHeader::name_len() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPHeader.name_len)
  return name_len_;
}
inline void
HTTPHeader::set_name_len(::google::protobuf::uint64 value)
{
  name_len_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPHeader.name_len)
}

// uint64 val_ofs = 3;
inline void
HTTPHeader::clear_val_ofs()
{
  val_ofs_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPHeader::val_ofs() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPHeader.val_ofs)
  return val_ofs_;
}
inline void
HTTPHeader::set_val_ofs(::google::protobuf::uint64 value)
{
  val_ofs_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPHeader.val_ofs)
}

// uint64 val_len = 4;
inline void
HTTPHeader::clear_val_len()
{
  val_len_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPHeader::val_len() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPHeader.val_len)
  return val_len_;
}
inline void
HTTPHeader::set_val_len(::google::protobuf::uint64 value)
{
  val_len_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPHeader.val_len)
}

// -------------------------------------------------------------------

// HTTPReq

// bytes buf = 1;
inline void
HTTPReq::clear_buf()
{
  buf_.ClearToEmptyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string &
HTTPReq::buf() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.buf)
  return buf_.GetNoArena();
}
inline void
HTTPReq::set_buf(const ::std::string &value)
{
  buf_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
                  value);
  // @@protoc_insertion_point(field_set:prism.HTTPReq.buf)
}
#if LANG_CXX11
inline void
HTTPReq::set_buf(::std::string &&value)
{
  buf_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
                  ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:prism.HTTPReq.buf)
}
#endif
inline void
HTTPReq::set_buf(const char *value)
{
  GOOGLE_DCHECK(value != NULL);

  buf_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
                  ::std::string(value));
  // @@protoc_insertion_point(field_set_char:prism.HTTPReq.buf)
}
inline void
HTTPReq::set_buf(const void *value, size_t size)
{
  buf_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
                  ::std::string(reinterpret_cast<const char *>(value), size));
  // @@protoc_insertion_point(field_set_pointer:prism.HTTPReq.buf)
}
inline ::std::string *
HTTPReq::mutable_buf()
{
  // @@protoc_insertion_point(field_mutable:prism.HTTPReq.buf)
  return buf_.MutableNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string *
HTTPReq::release_buf()
{
  // @@protoc_insertion_point(field_release:prism.HTTPReq.buf)

  return buf_.ReleaseNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void
HTTPReq::set_allocated_buf(::std::string *buf)
{
  if (buf != NULL) {
  } else {
  }
  buf_.SetAllocatedNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited(), buf);
  // @@protoc_insertion_point(field_set_allocated:prism.HTTPReq.buf)
}

// uint32 minor_version = 2;
inline void
HTTPReq::clear_minor_version()
{
  minor_version_ = 0u;
}
inline ::google::protobuf::uint32
HTTPReq::minor_version() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.minor_version)
  return minor_version_;
}
inline void
HTTPReq::set_minor_version(::google::protobuf::uint32 value)
{
  minor_version_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.minor_version)
}

// uint64 method_ofs = 3;
inline void
HTTPReq::clear_method_ofs()
{
  method_ofs_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::method_ofs() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.method_ofs)
  return method_ofs_;
}
inline void
HTTPReq::set_method_ofs(::google::protobuf::uint64 value)
{
  method_ofs_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.method_ofs)
}

// uint64 method_len = 4;
inline void
HTTPReq::clear_method_len()
{
  method_len_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::method_len() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.method_len)
  return method_len_;
}
inline void
HTTPReq::set_method_len(::google::protobuf::uint64 value)
{
  method_len_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.method_len)
}

// uint64 path_ofs = 5;
inline void
HTTPReq::clear_path_ofs()
{
  path_ofs_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::path_ofs() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.path_ofs)
  return path_ofs_;
}
inline void
HTTPReq::set_path_ofs(::google::protobuf::uint64 value)
{
  path_ofs_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.path_ofs)
}

// uint64 path_len = 6;
inline void
HTTPReq::clear_path_len()
{
  path_len_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::path_len() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.path_len)
  return path_len_;
}
inline void
HTTPReq::set_path_len(::google::protobuf::uint64 value)
{
  path_len_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.path_len)
}

// uint64 body_ofs = 7;
inline void
HTTPReq::clear_body_ofs()
{
  body_ofs_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::body_ofs() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.body_ofs)
  return body_ofs_;
}
inline void
HTTPReq::set_body_ofs(::google::protobuf::uint64 value)
{
  body_ofs_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.body_ofs)
}

// uint64 body_len = 8;
inline void
HTTPReq::clear_body_len()
{
  body_len_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::body_len() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.body_len)
  return body_len_;
}
inline void
HTTPReq::set_body_len(::google::protobuf::uint64 value)
{
  body_len_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.body_len)
}

// uint64 nheaders = 9;
inline void
HTTPReq::clear_nheaders()
{
  nheaders_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64
HTTPReq::nheaders() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.nheaders)
  return nheaders_;
}
inline void
HTTPReq::set_nheaders(::google::protobuf::uint64 value)
{
  nheaders_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPReq.nheaders)
}

// repeated .prism.HTTPHeader headers = 10;
inline int
HTTPReq::headers_size() const
{
  return headers_.size();
}
inline void
HTTPReq::clear_headers()
{
  headers_.Clear();
}
inline ::prism::HTTPHeader *
HTTPReq::mutable_headers(int index)
{
  // @@protoc_insertion_point(field_mutable:prism.HTTPReq.headers)
  return headers_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::prism::HTTPHeader> *
HTTPReq::mutable_headers()
{
  // @@protoc_insertion_point(field_mutable_list:prism.HTTPReq.headers)
  return &headers_;
}
inline const ::prism::HTTPHeader &
HTTPReq::headers(int index) const
{
  // @@protoc_insertion_point(field_get:prism.HTTPReq.headers)
  return headers_.Get(index);
}
inline ::prism::HTTPHeader *
HTTPReq::add_headers()
{
  // @@protoc_insertion_point(field_add:prism.HTTPReq.headers)
  return headers_.Add();
}
inline const ::google::protobuf::RepeatedPtrField<::prism::HTTPHeader> &
HTTPReq::headers() const
{
  // @@protoc_insertion_point(field_list:prism.HTTPReq.headers)
  return headers_;
}

// -------------------------------------------------------------------

// HTTPHandoffReq

// .prism.TCPState tcp = 1;
inline bool
HTTPHandoffReq::has_tcp() const
{
  return this != internal_default_instance() && tcp_ != NULL;
}
inline const ::prism::TCPState &
HTTPHandoffReq::_internal_tcp() const
{
  return *tcp_;
}
inline const ::prism::TCPState &
HTTPHandoffReq::tcp() const
{
  const ::prism::TCPState *p = tcp_;
  // @@protoc_insertion_point(field_get:prism.HTTPHandoffReq.tcp)
  return p != NULL ? *p
                   : *reinterpret_cast<const ::prism::TCPState *>(
                         &::prism::_TCPState_default_instance_);
}
inline ::prism::TCPState *
HTTPHandoffReq::release_tcp()
{
  // @@protoc_insertion_point(field_release:prism.HTTPHandoffReq.tcp)

  ::prism::TCPState *temp = tcp_;
  tcp_ = NULL;
  return temp;
}
inline ::prism::TCPState *
HTTPHandoffReq::mutable_tcp()
{
  if (tcp_ == NULL) {
    auto *p = CreateMaybeMessage<::prism::TCPState>(GetArenaNoVirtual());
    tcp_ = p;
  }
  // @@protoc_insertion_point(field_mutable:prism.HTTPHandoffReq.tcp)
  return tcp_;
}
inline void
HTTPHandoffReq::set_allocated_tcp(::prism::TCPState *tcp)
{
  ::google::protobuf::Arena *message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast<::google::protobuf::MessageLite *>(tcp_);
  }
  if (tcp) {
    ::google::protobuf::Arena *submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      tcp = ::google::protobuf::internal::GetOwnedMessage(message_arena, tcp,
                                                          submessage_arena);
    }

  } else {
  }
  tcp_ = tcp;
  // @@protoc_insertion_point(field_set_allocated:prism.HTTPHandoffReq.tcp)
}

// .prism.TLSState tls = 2;
inline bool
HTTPHandoffReq::has_tls() const
{
  return this != internal_default_instance() && tls_ != NULL;
}
inline const ::prism::TLSState &
HTTPHandoffReq::_internal_tls() const
{
  return *tls_;
}
inline const ::prism::TLSState &
HTTPHandoffReq::tls() const
{
  const ::prism::TLSState *p = tls_;
  // @@protoc_insertion_point(field_get:prism.HTTPHandoffReq.tls)
  return p != NULL ? *p
                   : *reinterpret_cast<const ::prism::TLSState *>(
                         &::prism::_TLSState_default_instance_);
}
inline ::prism::TLSState *
HTTPHandoffReq::release_tls()
{
  // @@protoc_insertion_point(field_release:prism.HTTPHandoffReq.tls)

  ::prism::TLSState *temp = tls_;
  tls_ = NULL;
  return temp;
}
inline ::prism::TLSState *
HTTPHandoffReq::mutable_tls()
{
  if (tls_ == NULL) {
    auto *p = CreateMaybeMessage<::prism::TLSState>(GetArenaNoVirtual());
    tls_ = p;
  }
  // @@protoc_insertion_point(field_mutable:prism.HTTPHandoffReq.tls)
  return tls_;
}
inline void
HTTPHandoffReq::set_allocated_tls(::prism::TLSState *tls)
{
  ::google::protobuf::Arena *message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast<::google::protobuf::MessageLite *>(tls_);
  }
  if (tls) {
    ::google::protobuf::Arena *submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      tls = ::google::protobuf::internal::GetOwnedMessage(message_arena, tls,
                                                          submessage_arena);
    }

  } else {
  }
  tls_ = tls;
  // @@protoc_insertion_point(field_set_allocated:prism.HTTPHandoffReq.tls)
}

// .prism.HTTPReq http = 3;
inline bool
HTTPHandoffReq::has_http() const
{
  return this != internal_default_instance() && http_ != NULL;
}
inline void
HTTPHandoffReq::clear_http()
{
  if (GetArenaNoVirtual() == NULL && http_ != NULL) {
    delete http_;
  }
  http_ = NULL;
}
inline const ::prism::HTTPReq &
HTTPHandoffReq::_internal_http() const
{
  return *http_;
}
inline const ::prism::HTTPReq &
HTTPHandoffReq::http() const
{
  const ::prism::HTTPReq *p = http_;
  // @@protoc_insertion_point(field_get:prism.HTTPHandoffReq.http)
  return p != NULL ? *p
                   : *reinterpret_cast<const ::prism::HTTPReq *>(
                         &::prism::_HTTPReq_default_instance_);
}
inline ::prism::HTTPReq *
HTTPHandoffReq::release_http()
{
  // @@protoc_insertion_point(field_release:prism.HTTPHandoffReq.http)

  ::prism::HTTPReq *temp = http_;
  http_ = NULL;
  return temp;
}
inline ::prism::HTTPReq *
HTTPHandoffReq::mutable_http()
{
  if (http_ == NULL) {
    auto *p = CreateMaybeMessage<::prism::HTTPReq>(GetArenaNoVirtual());
    http_ = p;
  }
  // @@protoc_insertion_point(field_mutable:prism.HTTPHandoffReq.http)
  return http_;
}
inline void
HTTPHandoffReq::set_allocated_http(::prism::HTTPReq *http)
{
  ::google::protobuf::Arena *message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete http_;
  }
  if (http) {
    ::google::protobuf::Arena *submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      http = ::google::protobuf::internal::GetOwnedMessage(message_arena, http,
                                                           submessage_arena);
    }

  } else {
  }
  http_ = http;
  // @@protoc_insertion_point(field_set_allocated:prism.HTTPHandoffReq.http)
}

// -------------------------------------------------------------------

// HTTPHandoffReply

// int32 error = 1;
inline void
HTTPHandoffReply::clear_error()
{
  error_ = 0;
}
inline ::google::protobuf::int32
HTTPHandoffReply::error() const
{
  // @@protoc_insertion_point(field_get:prism.HTTPHandoffReply.error)
  return error_;
}
inline void
HTTPHandoffReply::set_error(::google::protobuf::int32 value)
{
  error_ = value;
  // @@protoc_insertion_point(field_set:prism.HTTPHandoffReply.error)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// @@protoc_insertion_point(namespace_scope)

} // namespace prism

// @@protoc_insertion_point(global_scope)

#endif // PROTOBUF_INCLUDED_http_2eproto
