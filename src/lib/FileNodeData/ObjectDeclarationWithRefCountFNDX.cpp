#include "ObjectDeclarationWithRefCountFNDX.h"

namespace libone
{

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_objectRef(stpFormat, cbFormat), m_body(), m_cRef() {}

ObjectDeclarationWithRefCountFNDX::~ObjectDeclarationWithRefCountFNDX() {}

FileNodeChunkReference ObjectDeclarationWithRefCountFNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCountFNDX::setObjectRef(
  const FileNodeChunkReference &value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCountFNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCountFNDX::setBody(
  const ObjectDeclarationWithRefCountBody &value)
{
  m_body = value;
}

uint8_t ObjectDeclarationWithRefCountFNDX::getCRef() const
{
  return m_cRef;
}

void ObjectDeclarationWithRefCountFNDX::setCRef(const uint8_t &value)
{
  m_cRef = value;
}

void ObjectDeclarationWithRefCountFNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_objectRef;
  input >> m_body;
  input>> m_cRef;
}

std::string ObjectDeclarationWithRefCountFNDX::to_string() const
{
  return "";
}

} // namespace libone
