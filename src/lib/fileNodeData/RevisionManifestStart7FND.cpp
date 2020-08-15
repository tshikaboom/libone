#include "RevisionManifestStart7FND.h"

namespace libone
{
RevisionManifestStart7FND::RevisionManifestStart7FND() : m_base(), m_gctxid() {}

ExtendedGUID RevisionManifestStart7FND::getGctxid() const
{
  return m_gctxid;
}

void RevisionManifestStart7FND::setGctxid(const ExtendedGUID &value)
{
  m_gctxid = value;
}

RevisionManifestStart6FND RevisionManifestStart7FND::getBase() const
{
  return m_base;
}

void RevisionManifestStart7FND::setBase(
  const RevisionManifestStart6FND &value)
{
  m_base = value;
}

void RevisionManifestStart7FND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_base;
  input >> m_gctxid;
}

std::string RevisionManifestStart7FND::to_string() const
{
  return "";
}

} // namespace libone
