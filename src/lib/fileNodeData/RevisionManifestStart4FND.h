#ifndef REVISIONMANIFESTSTART4FND_H
#define REVISIONMANIFESTSTART4FND_H


#include "IFileNodeData.h"

#include "../ExtendedGUID.h"

namespace libone
{

class RevisionManifestStart4FND : public IFileNodeData
{
private:
  ExtendedGUID m_rid;
  ExtendedGUID m_ridDependent;

  uint64_t m_timeCreation;
  int32_t m_revisionRole;
  uint16_t m_odcsDefault;

public:
  RevisionManifestStart4FND();

  uint16_t getOdcsDefault() const;
  void setOdcsDefault(const uint16_t &value);

  int32_t getRevisionRole() const;
  void setRevisionRole(const int32_t &value);

  uint64_t getTimeCreation() const;
  void setTimeCreation(const uint64_t &value);

  ExtendedGUID getRidDependent() const;
  void setRidDependent(const ExtendedGUID &value);

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // REVISIONMANIFESTSTART4FND_H
