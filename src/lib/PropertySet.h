/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_PROPERTYSET_H
#define INCLUDED_PROPERTYSET_H

#include <string>
#include <cstdint>
#include <vector>
#include <librevenge-stream/librevenge-stream.h>
#include "PropertyID.h"

namespace libone
{

class PropertySet
{
public:
  void parse(const libone::RVNGInputStreamPtr_t &input);
  std::string to_string();
private:
  uint16_t count = 0;
  std::vector<PropertyID> prop_ids = std::vector<PropertyID>();
};

}

#endif
