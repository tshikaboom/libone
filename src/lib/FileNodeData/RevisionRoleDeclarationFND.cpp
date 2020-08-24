#include "RevisionRoleDeclarationFND.h"

namespace libone
{
RevisionRoleDeclarationFND::RevisionRoleDeclarationFND(): m_rid(), m_RevisionRole() {}

uint32_t RevisionRoleDeclarationFND::getRevisionRole() const
{
  return m_RevisionRole;
}

void RevisionRoleDeclarationFND::setRevisionRole(const uint32_t &value)
{
  m_RevisionRole = value;
}

ExtendedGUID RevisionRoleDeclarationFND::getRid() const
{
  return m_rid;
}

void RevisionRoleDeclarationFND::setRid(const ExtendedGUID &value)
{
  m_rid = value;
}

void RevisionRoleDeclarationFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_rid;
  input >> m_RevisionRole;
}

std::string RevisionRoleDeclarationFND::to_string() const
{
  return "";
}

} // namespace libone
