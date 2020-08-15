/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>

#include "ExtendedGUID.h"

#include "libone_utils.h"

namespace libone
{

ExtendedGUID::ExtendedGUID() : guid(), n() {}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, ExtendedGUID &obj)
{
  obj.parse(input);
  return input;
}

void ExtendedGUID::parse(const libone::RVNGInputStreamPtr_t &input)
{
  guid.parse(input);

  n = readU32(input, false);
}

std::string ExtendedGUID::to_string()
{
  std::stringstream stream;
  stream << guid.to_string() << " n=" << n;

  return stream.str();
}

uint32_t ExtendedGUID::get_n()
{
  return n;
}

bool ExtendedGUID::is_equal(ExtendedGUID other)
{
  if ((guid.is_equal(other.guid)) && (n == other.n))
  {
    return true;
  }
  return false;
}

void ExtendedGUID::zero()
{
  guid.zero();
  n = 0;
}

void ExtendedGUID::set_n(uint32_t new_n)
{
  n = new_n;
}

void ExtendedGUID::set_GUID(GUID new_guid)
{
  guid = new_guid;
}

}
