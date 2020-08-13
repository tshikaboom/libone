#include "FileDataStoreListReferenceFND.h"

namespace libone
{

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat) {}

FileDataStoreListReferenceFND::~FileDataStoreListReferenceFND() {}

FileNodeChunkReference FileDataStoreListReferenceFND::getRef() const
{
  return m_ref;
}

void FileDataStoreListReferenceFND::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void FileDataStoreListReferenceFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
}

} // namespace libone
