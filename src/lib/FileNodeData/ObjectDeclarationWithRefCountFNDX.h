#ifndef OBJECTDECLARATIONWITHREFCOUNTFNDX_H
#define OBJECTDECLARATIONWITHREFCOUNTFNDX_H

#include "../FileNodeChunkReference.h"
#include "../ObjectDeclarationWithRefCountBody.h"
#include "IFileNodeData.h"

namespace libone
{

class ObjectDeclarationWithRefCountFNDX : public IFileNodeData
{
private:

  FileNodeChunkReference m_objectRef;

  ObjectDeclarationWithRefCountBody m_body;

  uint8_t m_cRef;

public:
  ObjectDeclarationWithRefCountFNDX(StpFormat stpFormat,
                                    CbFormat cbFormat);
  ~ObjectDeclarationWithRefCountFNDX();



  FileNodeChunkReference getObjectRef() const;
  void setObjectRef(const FileNodeChunkReference &value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody &value);

  uint8_t getCRef() const;
  void setCRef(const uint8_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTDECLARATIONWITHREFCOUNTFNDX_H
