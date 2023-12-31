// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SentBody.proto

#include "SentBody.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace com {
namespace chuzi {
namespace imsdk {
namespace server {
namespace model {
namespace proto {
      template <typename>
PROTOBUF_CONSTEXPR SentBody_DataEntry_DoNotUse::SentBody_DataEntry_DoNotUse(::_pbi::ConstantInitialized) {}
struct SentBody_DataEntry_DoNotUseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SentBody_DataEntry_DoNotUseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~SentBody_DataEntry_DoNotUseDefaultTypeInternal() {}
  union {
    SentBody_DataEntry_DoNotUse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SentBody_DataEntry_DoNotUseDefaultTypeInternal _SentBody_DataEntry_DoNotUse_default_instance_;
        template <typename>
PROTOBUF_CONSTEXPR SentBody::SentBody(::_pbi::ConstantInitialized)
    : _impl_{
      /* decltype(_impl_.data_) */ {},
      /*decltype(_impl_.key_)*/ {
          &::_pbi::fixed_address_empty_string,
          ::_pbi::ConstantInitialized{},
      },
      /*decltype(_impl_.timestamp_)*/ ::int64_t{0},
      /*decltype(_impl_._cached_size_)*/ {},
    } {}
struct SentBodyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SentBodyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~SentBodyDefaultTypeInternal() {}
  union {
    SentBody _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SentBodyDefaultTypeInternal _SentBody_default_instance_;
}  // namespace proto
}  // namespace model
}  // namespace server
}  // namespace imsdk
}  // namespace chuzi
}  // namespace com
static ::_pb::Metadata file_level_metadata_SentBody_2eproto[2];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_SentBody_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_SentBody_2eproto = nullptr;
const ::uint32_t TableStruct_SentBody_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody_DataEntry_DoNotUse, _has_bits_),
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody_DataEntry_DoNotUse, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody_DataEntry_DoNotUse, key_),
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody_DataEntry_DoNotUse, value_),
    0,
    1,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody, _impl_.key_),
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody, _impl_.timestamp_),
    PROTOBUF_FIELD_OFFSET(::com::chuzi::imsdk::server::model::proto::SentBody, _impl_.data_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, 10, -1, sizeof(::com::chuzi::imsdk::server::model::proto::SentBody_DataEntry_DoNotUse)},
        {12, -1, -1, sizeof(::com::chuzi::imsdk::server::model::proto::SentBody)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::com::chuzi::imsdk::server::model::proto::_SentBody_DataEntry_DoNotUse_default_instance_._instance,
    &::com::chuzi::imsdk::server::model::proto::_SentBody_default_instance_._instance,
};
const char descriptor_table_protodef_SentBody_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\016SentBody.proto\022\"com.chuzi.imsdk.server"
    ".model.proto\"\235\001\n\010SentBody\022\013\n\003key\030\001 \001(\t\022\021"
    "\n\ttimestamp\030\002 \001(\003\022D\n\004data\030\003 \003(\01326.com.ch"
    "uzi.imsdk.server.model.proto.SentBody.Da"
    "taEntry\032+\n\tDataEntry\022\013\n\003key\030\001 \001(\t\022\r\n\005val"
    "ue\030\002 \001(\t:\0028\001B\017B\rSentBodyProtob\006proto3"
};
static ::absl::once_flag descriptor_table_SentBody_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_SentBody_2eproto = {
    false,
    false,
    237,
    descriptor_table_protodef_SentBody_2eproto,
    "SentBody.proto",
    &descriptor_table_SentBody_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_SentBody_2eproto::offsets,
    file_level_metadata_SentBody_2eproto,
    file_level_enum_descriptors_SentBody_2eproto,
    file_level_service_descriptors_SentBody_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_SentBody_2eproto_getter() {
  return &descriptor_table_SentBody_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_SentBody_2eproto(&descriptor_table_SentBody_2eproto);
namespace com {
namespace chuzi {
namespace imsdk {
namespace server {
namespace model {
namespace proto {
// ===================================================================

SentBody_DataEntry_DoNotUse::SentBody_DataEntry_DoNotUse() {}
SentBody_DataEntry_DoNotUse::SentBody_DataEntry_DoNotUse(::google::protobuf::Arena* arena)
    : SuperType(arena) {}
void SentBody_DataEntry_DoNotUse::MergeFrom(const SentBody_DataEntry_DoNotUse& other) {
  MergeFromInternal(other);
}
::google::protobuf::Metadata SentBody_DataEntry_DoNotUse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SentBody_2eproto_getter, &descriptor_table_SentBody_2eproto_once,
      file_level_metadata_SentBody_2eproto[0]);
}
// ===================================================================

class SentBody::_Internal {
 public:
};

SentBody::SentBody(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:com.chuzi.imsdk.server.model.proto.SentBody)
}
SentBody::SentBody(const SentBody& from) : ::google::protobuf::Message() {
  SentBody* const _this = this;
  (void)_this;
  new (&_impl_) Impl_{
      /* decltype(_impl_.data_) */ {},
      decltype(_impl_.key_){},
      decltype(_impl_.timestamp_){},
      /*decltype(_impl_._cached_size_)*/ {},
  };
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  _this->_impl_.data_.MergeFrom(from._impl_.data_);
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.key_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_key().empty()) {
    _this->_impl_.key_.Set(from._internal_key(), _this->GetArenaForAllocation());
  }
  _this->_impl_.timestamp_ = from._impl_.timestamp_;

  // @@protoc_insertion_point(copy_constructor:com.chuzi.imsdk.server.model.proto.SentBody)
}
inline void SentBody::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      /* decltype(_impl_.data_) */ {::google::protobuf::internal::ArenaInitialized(), arena},
      decltype(_impl_.key_){},
      decltype(_impl_.timestamp_){::int64_t{0}},
      /*decltype(_impl_._cached_size_)*/ {},
  };
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.key_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}
SentBody::~SentBody() {
  // @@protoc_insertion_point(destructor:com.chuzi.imsdk.server.model.proto.SentBody)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void SentBody::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.data_.~MapField();
  _impl_.key_.Destroy();
}
void SentBody::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

PROTOBUF_NOINLINE void SentBody::Clear() {
// @@protoc_insertion_point(message_clear_start:com.chuzi.imsdk.server.model.proto.SentBody)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.data_.Clear();
  _impl_.key_.ClearToEmpty();
  _impl_.timestamp_ = ::int64_t{0};
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* SentBody::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 3, 1, 59, 2> SentBody::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    3, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967288,  // skipmap
    offsetof(decltype(_table_), field_entries),
    3,  // num_field_entries
    1,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_SentBody_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // int64 timestamp = 2;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(SentBody, _impl_.timestamp_), 63>(),
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(SentBody, _impl_.timestamp_)}},
    // string key = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(SentBody, _impl_.key_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string key = 1;
    {PROTOBUF_FIELD_OFFSET(SentBody, _impl_.key_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // int64 timestamp = 2;
    {PROTOBUF_FIELD_OFFSET(SentBody, _impl_.timestamp_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt64)},
    // map<string, string> data = 3;
    {PROTOBUF_FIELD_OFFSET(SentBody, _impl_.data_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kMap)},
  }}, {{
    {::_pbi::TcParser::GetMapAuxInfo<decltype(SentBody()._impl_.data_)>(1, 0, 0)},
  }}, {{
    "\53\3\0\4\0\0\0\0"
    "com.chuzi.imsdk.server.model.proto.SentBody"
    "key"
    "data"
  }},
};

::uint8_t* SentBody::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.chuzi.imsdk.server.model.proto.SentBody)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string key = 1;
  if (!this->_internal_key().empty()) {
    const std::string& _s = this->_internal_key();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "com.chuzi.imsdk.server.model.proto.SentBody.key");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // int64 timestamp = 2;
  if (this->_internal_timestamp() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt64ToArrayWithField<2>(
            stream, this->_internal_timestamp(), target);
  }

  // map<string, string> data = 3;
  if (!_internal_data().empty()) {
    using MapType = ::google::protobuf::Map<std::string, std::string>;
    using WireHelper = SentBody_DataEntry_DoNotUse::Funcs;
    const auto& field = _internal_data();

    if (stream->IsSerializationDeterministic() && field.size() > 1) {
      for (const auto& entry : ::google::protobuf::internal::MapSorterPtr<MapType>(field)) {
        target = WireHelper::InternalSerialize(
            3, entry.first, entry.second, target, stream);
        ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            entry.first.data(), static_cast<int>(entry.first.length()),
 ::google::protobuf::internal::WireFormatLite::SERIALIZE, "com.chuzi.imsdk.server.model.proto.SentBody.data");
        ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            entry.second.data(), static_cast<int>(entry.second.length()),
 ::google::protobuf::internal::WireFormatLite::SERIALIZE, "com.chuzi.imsdk.server.model.proto.SentBody.data");
      }
    } else {
      for (const auto& entry : field) {
        target = WireHelper::InternalSerialize(
            3, entry.first, entry.second, target, stream);
        ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            entry.first.data(), static_cast<int>(entry.first.length()),
 ::google::protobuf::internal::WireFormatLite::SERIALIZE, "com.chuzi.imsdk.server.model.proto.SentBody.data");
        ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            entry.second.data(), static_cast<int>(entry.second.length()),
 ::google::protobuf::internal::WireFormatLite::SERIALIZE, "com.chuzi.imsdk.server.model.proto.SentBody.data");
      }
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.chuzi.imsdk.server.model.proto.SentBody)
  return target;
}

::size_t SentBody::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:com.chuzi.imsdk.server.model.proto.SentBody)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // map<string, string> data = 3;
  total_size += 1 * ::google::protobuf::internal::FromIntSize(_internal_data_size());
  for (const auto& entry : _internal_data()) {
    total_size += SentBody_DataEntry_DoNotUse::Funcs::ByteSizeLong(entry.first, entry.second);
  }
  // string key = 1;
  if (!this->_internal_key().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_key());
  }

  // int64 timestamp = 2;
  if (this->_internal_timestamp() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_timestamp());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData SentBody::_class_data_ = {
    ::google::protobuf::Message::CopyWithSourceCheck,
    SentBody::MergeImpl
};
const ::google::protobuf::Message::ClassData*SentBody::GetClassData() const { return &_class_data_; }


void SentBody::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<SentBody*>(&to_msg);
  auto& from = static_cast<const SentBody&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:com.chuzi.imsdk.server.model.proto.SentBody)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.data_.MergeFrom(from._impl_.data_);
  if (!from._internal_key().empty()) {
    _this->_internal_set_key(from._internal_key());
  }
  if (from._internal_timestamp() != 0) {
    _this->_internal_set_timestamp(from._internal_timestamp());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void SentBody::CopyFrom(const SentBody& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:com.chuzi.imsdk.server.model.proto.SentBody)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool SentBody::IsInitialized() const {
  return true;
}

void SentBody::InternalSwap(SentBody* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.data_.InternalSwap(&other->_impl_.data_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.key_, lhs_arena,
                                       &other->_impl_.key_, rhs_arena);
        swap(_impl_.timestamp_, other->_impl_.timestamp_);
}

::google::protobuf::Metadata SentBody::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_SentBody_2eproto_getter, &descriptor_table_SentBody_2eproto_once,
      file_level_metadata_SentBody_2eproto[1]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace model
}  // namespace server
}  // namespace imsdk
}  // namespace chuzi
}  // namespace com
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
