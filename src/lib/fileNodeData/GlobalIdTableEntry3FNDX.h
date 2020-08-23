#ifndef GLOBALIDTABLEENTRY3FNDX_H
#define GLOBALIDTABLEENTRY3FNDX_H

#include "IFileNodeData.h"

namespace libone
{

class GlobalIdTableEntry3FNDX : public IFileNodeData
{
private:
  uint32_t m_iIndexCopyFromStart;
  uint32_t m_cEntriesToCopy;
  uint32_t m_iIndexCopyToStart;

public:
  GlobalIdTableEntry3FNDX();



  uint32_t getIIndexCopyFromStart() const;
  void setIIndexCopyFromStart(const uint32_t &value);
  uint32_t getCEntriesToCopy() const;
  void setCEntriesToCopy(const uint32_t &value);
  uint32_t getIIndexCopyToStart() const;
  void setIIndexCopyToStart(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};

} // namespace libone

#endif // GLOBALIDTABLEENTRY3FNDX_H
