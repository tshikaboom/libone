#include "ReadOnlyObjectDeclaration2LargeRefCountFND.h"

#include <algorithm>

namespace libone
{
ReadOnlyObjectDeclaration2LargeRefCountFND::
ReadOnlyObjectDeclaration2LargeRefCountFND(StpFormat stpFormat,
                                           CbFormat cbFormat)
  : m_stpFormat(stpFormat), m_cbFormat(cbFormat),
    m_base(stpFormat, cbFormat), m_md5hash() {}

ReadOnlyObjectDeclaration2LargeRefCountFND::
~ReadOnlyObjectDeclaration2LargeRefCountFND() {}

StpFormat
ReadOnlyObjectDeclaration2LargeRefCountFND::getStpFormat() const
{
  return m_stpFormat;
}

CbFormat ReadOnlyObjectDeclaration2LargeRefCountFND::getCbFormat() const
{
  return m_cbFormat;
}

ObjectDeclaration2LargeRefCountFND
ReadOnlyObjectDeclaration2LargeRefCountFND::getBase() const
{
  return m_base;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setBase(
  const ObjectDeclaration2LargeRefCountFND &value)
{
  m_base = value;
}

std::array<unsigned char, 16> ReadOnlyObjectDeclaration2LargeRefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::setMd5hash(
  const std::array<unsigned char, 16> &value)
{
  m_md5hash = value;
}

void ReadOnlyObjectDeclaration2LargeRefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{

  m_base = ObjectDeclaration2LargeRefCountFND(m_stpFormat, m_cbFormat);
  input >> m_base;

  const  unsigned char *md5hashRaw {};
  md5hashRaw = readNBytes(input, 16);

  std::copy_n(md5hashRaw, 16, std::begin(m_md5hash));
}

std::string ReadOnlyObjectDeclaration2LargeRefCountFND::to_string() const
{
  return "";
}

} // namespace libone
