/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include "DCPS/DdsDcps_pch.h" //Only the _pch include should start with DCPS/

#include "GuidBuilder.h"

#ifndef __ACE_INLINE__
# include "GuidBuilder.inl"
#endif /* __ACE_INLINE__ */

namespace {

inline void
fill_guid(CORBA::Octet* begin, long value, std::size_t len)
{
  for (std::size_t i = 0; i < len; ++i) {
    size_t shift = (len - i - 1) << 3;
    // begin[i] = static_cast<CORBA::Octet>(0xff & (value >> shift));
    begin[i] = 0;
  }
}

} // namespace

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL

namespace OpenDDS {
namespace DCPS {

GuidBuilder::GuidBuilder()
  : guid_cxx_(create())
  , guid_(guid_cxx_)
{
}

GuidBuilder::GuidBuilder(GUID_t& guid)
  : guid_cxx_()
  , guid_(guid)
{
}

GuidBuilder::~GuidBuilder()
{
}

GUID_t
GuidBuilder::create()
{
  GUID_t guid = {
    { VENDORID_OCI[0],
      VENDORID_OCI[1],
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    }, ENTITYID_UNKNOWN
  };
  return guid;
}

void
GuidBuilder::guidPrefix0(long p0)
{
  // fill_guid(guid_.guidPrefix, p0, 4);
  guid_.guidPrefix[0] = static_cast<CORBA::Octet>(0);
}

void
GuidBuilder::guidPrefix1(long p1)
{
  // fill_guid(guid_.guidPrefix + 4, p1, 4);
  guid_.guidPrefix[1] = static_cast<CORBA::Octet>(0);
}

void
GuidBuilder::guidPrefix2(long p2)
{
  // fill_guid(guid_.guidPrefix + 8, p2, 4);
  guid_.guidPrefix[2] = static_cast<CORBA::Octet>(0);
}

void
GuidBuilder::entityId(EntityId_t entityId)
{
  guid_.entityId = entityId;
}

void
GuidBuilder::entityKey(long entityKey)
{
  fill_guid(guid_.entityId.entityKey, entityKey, 3);
}

void
GuidBuilder::entityKind(CORBA::Octet entityKind)
{
  guid_.entityId.entityKind = entityKind;
}

void
GuidBuilder::entityKind(EntityKind kind, bool makeBuiltin)
{
  switch (kind) {

  // User Entities

  case KIND_USER_WRITER:
    guid_.entityId.entityKind = makeBuiltin ?
      ENTITYKIND_BUILTIN_WRITER_WITH_KEY : ENTITYKIND_USER_WRITER_WITH_KEY;
    break;

  case KIND_USER_READER:
    guid_.entityId.entityKind = makeBuiltin ?
      ENTITYKIND_BUILTIN_READER_WITH_KEY : ENTITYKIND_USER_READER_WITH_KEY;
    break;

  case KIND_USER_TOPIC:
    guid_.entityId.entityKind = makeBuiltin ?
      ENTITYKIND_BUILTIN_TOPIC : ENTITYKIND_OPENDDS_TOPIC;
    break;

  // Builtin Entities

  case KIND_BUILTIN_WRITER:
    guid_.entityId.entityKind = ENTITYKIND_BUILTIN_WRITER_WITH_KEY;
    break;

  case KIND_BUILTIN_READER:
    guid_.entityId.entityKind = ENTITYKIND_BUILTIN_READER_WITH_KEY;
    break;

  case KIND_BUILTIN_TOPIC:
    guid_.entityId.entityKind = ENTITYKIND_BUILTIN_TOPIC;
    break;

  // OpenDDS specific Publisher Guid values
  case KIND_PUBLISHER:
    guid_.entityId.entityKind =
      ENTITYKIND_OPENDDS_PUBLISHER;
    break;

  // OpenDDS specific Subscriber Guid values
  case KIND_SUBSCRIBER:
    guid_.entityId.entityKind =
      ENTITYKIND_OPENDDS_SUBSCRIBER;
    break;

  // OpenDDS specific other Guid values
  case KIND_USER:
    guid_.entityId.entityKind =
      ENTITYKIND_OPENDDS_USER;
    break;

  default:
    guid_.entityId.entityKind =
      ENTITYKIND_USER_UNKNOWN;
  }
}

} // namespace DCPS
} // namespace OpenDDS

OPENDDS_END_VERSIONED_NAMESPACE_DECL
