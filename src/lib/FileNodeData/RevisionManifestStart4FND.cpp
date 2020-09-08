#include "RevisionManifestStart4FND.h"

namespace libone
{

RevisionManifestStart4FND::RevisionManifestStart4FND() : m_rid(), m_ridDependent(),
  m_timeCreation(), m_revisionRole(), m_odcsDefault() {}

ExtendedGUID RevisionManifestStart4FND::getRid() const
{
  return m_rid;
}

void RevisionManifestStart4FND::setRid(const ExtendedGUID &value)
{
  m_rid = value;
}

ExtendedGUID RevisionManifestStart4FND::getRidDependent() const
{
  return m_ridDependent;
}

void RevisionManifestStart4FND::setRidDependent(const ExtendedGUID &value)
{
  m_ridDependent = value;
}

uint64_t RevisionManifestStart4FND::getTimeCreation() const
{
  return m_timeCreation;
}

void RevisionManifestStart4FND::setTimeCreation(const uint64_t &value)
{
  m_timeCreation = value;
}

int32_t RevisionManifestStart4FND::getRevisionRole() const
{
  return m_revisionRole;
}

void RevisionManifestStart4FND::setRevisionRole(const int32_t &value)
{
  m_revisionRole = value;
}

uint16_t RevisionManifestStart4FND::getOdcsDefault() const
{
  return m_odcsDefault;
}

void RevisionManifestStart4FND::setOdcsDefault(const uint16_t &value)
{
  m_odcsDefault = value;
}

void RevisionManifestStart4FND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_rid;
  input >> m_ridDependent;
  input >> m_timeCreation;
  input >> m_revisionRole;
  input >> m_odcsDefault;
}

std::string RevisionManifestStart4FND::to_string() const
{
  return "";
}

} // namespace libone
