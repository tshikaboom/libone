#ifndef OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
#define OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H

#include "../CompactID.h"
#include "../StringInStorageBuffer.h"
#include "../JCID.h"
#include "IFileNodeData.h"

namespace libone
{
class ObjectDeclarationFileData3LargeRefCountFND : public IFileNodeData
{
private:
  CompactID m_oid;
  JCID m_jcid;

  uint32_t m_cRef;

  StringInStorageBuffer m_FileDataReference;
  StringInStorageBuffer m_Extension;

public:
  ObjectDeclarationFileData3LargeRefCountFND();

  CompactID oid() const;
  void setOid(const CompactID &oid);

  JCID jcid() const;
  void setJcid(const JCID &jcid);

  uint32_t cRef() const;
  void setCRef(const uint32_t &cRef);

  StringInStorageBuffer FileDataReference() const;
  void setFileDataReference(const StringInStorageBuffer &FileDataReference);

  StringInStorageBuffer Extension() const;
  void setExtension(const StringInStorageBuffer &Extension);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone
#endif // OBJECTDECLARATIONFILEDATA3LARGEREFCOUNTFND_H
