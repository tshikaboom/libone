#include "DataSignatureGroupDefinitionFND.h"

namespace libone
{

DataSignatureGroupDefinitionFND::DataSignatureGroupDefinitionFND()
  : m_dataSignatureGroup()
{}

ExtendedGUID DataSignatureGroupDefinitionFND::dataSignatureGroup() const
{
  return m_dataSignatureGroup;
}

void DataSignatureGroupDefinitionFND::setDataSignatureGroup(const ExtendedGUID &DataSignatureGroup)
{
  m_dataSignatureGroup = DataSignatureGroup;
}


void DataSignatureGroupDefinitionFND::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_dataSignatureGroup;
}

std::string DataSignatureGroupDefinitionFND::to_string() const
{
  return "";
}

} // namespace libone
