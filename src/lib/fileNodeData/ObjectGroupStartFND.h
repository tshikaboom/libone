#ifndef OBJECTGROUPSTARTFND_H
#define OBJECTGROUPSTARTFND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectGroupStartFND : public IFileNodeData
{
private:
  ExtendedGUID m_oid;
public:
  ObjectGroupStartFND();

  ExtendedGUID oid() const;
  void setOid(const ExtendedGUID &oid);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTGROUPSTARTFND_H
