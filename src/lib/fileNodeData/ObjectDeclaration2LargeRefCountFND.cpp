#include "ObjectDeclaration2LargeRefCountFND.h"

namespace libone
{

ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_BlobRef(stpFormat, cbFormat), m_body(), m_cRef() {}

ObjectDeclaration2LargeRefCountFND::~ObjectDeclaration2LargeRefCountFND() {}

ObjectDeclaration2Body ObjectDeclaration2LargeRefCountFND::body() const
{
  return m_body;
}

void ObjectDeclaration2LargeRefCountFND::setBody(
  const ObjectDeclaration2Body &body)
{
  m_body = body;
}

uint32_t ObjectDeclaration2LargeRefCountFND::cRef() const
{
  return m_cRef;
}

void ObjectDeclaration2LargeRefCountFND::setCRef(const uint32_t &cRef)
{
  m_cRef = cRef;
}

FileNodeChunkReference ObjectDeclaration2LargeRefCountFND::BlobRef() const
{
  return m_BlobRef;
}

void ObjectDeclaration2LargeRefCountFND::setBlobRef(
  const FileNodeChunkReference &BlobRef)
{
  m_BlobRef = BlobRef;
}

void ObjectDeclaration2LargeRefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_BlobRef;
  input >> m_body;
  input >> m_cRef;
}

std::string ObjectDeclaration2LargeRefCountFND::to_string() const
{
  return "";
}

} // namespace libone
