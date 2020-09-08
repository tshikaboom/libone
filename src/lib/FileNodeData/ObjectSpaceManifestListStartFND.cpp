#include "ObjectSpaceManifestListStartFND.h"

namespace libone
{
ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND() : m_gosid() {}

ExtendedGUID ObjectSpaceManifestListStartFND::getGosid() const
{
  return m_gosid;
}

void ObjectSpaceManifestListStartFND::setGosid(const ExtendedGUID &value)
{
  m_gosid = value;
}

void ObjectSpaceManifestListStartFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_gosid;
}

std::string ObjectSpaceManifestListStartFND::to_string() const
{
  return "";
}

} // namespace libone
