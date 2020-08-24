#include "ObjectInfoDependencyOverride8.h"

namespace libone
{

ObjectInfoDependencyOverride8::ObjectInfoDependencyOverride8() : m_oid(), m_cRef() {}


CompactID ObjectInfoDependencyOverride8::oid() const
{
  return m_oid;
}

void ObjectInfoDependencyOverride8::setOid(const CompactID &oid)
{
  m_oid = oid;
}

uint8_t ObjectInfoDependencyOverride8::cRef() const
{
  return m_cRef;
}

void ObjectInfoDependencyOverride8::setCRef(const uint8_t &cRef)
{
  m_cRef = cRef;
}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ObjectInfoDependencyOverride8 &obj)
{
  obj.parse(input);
  return input;
}

void ObjectInfoDependencyOverride8::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  input >> m_cRef;
}

std::string ObjectInfoDependencyOverride8::to_string() const
{
  return "";
}

} // namespace libone
