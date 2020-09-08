#include "ObjectDeclaration2RefCountFND.h"

namespace libone
{

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_blobRef(stpFormat, cbFormat), m_body(), m_cRef{} {}

uint8_t ObjectDeclaration2RefCountFND::getCRef() const
{
  return m_cRef;
}

void ObjectDeclaration2RefCountFND::setCRef(const uint8_t &value)
{
  m_cRef = value;
}

ObjectDeclaration2Body ObjectDeclaration2RefCountFND::getBody() const
{
  return m_body;
}

void ObjectDeclaration2RefCountFND::setBody(
  const ObjectDeclaration2Body &value)
{
  m_body = value;
}

FileNodeChunkReference ObjectDeclaration2RefCountFND::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDeclaration2RefCountFND::setBlobRef(
  const FileNodeChunkReference &value)
{
  m_blobRef = value;
}

void ObjectDeclaration2RefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_blobRef;
  input >> m_body;
  input >> m_cRef;
}

std::string ObjectDeclaration2RefCountFND::to_string() const
{
  return "";
}

} // namespace libone
