#ifndef OBJECTDECLARATIONWITHREFCOUNTBODY_H
#define OBJECTDECLARATIONWITHREFCOUNTBODY_H

#include "CompactID.h"

namespace libone
{

class ObjectDeclarationWithRefCountBody
{
private:
  CompactID m_oid;

  uint8_t m_jci;
  uint8_t m_odcs;

  uint8_t m_fReserved1;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  uint32_t m_fReserved2;

public:
  ObjectDeclarationWithRefCountBody();


  CompactID getOid() const;
  void setOid(const CompactID &value);

  uint8_t getJci() const;
  void setJci(const uint8_t &value);

  uint8_t getOdc() const;
  void setOdc(const uint8_t &value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                                        ObjectDeclarationWithRefCountBody &obj);

  void parse(const libone::RVNGInputStreamPtr_t &input);

  std::string to_string() const;
};

} // namespace libone

#endif // OBJECTDECLARATIONWITHREFCOUNTBODY_H
