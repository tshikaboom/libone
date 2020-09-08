#include "GlobalIdTableEntryFNDX.h"

namespace libone
{

GlobalIdTableEntryFNDX::GlobalIdTableEntryFNDX() : m_index{0}, m_guid() {}

GUID GlobalIdTableEntryFNDX::getGuid() const
{
  return m_guid;
}

void GlobalIdTableEntryFNDX::setGuid(const GUID &value)
{
  m_guid = value;
}

uint32_t GlobalIdTableEntryFNDX::getIndex() const
{
  return m_index;
}

void GlobalIdTableEntryFNDX::setIndex(const uint32_t &value)
{
  m_index = value;
}

void GlobalIdTableEntryFNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_index;
  input >> m_guid;
}

std::string GlobalIdTableEntryFNDX::to_string() const
{
  return "";
}

} // namespace libone
