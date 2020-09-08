#include "ObjectDeclarationFileData3RefCountFND.h"

namespace libone
{

ObjectDeclarationFileData3RefCountFND::ObjectDeclarationFileData3RefCountFND() :
  m_oid(), m_jcid(), m_cRef{}, m_FileDataReference(), m_Extension() {}

CompactID ObjectDeclarationFileData3RefCountFND::oid() const
{
  return m_oid;
}

void ObjectDeclarationFileData3RefCountFND::setOid(const CompactID &oid)
{
  m_oid = oid;
}

JCID ObjectDeclarationFileData3RefCountFND::jcid() const
{
  return m_jcid;
}

void ObjectDeclarationFileData3RefCountFND::setJcid(const JCID &jcid)
{
  m_jcid = jcid;
}

uint8_t ObjectDeclarationFileData3RefCountFND::cRef() const
{
  return m_cRef;
}

void ObjectDeclarationFileData3RefCountFND::setCRef(const uint8_t &cRef)
{
  m_cRef = cRef;
}

StringInStorageBuffer ObjectDeclarationFileData3RefCountFND::FileDataReference() const
{
  return m_FileDataReference;
}

void ObjectDeclarationFileData3RefCountFND::setFileDataReference(const StringInStorageBuffer &FileDataReference)
{
  m_FileDataReference = FileDataReference;
}

StringInStorageBuffer ObjectDeclarationFileData3RefCountFND::Extension() const
{
  return m_Extension;
}

void ObjectDeclarationFileData3RefCountFND::setExtension(const StringInStorageBuffer &Extension)
{
  m_Extension = Extension;
}

void ObjectDeclarationFileData3RefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  input >> m_jcid;
  input >> m_cRef;
  input >> m_FileDataReference;
  input >> m_Extension;
}

std::string ObjectDeclarationFileData3RefCountFND::to_string() const
{
  return "";
}

} // namespace libone
