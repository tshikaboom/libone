#ifndef GLOBALIDTABLEENTRY2FNDX_H
#define GLOBALIDTABLEENTRY2FNDX_H

#include "IFileNodeData.h"

namespace libone
{

class GlobalIdTableEntry2FNDX : public IFileNodeData
{
private:
  uint32_t m_iIndexMapFrom;

  uint32_t m_iIndexMapTo;
public:
  GlobalIdTableEntry2FNDX();



  uint32_t getIIndexMapTo() const;
  void setIIndexMapTo(const uint32_t &value);

  uint32_t getIIndexMapFrom() const;
  void setIIndexMapFrom(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // GLOBALIDTABLEENTRY2FNDX_H
