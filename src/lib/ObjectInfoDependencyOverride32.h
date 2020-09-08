#ifndef OBJECTINFODEPENDENCYOVERRIDE32_H
#define OBJECTINFODEPENDENCYOVERRIDE32_H

#include "CompactID.h"

namespace libone
{

class ObjectInfoDependencyOverride32
{
private:
  CompactID m_oid;
  uint32_t m_cRef;

public:
  ObjectInfoDependencyOverride32();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  uint32_t cRef() const;
  void setCRef(const uint32_t &cRef);


  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                                        ObjectInfoDependencyOverride32 &obj);
  void parse(const libone::RVNGInputStreamPtr_t &input);

  std::string to_string() const;
};

} // namespace libone

#endif // OBJECTINFODEPENDENCYOVERRIDE32_H
