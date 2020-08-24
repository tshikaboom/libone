/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_COMPACTID_H
#define INCLUDED_LIBONE_COMPACTID_H
#include "ExtendedGUID.h"
#include <librevenge-stream/librevenge-stream.h>

namespace libone
{

class CompactID
{
public:
  void parse(const libone::RVNGInputStreamPtr_t &input);
  std::string to_string();
  ExtendedGUID to_EGUID();

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, CompactID &obj);

private:
  uint16_t n = 0;
  uint32_t guidIndex = 0; // 24 bits used only

};

}

#endif
