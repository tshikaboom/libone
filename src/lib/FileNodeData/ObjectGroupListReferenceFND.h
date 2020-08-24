#ifndef OBJECTGROUPLISTREFERENCEFND_H
#define OBJECTGROUPLISTREFERENCEFND_H

#include "../ExtendedGUID.h"
#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectGroupListReferenceFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

  ExtendedGUID m_ObjectGroupID;

public:
  ObjectGroupListReferenceFND(StpFormat stpFormat,
                              CbFormat cbFormat);
  ~ObjectGroupListReferenceFND() = default;

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);

  ExtendedGUID objectGroupID() const;
  void setObjectGroupID(const ExtendedGUID &objectGroupID);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTGROUPLISTREFERENCEFND_H
