#ifndef READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
#define READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H

#include <array>

#include "../FileNodeChunkReference.h"
#include "IFileNodeData.h"
#include "ObjectDeclaration2LargeRefCountFND.h"

namespace libone
{
class ReadOnlyObjectDeclaration2LargeRefCountFND : public IFileNodeData
{
private:
  StpFormat m_stpFormat;
  CbFormat m_cbFormat;

  ObjectDeclaration2LargeRefCountFND m_base;

  std::array<unsigned char, 16> m_md5hash;

public:
  ReadOnlyObjectDeclaration2LargeRefCountFND(StpFormat stpFormat,
                                             CbFormat cbFormat);

  ~ReadOnlyObjectDeclaration2LargeRefCountFND();

  FileNodeChunkReference ref() const;
  void setRef(const FileNodeChunkReference &ref);
  ObjectDeclaration2LargeRefCountFND getBase() const;
  void setBase(const ObjectDeclaration2LargeRefCountFND &value);

  std::array<unsigned char, 16> getMd5hash() const;
  void setMd5hash(const std::array<unsigned char, 16> &value);

  StpFormat getStpFormat() const;

  CbFormat getCbFormat() const;

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
