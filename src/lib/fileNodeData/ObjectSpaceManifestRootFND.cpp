#include "ObjectSpaceManifestRootFND.h"

namespace libone
{

ObjectSpaceManifestRootFND::ObjectSpaceManifestRootFND() : m_gosidRoot() {}

ObjectSpaceManifestRootFND::~ObjectSpaceManifestRootFND() {}

ExtendedGUID ObjectSpaceManifestRootFND::getGosidRoot() const
{
  return m_gosidRoot;
}

void ObjectSpaceManifestRootFND::setGosidRoot(const ExtendedGUID &value)
{
  m_gosidRoot = value;
}

void ObjectSpaceManifestRootFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_gosidRoot;
}

std::string ObjectSpaceManifestRootFND::to_string() const
{
  return "";
}

} // namespace libone
