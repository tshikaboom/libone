#ifndef OBJECTDECLARATION2REFCOUNTFND_H
#define OBJECTDECLARATION2REFCOUNTFND_H

#include "../FileNodeChunkReference.h"
#include "../ObjectDeclaration2Body.h"
#include "IFileNodeData.h"

namespace libone
{
class ObjectDeclaration2RefCountFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_blobRef;

  ObjectDeclaration2Body m_body;

  uint8_t m_cRef;
public:
  ObjectDeclaration2RefCountFND(StpFormat stpFormat,
                                CbFormat cbFormat);
  ~ObjectDeclaration2RefCountFND() = default;

  FileNodeChunkReference getBlobRef() const;
  void setBlobRef(const FileNodeChunkReference &value);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body &value);

  uint8_t getCRef() const;
  void setCRef(const uint8_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // OBJECTDECLARATION2REFCOUNTFND_H
