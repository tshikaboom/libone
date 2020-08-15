#include "ObjectInfoDependencyOverride32.h"

namespace libone
{

ObjectInfoDependencyOverride32::ObjectInfoDependencyOverride32() : m_oid(), m_cRef() {}


CompactID ObjectInfoDependencyOverride32::oid() const
{
  return m_oid;
}

void ObjectInfoDependencyOverride32::setOid(const CompactID &oid)
{
  m_oid = oid;
}

uint32_t ObjectInfoDependencyOverride32::cRef() const
{
  return m_cRef;
}

void ObjectInfoDependencyOverride32::setCRef(const uint32_t &cRef)
{
  m_cRef = cRef;
}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ObjectInfoDependencyOverride32 &obj)
{
  obj.parse(input);
  return input;
}

void ObjectInfoDependencyOverride32::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  input >> m_cRef;
}

std::string ObjectInfoDependencyOverride32::to_string() const
{
  return "";
}

} // namespace libone
