#include "GlobalIdTableEntry2FNDX.h"

#include "../libone_utils.h"

namespace libone
{

GlobalIdTableEntry2FNDX::GlobalIdTableEntry2FNDX()
  : m_iIndexMapFrom{0}, m_iIndexMapTo{0} {}

uint32_t GlobalIdTableEntry2FNDX::getIIndexMapFrom() const
{
  return m_iIndexMapFrom;
}

void GlobalIdTableEntry2FNDX::setIIndexMapFrom(const uint32_t &value)
{
  m_iIndexMapFrom = value;
}

uint32_t GlobalIdTableEntry2FNDX::getIIndexMapTo() const
{
  return m_iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::setIIndexMapTo(const uint32_t &value)
{
  m_iIndexMapTo = value;
}

void GlobalIdTableEntry2FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_iIndexMapFrom;
  input >> m_iIndexMapTo;
}

std::string GlobalIdTableEntry2FNDX::to_string() const
{
  return "";
}

} // namespace libone
