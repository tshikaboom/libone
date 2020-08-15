#include "ObjectDeclarationFileData3LargeRefCountFND.h"

namespace libone
{

ObjectDeclarationFileData3LargeRefCountFND::
ObjectDeclarationFileData3LargeRefCountFND() : m_oid(), m_jcid(), m_cRef(), m_FileDataReference(), m_Extension() {}

CompactID ObjectDeclarationFileData3LargeRefCountFND::oid() const
{
  return m_oid;
}

void ObjectDeclarationFileData3LargeRefCountFND::setOid(const CompactID &oid)
{
  m_oid = oid;
}

JCID ObjectDeclarationFileData3LargeRefCountFND::jcid() const
{
  return m_jcid;
}

void ObjectDeclarationFileData3LargeRefCountFND::setJcid(const JCID &jcid)
{
  m_jcid = jcid;
}

uint32_t ObjectDeclarationFileData3LargeRefCountFND::cRef() const
{
  return m_cRef;
}

void ObjectDeclarationFileData3LargeRefCountFND::setCRef(const uint32_t &cRef)
{
  m_cRef = cRef;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::FileDataReference() const
{
  return m_FileDataReference;
}

void ObjectDeclarationFileData3LargeRefCountFND::setFileDataReference(
  const StringInStorageBuffer &FileDataReference)
{
  m_FileDataReference = FileDataReference;
}

StringInStorageBuffer
ObjectDeclarationFileData3LargeRefCountFND::Extension() const
{
  return m_Extension;
}

void ObjectDeclarationFileData3LargeRefCountFND::setExtension(
  const StringInStorageBuffer &Extension)
{
  m_Extension = Extension;
}


void ObjectDeclarationFileData3LargeRefCountFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
  input >> m_jcid;
  input >> m_cRef;
  input >> m_FileDataReference;
  input >> m_Extension;
}

std::string ObjectDeclarationFileData3LargeRefCountFND::to_string() const
{
  return "";
}

} // namespace libone
