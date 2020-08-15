#include "ObjectInfoDependencyOverridesFND.h"

namespace libone
{
ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat), m_data() {}

ObjectInfoDependencyOverridesFND::~ObjectInfoDependencyOverridesFND() {}

ObjectInfoDependencyOverrideData
ObjectInfoDependencyOverridesFND::getData() const
{
  return m_data;
}

void ObjectInfoDependencyOverridesFND::setData(
  const ObjectInfoDependencyOverrideData &value)
{
  m_data = value;
}

FileNodeChunkReference ObjectInfoDependencyOverridesFND::getRef() const
{
  return m_ref;
}

void ObjectInfoDependencyOverridesFND::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void ObjectInfoDependencyOverridesFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;

  if (m_ref.is_fcrNil())
  {
    input >> m_data;
  }
  else
  {
    uint64_t currentloc = input->tell();
    input->seek(m_ref.stp(), librevenge::RVNG_SEEK_SET);
    input >> m_data;
    input->seek(currentloc, librevenge::RVNG_SEEK_SET);
  }
}

std::string ObjectInfoDependencyOverridesFND::to_string() const
{
  return "";
}

} // namespace libone
