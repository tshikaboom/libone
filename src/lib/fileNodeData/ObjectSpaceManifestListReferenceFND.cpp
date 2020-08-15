#include "ObjectSpaceManifestListReferenceFND.h"

namespace libone
{
ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref{FileNodeChunkReference(stpFormat, cbFormat)}, m_gosid() {}

ObjectSpaceManifestListReferenceFND::~ObjectSpaceManifestListReferenceFND() {}

ExtendedGUID ObjectSpaceManifestListReferenceFND::getGosid() const
{
  return m_gosid;
}

void ObjectSpaceManifestListReferenceFND::setGosid(const ExtendedGUID &value)
{
  m_gosid = value;
}

FileNodeChunkReference ObjectSpaceManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void ObjectSpaceManifestListReferenceFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
  input >> m_gosid;
}

std::string ObjectSpaceManifestListReferenceFND::to_string() const
{
  return "";
}

} // namespace libone
