#ifndef OBJECTREVISIONWITHREFCOUNT2FNDX_H
#define OBJECTREVISIONWITHREFCOUNT2FNDX_H

#include "../CompactID.h"
#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectRevisionWithRefCount2FNDX : public IFileNodeData
{
private:

  FileNodeChunkReference m_ref;

  CompactID m_oid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  uint32_t m_cRef;

public:
  ObjectRevisionWithRefCount2FNDX(StpFormat stpFormat,
                                  CbFormat cbFormat);

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  CompactID getOid() const;
  void setOid(const CompactID &value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  uint32_t getCRef() const;
  void setCRef(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTREVISIONWITHREFCOUNT2FNDX_H
