#ifndef OBJECTINFODEPENDENCYOVERRIDE8_H
#define OBJECTINFODEPENDENCYOVERRIDE8_H

#include "CompactID.h"

namespace libone
{

class ObjectInfoDependencyOverride8
{
private:
  CompactID m_oid;
  uint8_t m_cRef;

public:
  ObjectInfoDependencyOverride8();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  uint8_t cRef() const;
  void setCRef(const uint8_t &cRef);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                                        ObjectInfoDependencyOverride8 &obj);
  void parse(const libone::RVNGInputStreamPtr_t &input);

  std::string to_string() const;
};

} // namespace libone

#endif // OBJECTINFODEPENDENCYOVERRIDE8_H
