#ifndef REVISIONROLEANDCONTEXTDECLARATIONFND_H
#define REVISIONROLEANDCONTEXTDECLARATIONFND_H

#include "../ExtendedGUID.h"
#include "IFileNodeData.h"
#include "RevisionRoleDeclarationFND.h"

namespace libone
{

class RevisionRoleAndContextDeclarationFND : public IFileNodeData
{
private:
  RevisionRoleDeclarationFND m_base;

  ExtendedGUID m_gctxid;

public:
  RevisionRoleAndContextDeclarationFND();

  RevisionRoleDeclarationFND getBase() const;
  void setBase(const RevisionRoleDeclarationFND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

  void parse(const libone::RVNGInputStreamPtr_t &input) override;

  std::string to_string() const override;

  IFileNodeData *clone() const override
  {
    return new RevisionRoleAndContextDeclarationFND(*this);
  }
};

} // namespace libone

#endif // REVISIONROLEANDCONTEXTDECLARATIONFND_H
