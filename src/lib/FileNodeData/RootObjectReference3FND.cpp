#include "RootObjectReference3FND.h"

namespace libone
{
RootObjectReference3FND::RootObjectReference3FND() :m_oidRoot(),  m_RootRole(0) {}

uint32_t RootObjectReference3FND::getRootRole() const
{
  return m_RootRole;
}

void RootObjectReference3FND::setRootRole(const uint32_t &value)
{
  m_RootRole = value;
}

ExtendedGUID RootObjectReference3FND::getOidRoot() const
{
  return m_oidRoot;
}

void RootObjectReference3FND::setOidRoot(const ExtendedGUID &value)
{
  m_oidRoot = value;
}

void RootObjectReference3FND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oidRoot;
  input >> m_RootRole;
}

std::string RootObjectReference3FND::to_string() const
{
  return "";
}

} // namespace libone
