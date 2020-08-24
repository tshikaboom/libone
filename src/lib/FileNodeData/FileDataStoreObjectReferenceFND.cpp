#include "FileDataStoreObjectReferenceFND.h"

namespace libone
{

FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat) {}

FileDataStoreObjectReferenceFND::~FileDataStoreObjectReferenceFND() {}

FileNodeChunkReference FileDataStoreObjectReferenceFND::getRef() const
{
  return m_ref;
}

void FileDataStoreObjectReferenceFND::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

libone::GUID FileDataStoreObjectReferenceFND::getGuidReference() const
{
  return m_guidReference;
}

void FileDataStoreObjectReferenceFND::setGuidReference(const GUID &value)
{
  m_guidReference = value;
}

void FileDataStoreObjectReferenceFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
  input >> m_guidReference;
}

std::string FileDataStoreObjectReferenceFND::to_string() const
{
  return "";
}

} // namespace libone
