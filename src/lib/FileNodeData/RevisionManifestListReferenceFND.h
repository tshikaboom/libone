#ifndef REVISIONMANIFESTLISTREFERENCEFND_H
#define REVISIONMANIFESTLISTREFERENCEFND_H

#include "IFileNodeData.h"
#include "../FileNodeChunkReference.h"

namespace libone
{

class RevisionManifestListReferenceFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

public:
  RevisionManifestListReferenceFND(StpFormat stpFormat,
                                   CbFormat cbFormat);

  ~RevisionManifestListReferenceFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // REVISIONMANIFESTLISTREFERENCEFND_H
