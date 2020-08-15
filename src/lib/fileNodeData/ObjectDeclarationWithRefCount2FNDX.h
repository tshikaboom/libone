#ifndef OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
#define OBJECTDECLARATIONWITHREFCOUNT2FNDX_H


#include "../FileNodeChunkReference.h"
#include "../ObjectDeclarationWithRefCountBody.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectDeclarationWithRefCount2FNDX : public IFileNodeData
{
private:
  FileNodeChunkReference m_objectRef;

  ObjectDeclarationWithRefCountBody m_body;

  uint32_t m_cRef;
public:
  ObjectDeclarationWithRefCount2FNDX(StpFormat stpFormat,
                                     CbFormat cbFormat);
  ~ObjectDeclarationWithRefCount2FNDX();



  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  uint32_t getCRef() const;
  void setCRef(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // OBJECTDECLARATIONWITHREFCOUNT2FNDX_H
