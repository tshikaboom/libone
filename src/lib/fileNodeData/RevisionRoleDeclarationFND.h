#ifndef REVISIONROLEDECLARATIONFND_H
#define REVISIONROLEDECLARATIONFND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"

namespace libone
{

class RevisionRoleDeclarationFND : public IFileNodeData
{
private:
  ExtendedGUID m_rid;
  uint32_t m_RevisionRole;

public:
  RevisionRoleDeclarationFND();

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID &value);

  uint32_t getRevisionRole() const;
  void setRevisionRole(const uint32_t &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;
};

} // namespace libone

#endif // REVISIONROLEDECLARATIONFND_H
