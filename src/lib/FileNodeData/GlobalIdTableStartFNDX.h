#ifndef GLOBALIDTABLESTARTFNDX_H
#define GLOBALIDTABLESTARTFNDX_H

#include "IFileNodeData.h"

namespace libone
{

class GlobalIdTableStartFNDX : public IFileNodeData
{
private:
  uint8_t m_reserved;
public:
  GlobalIdTableStartFNDX();

  uint8_t getReserved() const;
  void setReserved(const uint8_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone
#endif // GLOBALIDTABLESTARTFNDX_H
