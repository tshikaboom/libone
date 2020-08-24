#ifndef OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H

#include "IFileNodeData.h"

#include "../CompactID.h"
#include "../StringInStorageBuffer.h"
#include "../JCID.h"

namespace libone
{
class ObjectDeclarationFileData3RefCountFND : public IFileNodeData
{
private:
  CompactID m_oid;
  JCID m_jcid;

  uint8_t m_cRef = 0;

  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3RefCountFND();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  JCID jcid() const;
  void setJcid(const JCID &jcid);

  uint8_t cRef() const;
  void setCRef(const uint8_t &cRef);

  StringInStorageBuffer FileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer &FileDataReference);

  StringInStorageBuffer Extension() const;
  void setExtension(const StringInStorageBuffer &Extension);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTDECLARATIONFILEDATA3REFCOUNTFND_H
