#ifndef REVISIONMANIFESTLISTSTARTFND_H
#define REVISIONMANIFESTLISTSTARTFND_H

#include "IFileNodeData.h"

#include "../ExtendedGUID.h"

namespace libone
{

class RevisionManifestListStartFND : public IFileNodeData
{
private:
  ExtendedGUID m_gosid;

  uint32_t m_nInstance;

public:
  RevisionManifestListStartFND();
  ~RevisionManifestListStartFND();

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);
  uint32_t getNInstance() const;
  void setNInstance(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // REVISIONMANIFESTLISTSTARTFND_H
