#include "ObjectRevisionWithRefCount2FNDX.h"

namespace libone
{

ObjectRevisionWithRefCount2FNDX::ObjectRevisionWithRefCount2FNDX(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat), m_oid(),
    m_fHasOidReferences(false), m_fHasOsidReferences(false), m_cRef(0) {}

uint32_t ObjectRevisionWithRefCount2FNDX::getCRef() const
{
  return m_cRef;
}

void ObjectRevisionWithRefCount2FNDX::setCRef(const uint32_t &value)
{
  m_cRef = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

CompactID ObjectRevisionWithRefCount2FNDX::getOid() const
{
  return m_oid;
}

void ObjectRevisionWithRefCount2FNDX::setOid(const CompactID &value)
{
  m_oid = value;
}

FileNodeChunkReference ObjectRevisionWithRefCount2FNDX::getRef() const
{
  return m_ref;
}

void ObjectRevisionWithRefCount2FNDX::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void ObjectRevisionWithRefCount2FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
  input >> m_oid;

  uint32_t temp;
  input >> temp;

  m_fHasOidReferences = temp & 0x1;
  m_fHasOsidReferences = (temp & 0x2) >> 1;

  input >> m_cRef;
}

std::string ObjectRevisionWithRefCount2FNDX::to_string() const
{
  return "";
}

} // namespace libone
