#ifndef OBJECTDECLARATION2LARGEREFCOUNTFND_H
#define OBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../FileNodeChunkReference.h"
#include "../ObjectDeclaration2Body.h"
#include "IFileNodeData.h"


namespace libone
{
class ObjectDeclaration2LargeRefCountFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_BlobRef;

  ObjectDeclaration2Body m_body;

  uint32_t m_cRef;

public:
  ObjectDeclaration2LargeRefCountFND(StpFormat stpFormat,
                                     CbFormat cbFormat);

  ~ObjectDeclaration2LargeRefCountFND();


  FileNodeChunkReference BlobRef() const;
  void setBlobRef(const FileNodeChunkReference &BlobRef);

  ObjectDeclaration2Body body() const;
  void setBody(const ObjectDeclaration2Body &body);

  uint32_t cRef() const;
  void setCRef(const uint32_t &cRef);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone
#endif // OBJECTDECLARATION2LARGEREFCOUNTFND_H
