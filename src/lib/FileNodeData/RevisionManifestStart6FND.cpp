#include "RevisionManifestStart6FND.h"

namespace libone
{

RevisionManifestStart6FND::RevisionManifestStart6FND() : m_rid(), m_ridDependent(), m_revisionRole(), m_odcsDefault() {}

ExtendedGUID RevisionManifestStart6FND::getRid() const
{
  return m_rid;
}

void RevisionManifestStart6FND::setRid(const ExtendedGUID &value)
{
  m_rid = value;
}

ExtendedGUID RevisionManifestStart6FND::getRidDependent() const
{
  return m_ridDependent;
}

void RevisionManifestStart6FND::setRidDependent(const ExtendedGUID &value)
{
  m_ridDependent = value;
}

int32_t RevisionManifestStart6FND::getRevisionRole() const
{
  return m_revisionRole;
}

void RevisionManifestStart6FND::setRevisionRole(const int32_t &value)
{
  m_revisionRole = value;
}

uint16_t RevisionManifestStart6FND::getOdcsDefault() const
{
  return m_odcsDefault;
}

void RevisionManifestStart6FND::setOdcsDefault(const uint16_t &value)
{
  m_odcsDefault = value;
}

void RevisionManifestStart6FND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_rid;
  input >> m_ridDependent;
  input >> m_revisionRole;
  input >> m_odcsDefault;
}

std::string RevisionManifestStart6FND::to_string() const
{
  return "";
}

} // namespace libone
