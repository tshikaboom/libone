#include "ObjectDeclarationWithRefCountBody.h"

namespace libone
{

ObjectDeclarationWithRefCountBody::ObjectDeclarationWithRefCountBody()
  : m_oid(), m_jci(), m_odcs(), m_fReserved1(),
    m_fHasOidReferences(false), m_fHasOsidReferences(false), m_fReserved2() {}

bool ObjectDeclarationWithRefCountBody::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectDeclarationWithRefCountBody::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

uint8_t ObjectDeclarationWithRefCountBody::getOdc() const
{
  return m_odcs;
}

void ObjectDeclarationWithRefCountBody::setOdc(const uint8_t &value)
{
  m_odcs = value;
}

uint8_t ObjectDeclarationWithRefCountBody::getJci() const
{
  return m_jci;
}

void ObjectDeclarationWithRefCountBody::setJci(const uint8_t &value)
{
  m_jci = value;
}

CompactID ObjectDeclarationWithRefCountBody::getOid() const
{
  return m_oid;
}

void ObjectDeclarationWithRefCountBody::setOid(const CompactID &value)
{
  m_oid = value;
}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                               ObjectDeclarationWithRefCountBody &obj)
{
  obj.parse(input);
  return input;
}

void ObjectDeclarationWithRefCountBody::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  uint64_t temp;

  input >> temp;
  m_jci = temp & 0x3FF;
  m_odcs = (temp >> 10) & 0xF;
  m_fReserved1 = (temp >> 14) & 0x3;
  m_fHasOidReferences = (temp >> 16) & 0x1;
  m_fHasOsidReferences = (temp >> 17) & 0x1;
}

} // namespace libone
