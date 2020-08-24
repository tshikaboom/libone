#include "GlobalIdTableEntry3FNDX.h"

namespace libone
{

GlobalIdTableEntry3FNDX::GlobalIdTableEntry3FNDX()
  : m_iIndexCopyFromStart{0}, m_cEntriesToCopy{0}, m_iIndexCopyToStart{0} {}

uint32_t GlobalIdTableEntry3FNDX::getIIndexCopyFromStart() const
{
  return m_iIndexCopyFromStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyFromStart(const uint32_t &value)
{
  m_iIndexCopyFromStart = value;
}

uint32_t GlobalIdTableEntry3FNDX::getCEntriesToCopy() const
{
  return m_cEntriesToCopy;
}

void GlobalIdTableEntry3FNDX::setCEntriesToCopy(const uint32_t &value)
{
  m_cEntriesToCopy = value;
}

uint32_t GlobalIdTableEntry3FNDX::getIIndexCopyToStart() const
{
  return m_iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyToStart(const uint32_t &value)
{
  m_iIndexCopyToStart = value;
}

void GlobalIdTableEntry3FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_iIndexCopyFromStart;
  input >> m_cEntriesToCopy;
  input >> m_iIndexCopyToStart;
}

std::string GlobalIdTableEntry3FNDX::to_string() const
{
  return "";
}


} //namespace libone
