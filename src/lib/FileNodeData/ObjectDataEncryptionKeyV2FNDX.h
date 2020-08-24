#ifndef OBJECTDATAENCRYPTIONKEYV2FNDX_H
#define OBJECTDATAENCRYPTIONKEYV2FNDX_H

#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectDataEncryptionKeyV2FNDX : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

  static constexpr const uint64_t m_header = 0xFB6BA385DAD1A067;
  static constexpr const uint64_t m_footer = 0x2649294F8E198B3C;

  std::unique_ptr<unsigned char[]> m_EncryptionData;
public:
  ObjectDataEncryptionKeyV2FNDX(const StpFormat stpFormat, const CbFormat cbFormat);
  ~ObjectDataEncryptionKeyV2FNDX();

//   ObjectDataEncryptionKeyV2FNDX &operator=(const ObjectDataEncryptionKeyV2FNDX &rhs);

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  unsigned char *getEncryptionData() const;
  uint64_t getEncryptionDataLength() const;
  void setEncryptionData(const unsigned char *value, const uint64_t length);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTDATAENCRYPTIONKEYV2FNDX_H
