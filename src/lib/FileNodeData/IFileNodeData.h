#ifndef IFILENODEDATA_H
#define IFILENODEDATA_H

#include <string>
#include <sstream>

#include "../libone_utils.h"

namespace libone
{
class IFileNodeData
{
protected:
  IFileNodeData();

public:
  virtual ~IFileNodeData();

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, IFileNodeData &obj);
  friend std::stringstream &operator<<(std::stringstream &input, IFileNodeData &obj);

  virtual void parse(const libone::RVNGInputStreamPtr_t &input) = 0;

  virtual std::string to_string() const = 0;

};

} // namespace libone

#endif // IFILENODEDATA_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
