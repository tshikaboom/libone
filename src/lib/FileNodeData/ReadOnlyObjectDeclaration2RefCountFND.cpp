#include "ReadOnlyObjectDeclaration2RefCountFND.h"

#include <algorithm>

namespace libone
{

ReadOnlyObjectDeclaration2RefCountFND::ReadOnlyObjectDeclaration2RefCountFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_stpFormat(stpFormat), m_cbFormat(cbFormat),
    m_base(stpFormat, cbFormat), m_md5hash() {}

ReadOnlyObjectDeclaration2RefCountFND::
~ReadOnlyObjectDeclaration2RefCountFND() {}


StpFormat ReadOnlyObjectDeclaration2RefCountFND::getStpFormat() const
{
  return m_stpFormat;
}

CbFormat ReadOnlyObjectDeclaration2RefCountFND::getCbFormat() const
{
  return m_cbFormat;
}

ObjectDeclaration2RefCountFND
ReadOnlyObjectDeclaration2RefCountFND::getBase() const
{
  return m_base;
}

void ReadOnlyObjectDeclaration2RefCountFND::setBase(
  const ObjectDeclaration2RefCountFND &value)
{
  m_base = value;
}

std::array<unsigned char, 16> ReadOnlyObjectDeclaration2RefCountFND::getMd5hash() const
{
  return m_md5hash;
}

void ReadOnlyObjectDeclaration2RefCountFND::setMd5hash(
  const std::array<unsigned char, 16> &value)
{
  m_md5hash = value;
}

void ReadOnlyObjectDeclaration2RefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{

  m_base = ObjectDeclaration2RefCountFND(m_stpFormat, m_cbFormat);
  input >> m_base;

  const unsigned char *md5hashRaw;
  md5hashRaw = readNBytes(input, 16);
  std::copy_n(md5hashRaw, 16, std::begin(m_md5hash));

}

std::string ReadOnlyObjectDeclaration2RefCountFND::to_string() const
{
  return "";
}

} // namespace libone
