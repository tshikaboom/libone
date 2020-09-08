#include "ObjectRevisionWithRefCountFNDX.h"


namespace libone
{
ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat), m_oid(),
    m_fHasOidReferences(false), m_fHasOsidReferences(false), m_cRef(0) {}

bool ObjectRevisionWithRefCountFNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCountFNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

uint8_t ObjectRevisionWithRefCountFNDX::getCRef() const
{
  return m_cRef;
}

void ObjectRevisionWithRefCountFNDX::setCRef(const uint8_t &value)
{
  m_cRef = value;
}

CompactID ObjectRevisionWithRefCountFNDX::getOid() const
{
  return m_oid;
}

void ObjectRevisionWithRefCountFNDX::setOid(const CompactID &value)
{
  m_oid = value;
}

FileNodeChunkReference ObjectRevisionWithRefCountFNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCountFNDX::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void ObjectRevisionWithRefCountFNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
  input >> m_oid;
  input >> m_cRef;

  m_fHasOidReferences = m_cRef & 0x1;
  m_fHasOsidReferences = m_cRef & 0x2;

  m_cRef = m_cRef >> 2;
}

std::string ObjectRevisionWithRefCountFNDX::to_string() const
{
  return "";
}

} // namespace libone
