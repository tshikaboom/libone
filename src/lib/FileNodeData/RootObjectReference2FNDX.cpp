#include "RootObjectReference2FNDX.h"

namespace libone
{

RootObjectReference2FNDX::RootObjectReference2FNDX() :
  m_oidRoot(), m_RootRole(0) {}

CompactID RootObjectReference2FNDX::getOidRoot() const
{
  return m_oidRoot;
}

void RootObjectReference2FNDX::setOidRoot(const CompactID &value)
{
  m_oidRoot = value;
}

uint32_t RootObjectReference2FNDX::getRootRole() const
{
  return m_RootRole;
}

void RootObjectReference2FNDX::setRootRole(const uint32_t &value)
{
  m_RootRole = value;
}

void RootObjectReference2FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oidRoot;
  input >> m_RootRole;
}

std::string RootObjectReference2FNDX::to_string() const
{
  return "";
}

} // namespace libone
