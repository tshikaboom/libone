#ifndef OBJECTSPACEMANIFESTROOTFND_H
#define OBJECTSPACEMANIFESTROOTFND_H

#include "IFileNodeData.h"

#include "../ExtendedGUID.h"

namespace libone
{
class ObjectSpaceManifestRootFND : public IFileNodeData
{
private:
  ExtendedGUID m_gosidRoot;

public:
  ObjectSpaceManifestRootFND();
  ~ObjectSpaceManifestRootFND();

  ExtendedGUID getGosidRoot() const;
  void setGosidRoot(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

  IFileNodeData *clone() const override
  {
    return new ObjectSpaceManifestRootFND(*this);
  }
};

} // namespace libone

#endif // OBJECTSPACEMANIFESTROOTFND_H
