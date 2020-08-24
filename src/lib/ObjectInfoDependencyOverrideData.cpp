#include "ObjectInfoDependencyOverrideData.h"

namespace libone
{

ObjectInfoDependencyOverrideData::ObjectInfoDependencyOverrideData()
  : m_c8BitOverrides(), m_c32BitOverrides(), m_crc(), m_Overrides1{}, m_Overrides2{} {}


uint32_t ObjectInfoDependencyOverrideData::c8BitOverrides() const
{
  return m_c8BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC8BitOverrides(
  const uint32_t &c8BitOverrides)
{
  m_c8BitOverrides = c8BitOverrides;
}

uint32_t ObjectInfoDependencyOverrideData::c32BitOverrides() const
{
  return m_c32BitOverrides;
}

void ObjectInfoDependencyOverrideData::setC32BitOverrides(
  const uint32_t &c32BitOverrides)
{
  m_c32BitOverrides = c32BitOverrides;
}

uint32_t ObjectInfoDependencyOverrideData::crc() const
{
  return m_crc;
}

void ObjectInfoDependencyOverrideData::setCrc(const uint32_t &crc)
{
  m_crc = crc;
}

std::vector<ObjectInfoDependencyOverride8>
ObjectInfoDependencyOverrideData::Overrides1() const
{
  return m_Overrides1;
}

void ObjectInfoDependencyOverrideData::setOverrides1(
  const std::vector<ObjectInfoDependencyOverride8> &Overrides1)
{
  m_Overrides1 = Overrides1;
}

std::vector<ObjectInfoDependencyOverride32>
ObjectInfoDependencyOverrideData::Overrides2() const
{
  return m_Overrides2;
}

void ObjectInfoDependencyOverrideData::setOverrides2(
  const std::vector<ObjectInfoDependencyOverride32> &Overrides2)
{
  m_Overrides2 = Overrides2;
}


const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                               ObjectInfoDependencyOverrideData &obj)
{
  obj.parse(input);
  return input;
}

void ObjectInfoDependencyOverrideData::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_c8BitOverrides;
  input >> m_c32BitOverrides;
  input >> m_crc;

  ObjectInfoDependencyOverride8 temp8;
  for (size_t i{0}; i < m_c8BitOverrides; i++)
  {
    input >> temp8;
    m_Overrides1.push_back(temp8);
  }

  ObjectInfoDependencyOverride32 temp32;
  for (size_t i{0}; i < m_c8BitOverrides; i++)
  {
    input >> temp32;
    m_Overrides2.push_back(temp32);
  }
}

std::string ObjectInfoDependencyOverrideData::to_string() const
{
  return "";
}

} // namespace libone
