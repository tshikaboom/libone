#include "GlobalIdTableStartFNDX.h"

namespace libone
{

GlobalIdTableStartFNDX::GlobalIdTableStartFNDX() : m_reserved{0} {}

uint8_t GlobalIdTableStartFNDX::getReserved() const
{
  return m_reserved;
}

void GlobalIdTableStartFNDX::setReserved(const uint8_t &value)
{
  m_reserved = value;
}

void GlobalIdTableStartFNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;
}

std::string GlobalIdTableStartFNDX::to_string() const
{
}

} // namespace libone
