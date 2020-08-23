#ifndef GLOBALIDTABLEENTRYFNDX_H
#define GLOBALIDTABLEENTRYFNDX_H

#include "../GUID.h"
#include "IFileNodeData.h"

namespace libone
{

class GlobalIdTableEntryFNDX : public IFileNodeData
{
private:
  uint32_t m_index;

  GUID m_guid;
public:
  GlobalIdTableEntryFNDX();

  uint32_t getIndex() const;
  void setIndex(const uint32_t &value);

  GUID getGuid() const;
  void setGuid(const GUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

};
} //namespace libone

#endif // GLOBALIDTABLEENTRYFNDX_H
