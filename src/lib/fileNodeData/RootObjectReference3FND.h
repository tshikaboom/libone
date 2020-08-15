#ifndef ROOTOBJECTREFERENCE3FND_H
#define ROOTOBJECTREFERENCE3FND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"

namespace libone
{

class RootObjectReference3FND : public IFileNodeData
{
private:
  ExtendedGUID m_oidRoot;
  uint32_t m_RootRole;

public:
  RootObjectReference3FND();

  ExtendedGUID getOidRoot() const;
  void setOidRoot(const ExtendedGUID &value);

  uint32_t getRootRole() const;
  void setRootRole(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // ROOTOBJECTREFERENCE3FND_H
