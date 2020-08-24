/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_EXTENDEDGUID_H
#define INCLUDED_LIBONE_EXTENDEDGUID_H

#include "GUID.h"


namespace libone
{
class ExtendedGUID
{
public:
  ExtendedGUID();

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ExtendedGUID &obj);
  void parse(const libone::RVNGInputStreamPtr_t &input);
  void zero();
  std::string to_string();
  uint32_t get_n();
  void set_GUID(GUID new_guid);
  void set_n(uint32_t new_n);
  bool is_equal(ExtendedGUID other);
  uint32_t n = 0;

private:
  GUID guid = GUID();
};

}

#endif
