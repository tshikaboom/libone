#ifndef OBJECTSPACEMANIFESTLISTREFERENCEFND_H
#define OBJECTSPACEMANIFESTLISTREFERENCEFND_H

#include "../ExtendedGUID.h"
#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectSpaceManifestListReferenceFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

  ExtendedGUID m_gosid;
public:
  ObjectSpaceManifestListReferenceFND(StpFormat stpFormat,
                                      CbFormat cbFormat);

  ~ObjectSpaceManifestListReferenceFND();


  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTSPACEMANIFESTLISTREFERENCEFND_H
