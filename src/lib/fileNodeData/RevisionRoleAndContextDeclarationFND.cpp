#include "RevisionRoleAndContextDeclarationFND.h"

namespace libone
{

RevisionRoleAndContextDeclarationFND::RevisionRoleAndContextDeclarationFND() :m_base(), m_gctxid() {}

ExtendedGUID RevisionRoleAndContextDeclarationFND::getGctxid() const
{
  return m_gctxid;
}

void RevisionRoleAndContextDeclarationFND::setGctxid(
  const ExtendedGUID &value)
{
  m_gctxid = value;
}

RevisionRoleDeclarationFND
RevisionRoleAndContextDeclarationFND::getBase() const
{
  return m_base;
}

void RevisionRoleAndContextDeclarationFND::setBase(
  const RevisionRoleDeclarationFND &value)
{
  m_base = value;
}

void RevisionRoleAndContextDeclarationFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_base;
  input >> m_gctxid;
}

std::string RevisionRoleAndContextDeclarationFND::to_string() const
{
  return "";
}

} // namespace libone
