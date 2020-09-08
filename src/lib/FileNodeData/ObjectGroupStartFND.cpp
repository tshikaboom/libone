#include "ObjectGroupStartFND.h"


namespace libone
{
ObjectGroupStartFND::ObjectGroupStartFND()
  : m_oid(ExtendedGUID())
{
}

ExtendedGUID ObjectGroupStartFND::oid() const
{
  return m_oid;
}

void ObjectGroupStartFND::setOid(const ExtendedGUID &oid)
{
  m_oid = oid;
}


void ObjectGroupStartFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_oid;
}

std::string ObjectGroupStartFND::to_string() const
{
  return "";
}
} // namespace libone
