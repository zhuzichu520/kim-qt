// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Message.proto

#include "Message.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace com {
namespace chuzi {
namespace imsdk {
namespace server {
namespace model {
namespace proto {
PROTOBUF_CONSTEXPR Message::Message(
    ::_pbi::ConstantInitialized)
  : id_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , content_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , sender_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , receiver_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , extra_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , title_(&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{})
  , scene_(0)
  , type_(0)
  , timestamp_(int64_t{0})
  , subtype_(0){}
struct MessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MessageDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MessageDefaultTypeInternal() {}
  union {
    Message _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MessageDefaultTypeInternal _Message_default_instance_;
}  // namespace proto
}  // namespace model
}  // namespace server
}  // namespace imsdk
}  // namespace chuzi
}  // namespace com
static ::_pb::Metadata file_level_metadata_Message_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Message_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Message_2eproto = nullptr;

const uint32_t TableStruct_Message_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, id_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, scene_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, content_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, sender_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, receiver_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, extra_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, title_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, type_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, subtype_),
  PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::Message, timestamp_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::com::chuzi::imsdk::server::model::proto::Message)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::com::chuzi::imsdk::server::model::proto::_Message_default_instance_._instance,
};

const char descriptor_table_protodef_Message_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rMessage.proto\022\"com.chuzi.imsdk.server."
  "model.proto\"\247\001\n\007Message\022\n\n\002id\030\001 \001(\t\022\r\n\005s"
  "cene\030\002 \001(\005\022\017\n\007content\030\003 \001(\t\022\016\n\006sender\030\004 "
  "\001(\t\022\020\n\010receiver\030\005 \001(\t\022\r\n\005extra\030\006 \001(\t\022\r\n\005"
  "title\030\007 \001(\t\022\014\n\004type\030\010 \001(\005\022\017\n\007subType\030\t \001"
  "(\005\022\021\n\ttimestamp\030\n \001(\003B\016B\014MessageProtob\006p"
  "roto3"
  ;
static ::_pbi::once_flag descriptor_table_Message_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Message_2eproto = {
    false, false, 245, descriptor_table_protodef_Message_2eproto,
    "Message.proto",
    &descriptor_table_Message_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_Message_2eproto::offsets,
    file_level_metadata_Message_2eproto, file_level_enum_descriptors_Message_2eproto,
    file_level_service_descriptors_Message_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Message_2eproto_getter() {
  return &descriptor_table_Message_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Message_2eproto(&descriptor_table_Message_2eproto);
namespace com {
namespace chuzi {
namespace imsdk {
namespace server {
namespace model {
namespace proto {

// ===================================================================

class Message::_Internal {
 public:
};

Message::Message(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:com.chuzi.imsdk.server.model.proto.Message)
}
Message::Message(const Message& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  id_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    id_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_id().empty()) {
    id_.Set(from._internal_id(), 
      GetArenaForAllocation());
  }
  content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_content().empty()) {
    content_.Set(from._internal_content(), 
      GetArenaForAllocation());
  }
  sender_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    sender_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_sender().empty()) {
    sender_.Set(from._internal_sender(), 
      GetArenaForAllocation());
  }
  receiver_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    receiver_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_receiver().empty()) {
    receiver_.Set(from._internal_receiver(), 
      GetArenaForAllocation());
  }
  extra_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    extra_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_extra().empty()) {
    extra_.Set(from._internal_extra(), 
      GetArenaForAllocation());
  }
  title_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    title_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_title().empty()) {
    title_.Set(from._internal_title(), 
      GetArenaForAllocation());
  }
  ::memcpy(&scene_, &from.scene_,
    static_cast<size_t>(reinterpret_cast<char*>(&subtype_) -
    reinterpret_cast<char*>(&scene_)) + sizeof(subtype_));
  // @@protoc_insertion_point(copy_constructor:com.chuzi.imsdk.server.model.proto.Message)
}

inline void Message::SharedCtor() {
id_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  id_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
content_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  content_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
sender_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  sender_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
receiver_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  receiver_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
extra_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  extra_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
title_.InitDefault();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  title_.Set("", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&scene_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&subtype_) -
    reinterpret_cast<char*>(&scene_)) + sizeof(subtype_));
}

Message::~Message() {
  // @@protoc_insertion_point(destructor:com.chuzi.imsdk.server.model.proto.Message)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Message::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  id_.Destroy();
  content_.Destroy();
  sender_.Destroy();
  receiver_.Destroy();
  extra_.Destroy();
  title_.Destroy();
}

void Message::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Message::Clear() {
// @@protoc_insertion_point(message_clear_start:com.chuzi.imsdk.server.model.proto.Message)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_.ClearToEmpty();
  content_.ClearToEmpty();
  sender_.ClearToEmpty();
  receiver_.ClearToEmpty();
  extra_.ClearToEmpty();
  title_.ClearToEmpty();
  ::memset(&scene_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&subtype_) -
      reinterpret_cast<char*>(&scene_)) + sizeof(subtype_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Message::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_id();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.id"));
        } else
          goto handle_unusual;
        continue;
      // int32 scene = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          scene_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string content = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_content();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.content"));
        } else
          goto handle_unusual;
        continue;
      // string sender = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_sender();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.sender"));
        } else
          goto handle_unusual;
        continue;
      // string receiver = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_receiver();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.receiver"));
        } else
          goto handle_unusual;
        continue;
      // string extra = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          auto str = _internal_mutable_extra();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.extra"));
        } else
          goto handle_unusual;
        continue;
      // string title = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          auto str = _internal_mutable_title();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "com.chuzi.imsdk.server.model.proto.Message.title"));
        } else
          goto handle_unusual;
        continue;
      // int32 type = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 64)) {
          type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 subType = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 72)) {
          subtype_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int64 timestamp = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 80)) {
          timestamp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Message::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.chuzi.imsdk.server.model.proto.Message)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_id().data(), static_cast<int>(this->_internal_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.id");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_id(), target);
  }

  // int32 scene = 2;
  if (this->_internal_scene() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_scene(), target);
  }

  // string content = 3;
  if (!this->_internal_content().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_content().data(), static_cast<int>(this->_internal_content().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.content");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_content(), target);
  }

  // string sender = 4;
  if (!this->_internal_sender().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_sender().data(), static_cast<int>(this->_internal_sender().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.sender");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_sender(), target);
  }

  // string receiver = 5;
  if (!this->_internal_receiver().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_receiver().data(), static_cast<int>(this->_internal_receiver().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.receiver");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_receiver(), target);
  }

  // string extra = 6;
  if (!this->_internal_extra().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_extra().data(), static_cast<int>(this->_internal_extra().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.extra");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_extra(), target);
  }

  // string title = 7;
  if (!this->_internal_title().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_title().data(), static_cast<int>(this->_internal_title().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "com.chuzi.imsdk.server.model.proto.Message.title");
    target = stream->WriteStringMaybeAliased(
        7, this->_internal_title(), target);
  }

  // int32 type = 8;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(8, this->_internal_type(), target);
  }

  // int32 subType = 9;
  if (this->_internal_subtype() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(9, this->_internal_subtype(), target);
  }

  // int64 timestamp = 10;
  if (this->_internal_timestamp() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(10, this->_internal_timestamp(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.chuzi.imsdk.server.model.proto.Message)
  return target;
}

size_t Message::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:com.chuzi.imsdk.server.model.proto.Message)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_id());
  }

  // string content = 3;
  if (!this->_internal_content().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_content());
  }

  // string sender = 4;
  if (!this->_internal_sender().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_sender());
  }

  // string receiver = 5;
  if (!this->_internal_receiver().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_receiver());
  }

  // string extra = 6;
  if (!this->_internal_extra().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_extra());
  }

  // string title = 7;
  if (!this->_internal_title().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_title());
  }

  // int32 scene = 2;
  if (this->_internal_scene() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_scene());
  }

  // int32 type = 8;
  if (this->_internal_type() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_type());
  }

  // int64 timestamp = 10;
  if (this->_internal_timestamp() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_timestamp());
  }

  // int32 subType = 9;
  if (this->_internal_subtype() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_subtype());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Message::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Message::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Message::GetClassData() const { return &_class_data_; }

void Message::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Message *>(to)->MergeFrom(
      static_cast<const Message &>(from));
}


void Message::MergeFrom(const Message& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:com.chuzi.imsdk.server.model.proto.Message)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_id().empty()) {
    _internal_set_id(from._internal_id());
  }
  if (!from._internal_content().empty()) {
    _internal_set_content(from._internal_content());
  }
  if (!from._internal_sender().empty()) {
    _internal_set_sender(from._internal_sender());
  }
  if (!from._internal_receiver().empty()) {
    _internal_set_receiver(from._internal_receiver());
  }
  if (!from._internal_extra().empty()) {
    _internal_set_extra(from._internal_extra());
  }
  if (!from._internal_title().empty()) {
    _internal_set_title(from._internal_title());
  }
  if (from._internal_scene() != 0) {
    _internal_set_scene(from._internal_scene());
  }
  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  if (from._internal_timestamp() != 0) {
    _internal_set_timestamp(from._internal_timestamp());
  }
  if (from._internal_subtype() != 0) {
    _internal_set_subtype(from._internal_subtype());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Message::CopyFrom(const Message& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:com.chuzi.imsdk.server.model.proto.Message)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Message::IsInitialized() const {
  return true;
}

void Message::InternalSwap(Message* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &id_, lhs_arena,
      &other->id_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &content_, lhs_arena,
      &other->content_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &sender_, lhs_arena,
      &other->sender_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &receiver_, lhs_arena,
      &other->receiver_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &extra_, lhs_arena,
      &other->extra_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &title_, lhs_arena,
      &other->title_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Message, subtype_)
      + sizeof(Message::subtype_)
      - PROTOBUF_FIELD_OFFSET(Message, scene_)>(
          reinterpret_cast<char*>(&scene_),
          reinterpret_cast<char*>(&other->scene_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Message::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Message_2eproto_getter, &descriptor_table_Message_2eproto_once,
      file_level_metadata_Message_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace model
}  // namespace server
}  // namespace imsdk
}  // namespace chuzi
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::com::chuzi::imsdk::server::model::proto::Message*
Arena::CreateMaybeMessage< ::com::chuzi::imsdk::server::model::proto::Message >(Arena* arena) {
  return Arena::CreateMessageInternal< ::com::chuzi::imsdk::server::model::proto::Message >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
