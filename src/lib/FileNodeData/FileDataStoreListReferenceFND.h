#ifndef FILEDATASTORELISTREFERENCEFND_H
#define FILEDATASTORELISTREFERENCEFND_H

#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"
namespace libone
{

class FileDataStoreListReferenceFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

public:
  FileDataStoreListReferenceFND(StpFormat stpFormat, CbFormat cbFormat);
  ~FileDataStoreListReferenceFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

  IFileNodeData *clone() const override
  {
    return new FileDataStoreListReferenceFND(*this);
  }
};

} // namespace libone

#endif // FILEDATASTORELISTREFERENCEFND_H
