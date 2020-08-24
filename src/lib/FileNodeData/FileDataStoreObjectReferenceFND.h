#ifndef FILEDATASTOREOBJECTREFERENCEFND_H
#define FILEDATASTOREOBJECTREFERENCEFND_H

#include "../FileNodeChunkReference.h"
#include "../GUID.h"
#include "IFileNodeData.h"

namespace libone
{

class FileDataStoreObjectReferenceFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;
  GUID m_guidReference {};

public:
  FileDataStoreObjectReferenceFND(StpFormat stpFormat,
                                  CbFormat cbFormat);
  ~FileDataStoreObjectReferenceFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  libone::GUID getGuidReference() const;
  void setGuidReference(const GUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // FILEDATASTOREOBJECTREFERENCEFND_H
