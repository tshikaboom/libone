#ifndef HASHEDCHUNKDESCRIPTOR2FND_H
#define HASHEDCHUNKDESCRIPTOR2FND_H

#include <array>

#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class HashedChunkDescriptor2FND : public IFileNodeData
{
private:
  FileNodeChunkReference m_BlobRef;

  std::array<unsigned char,16> m_guidHash {};
  uint8_t m_guidHash_length = 16;

public:
  HashedChunkDescriptor2FND(StpFormat stpFormat, CbFormat cbFormat);
  HashedChunkDescriptor2FND(const HashedChunkDescriptor2FND &source);

  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference &BlobRef);

  std::array<unsigned char, 16>  guidHash() const;
  void setGuidHash(const std::array<unsigned char, 16> guidHash);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};
} // namespace libone

#endif // HASHEDCHUNKDESCRIPTOR2FND_H
