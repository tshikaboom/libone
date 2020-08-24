#ifndef OBJECTINFODEPENDENCYOVERRIDESFND_H
#define OBJECTINFODEPENDENCYOVERRIDESFND_H

#include "IFileNodeData.h"
#include "../FileNodeChunkReference.h"
#include "../ObjectInfoDependencyOverrideData.h"

namespace libone
{

class ObjectInfoDependencyOverridesFND : public IFileNodeData
{
private:
  FileNodeChunkReference m_ref;

  ObjectInfoDependencyOverrideData m_data;

public:
  ObjectInfoDependencyOverridesFND(StpFormat stpFormat, CbFormat cbFormat);
  ~ObjectInfoDependencyOverridesFND();

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  ObjectInfoDependencyOverrideData getData() const;
  void setData(const ObjectInfoDependencyOverrideData &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // OBJECTINFODEPENDENCYOVERRIDESFND_H
