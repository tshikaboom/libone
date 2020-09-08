#include "ObjectDeclarationWithRefCount2FNDX.h"


namespace libone
{
ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_objectRef(stpFormat, cbFormat), m_body(), m_cRef{} {}

ObjectDeclarationWithRefCount2FNDX::~ObjectDeclarationWithRefCount2FNDX() {}

FileNodeChunkReference
ObjectDeclarationWithRefCount2FNDX::getObjectRef() const
{
  return m_objectRef;
}

void ObjectDeclarationWithRefCount2FNDX::setObjectRef(
  const FileNodeChunkReference &value)
{
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCount2FNDX::getBody() const
{
  return m_body;
}

void ObjectDeclarationWithRefCount2FNDX::setBody(
  const ObjectDeclarationWithRefCountBody &value)
{
  m_body = value;
}

uint32_t ObjectDeclarationWithRefCount2FNDX::getCRef() const
{
  return m_cRef;
}

void ObjectDeclarationWithRefCount2FNDX::setCRef(const uint32_t &value)
{
  m_cRef = value;
}

void ObjectDeclarationWithRefCount2FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_objectRef;
  input >> m_body;
  input >> m_cRef;
}

std::string ObjectDeclarationWithRefCount2FNDX::to_string() const
{
  return "";
}

} // namespace libone
