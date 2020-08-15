#ifndef READONLYOBJECTDECLARATION2REFCOUNTFND_H
#define READONLYOBJECTDECLARATION2REFCOUNTFND_H

#include "IFileNodeData.h"
#include "ObjectDeclaration2RefCountFND.h"
#include "../FileNodeChunkReference.h"

namespace libone
{

class ReadOnlyObjectDeclaration2RefCountFND : public IFileNodeData
{
private:
  StpFormat m_stpFormat;
  CbFormat m_cbFormat;
  ObjectDeclaration2RefCountFND m_base;

  std::array<unsigned char, 16> m_md5hash;

public:
  ReadOnlyObjectDeclaration2RefCountFND(StpFormat stpFormat,
                                        CbFormat cbFormat);

  ~ReadOnlyObjectDeclaration2RefCountFND();

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);
  ObjectDeclaration2RefCountFND getBase() const;
  void setBase(const ObjectDeclaration2RefCountFND &value);

  std::array<unsigned char, 16> getMd5hash() const;
  void setMd5hash(const std::array<unsigned char, 16> &value);

  StpFormat getStpFormat() const;
  CbFormat getCbFormat() const;

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // READONLYOBJECTDECLARATION2REFCOUNTFND_H
