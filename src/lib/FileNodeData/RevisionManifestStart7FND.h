#ifndef REVISIONMANIFESTSTART7FND_H
#define REVISIONMANIFESTSTART7FND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"
#include "RevisionManifestStart6FND.h"

namespace libone
{

class RevisionManifestStart7FND : public IFileNodeData
{
private:
  RevisionManifestStart6FND m_base;

  ExtendedGUID m_gctxid;

public:
  RevisionManifestStart7FND();

  RevisionManifestStart6FND getBase() const;
  void setBase(const RevisionManifestStart6FND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // REVISIONMANIFESTSTART7FND_H
