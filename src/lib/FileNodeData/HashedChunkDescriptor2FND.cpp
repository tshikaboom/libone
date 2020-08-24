#include "HashedChunkDescriptor2FND.h"

#include <algorithm>

namespace libone
{
HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(StpFormat stpFormat,
                                                     CbFormat cbFormat)
  : m_BlobRef(stpFormat, cbFormat) {}

HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(const HashedChunkDescriptor2FND &source)
  : m_BlobRef(source.BlobRef()), m_guidHash(source.m_guidHash)
{
}

FileNodeChunkReference HashedChunkDescriptor2FND::BlobRef() const
{
  return m_BlobRef;
}

void HashedChunkDescriptor2FND::setBlobRef(
  const FileNodeChunkReference &BlobRef)
{
  m_BlobRef = BlobRef;
}

std::array<unsigned char,16> HashedChunkDescriptor2FND::guidHash() const
{
  return m_guidHash;
}

void HashedChunkDescriptor2FND::setGuidHash(std::array<unsigned char, 16> guidHash)
{
  m_guidHash = guidHash;
}



void HashedChunkDescriptor2FND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_BlobRef;
  const unsigned char *temp= readNBytes(input, m_guidHash_length);

  std::copy_n(temp, m_guidHash_length, std::begin(m_guidHash));
}

std::string HashedChunkDescriptor2FND::to_string() const
{
  return "";
}

} // namespace libone
