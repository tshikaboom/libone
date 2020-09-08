#ifndef OBJECTDECLARATION2BODY_H
#define OBJECTDECLARATION2BODY_H

#include "CompactID.h"
#include "JCID.h"

#include "libone_utils.h"

namespace libone
{

class ObjectDeclaration2Body
{
private:
  CompactID m_oid;
  JCID m_jcid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

public:
  ObjectDeclaration2Body();

  CompactID getOid() const;
  void setOid(const CompactID &value);
  JCID getJcid() const;
  void setJcid(const JCID &value);
  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);
  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ObjectDeclaration2Body &obj);

  void parse(const libone::RVNGInputStreamPtr_t &input);

  std::string to_string() const;
};

} // namespace libone

#endif // OBJECTDECLARATION2BODY_H
