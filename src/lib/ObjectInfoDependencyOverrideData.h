#ifndef OBJECTINFODEPENDENCYOVERRIDEDATA_H
#define OBJECTINFODEPENDENCYOVERRIDEDATA_H

#include <vector>

#include "ObjectInfoDependencyOverride32.h"
#include "ObjectInfoDependencyOverride8.h"

namespace libone
{

class ObjectInfoDependencyOverrideData
{
private:
  uint32_t m_c8BitOverrides;
  uint32_t m_c32BitOverrides;

  uint32_t m_crc;

  std::vector<ObjectInfoDependencyOverride8> m_Overrides1;
  std::vector<ObjectInfoDependencyOverride32> m_Overrides2;

public:
  ObjectInfoDependencyOverrideData();


  uint32_t c8BitOverrides() const;
  void setC8BitOverrides(const uint32_t &c8BitOverrides);

  uint32_t c32BitOverrides() const;
  void setC32BitOverrides(const uint32_t &c32BitOverrides);

  uint32_t crc() const;
  void setCrc(const uint32_t &crc);

  std::vector<ObjectInfoDependencyOverride8> Overrides1() const;
  void
  setOverrides1(const std::vector<ObjectInfoDependencyOverride8> &Overrides1);

  std::vector<ObjectInfoDependencyOverride32> Overrides2() const;
  void
  setOverrides2(const std::vector<ObjectInfoDependencyOverride32> &Overrides2);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input,
                                                        ObjectInfoDependencyOverrideData &obj);

  void parse(const libone::RVNGInputStreamPtr_t &input);

  std::string to_string() const;
};

} // namespace libone

#endif // OBJECTINFODEPENDENCYOVERRIDEDATA_H
