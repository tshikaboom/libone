#include "ObjectDeclaration2Body.h"

namespace libone
{

ObjectDeclaration2Body::ObjectDeclaration2Body() :m_oid(), m_jcid(), m_fHasOidReferences(false), m_fHasOsidReferences(false) {}

bool ObjectDeclaration2Body::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectDeclaration2Body::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectDeclaration2Body::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectDeclaration2Body::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

JCID ObjectDeclaration2Body::getJcid() const
{
  return m_jcid;
}

void ObjectDeclaration2Body::setJcid(const JCID &value)
{
  m_jcid = value;
}

CompactID ObjectDeclaration2Body::getOid() const
{
  return m_oid;
}

void ObjectDeclaration2Body::setOid(const CompactID &value)
{
  m_oid = value;
}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ObjectDeclaration2Body &obj)
{
  obj.parse(input);
  return input;
}

void ObjectDeclaration2Body::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  input >> m_jcid;

  uint8_t temp;
  input >> temp;
  m_fHasOidReferences = temp & 0x1;
  m_fHasOsidReferences = (temp >> 1) & 0x1;
}

std::string ObjectDeclaration2Body::to_string() const
{
  return "";
}

} // namespace libone
