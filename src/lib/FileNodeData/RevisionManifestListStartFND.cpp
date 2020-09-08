#include "RevisionManifestListStartFND.h"

namespace libone
{
RevisionManifestListStartFND::RevisionManifestListStartFND() : m_gosid(), m_nInstance()  {}
RevisionManifestListStartFND::~RevisionManifestListStartFND() {}

ExtendedGUID RevisionManifestListStartFND::getGosid() const
{
  return m_gosid;
}

void RevisionManifestListStartFND::setGosid(const ExtendedGUID &value)
{
  m_gosid = value;
}

uint32_t RevisionManifestListStartFND::getNInstance() const
{
  return m_nInstance;
}

void RevisionManifestListStartFND::setNInstance(const uint32_t &value)
{
  m_nInstance = value;
}

void RevisionManifestListStartFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_gosid;
  input >> m_nInstance;
}

std::string RevisionManifestListStartFND::to_string() const
{
  return "";
}

} // namespace libone
