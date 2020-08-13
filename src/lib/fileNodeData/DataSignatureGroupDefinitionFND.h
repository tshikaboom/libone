#ifndef DATASIGNATUREGROUPDEFINITIONFND_H
#define DATASIGNATUREGROUPDEFINITIONFND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"

namespace libone
{

class DataSignatureGroupDefinitionFND : public IFileNodeData
{
private:
  ExtendedGUID m_dataSignatureGroup;
public:
  DataSignatureGroupDefinitionFND();

  ExtendedGUID dataSignatureGroup() const;
  void setDataSignatureGroup(const ExtendedGUID &DataSignatureGroup);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // DATASIGNATUREGROUPDEFINITIONFND_H
