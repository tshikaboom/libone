#ifndef OBJECTSPACEMANIFESTLISTSTARTFND_H
#define OBJECTSPACEMANIFESTLISTSTARTFND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"

namespace libone
{
class ObjectSpaceManifestListStartFND : public IFileNodeData
{
private:
  ExtendedGUID m_gosid;

public:
  ObjectSpaceManifestListStartFND();
  ~ObjectSpaceManifestListStartFND() = default;

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

  IFileNodeData *clone() const override
  {
    return new ObjectSpaceManifestListStartFND(*this);
  }
};

} // namespace libone

#endif // OBJECTSPACEMANIFESTLISTSTARTFND_H
