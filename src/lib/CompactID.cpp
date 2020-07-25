/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>
#include "CompactID.h"
#include "libone_utils.h"
#include "libone_types.h"

namespace libone
{

void CompactID::parse(librevenge::RVNGInputStream *input)
{
  uint32_t temp = readU32(input);
  guidIndex = (temp >> 8) & 0xFFFFFF;
  n = temp & 0xFF;
}

std::string CompactID::to_string()
{
  std::stringstream stream;
  stream << "CompactID " << guidIndex << " n " << (unsigned) n << '\n';
  return stream.str();
}

ExtendedGUID CompactID::to_EGUID()
{
  ExtendedGUID ret;
  ret.set_GUID(GlobalIdentificationTable[guidIndex]);
  ret.set_n(n);

  return ret;
}
}


