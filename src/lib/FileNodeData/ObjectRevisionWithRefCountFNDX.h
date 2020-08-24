#ifndef OBJECTREVISIONWITHREFCOUNTFNDX_H
#define OBJECTREVISIONWITHREFCOUNTFNDX_H

#include "../CompactID.h"
#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectRevisionWithRefCountFNDX : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

  CompactID m_oid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  uint8_t m_cRef;

public:
  ObjectRevisionWithRefCountFNDX(StpFormat stpFormat,
                                 CbFormat cbFormat);
  ~ObjectRevisionWithRefCountFNDX() = default;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);
  CompactID getOid() const;
  void setOid(const CompactID &value);
  uint8_t getCRef() const;
  void setCRef(const uint8_t &value);
  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);
  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTREVISIONWITHREFCOUNTFNDX_H
