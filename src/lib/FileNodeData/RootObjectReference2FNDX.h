#ifndef ROOTOBJECTREFERENCE2FNDX_H
#define ROOTOBJECTREFERENCE2FNDX_H

#include "../CompactID.h"
#include "IFileNodeData.h"

namespace libone
{

class RootObjectReference2FNDX : public IFileNodeData
{
private:
  CompactID m_oidRoot;
  uint32_t m_RootRole;

public:
  RootObjectReference2FNDX();

  CompactID getOidRoot() const;
  void setOidRoot(const CompactID &value);

  uint32_t getRootRole() const;
  void setRootRole(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // ROOTOBJECTREFERENCE2FNDX_H
