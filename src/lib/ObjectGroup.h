/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_OBJECTGROUP_H
#define INCLUDED_LIBONE_OBJECTGROUP_H

#include <iostream>
#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include <unordered_map>

#include "Object.h"

namespace libone {

class ObjectGroup {
  public:
    std::unordered_map<std::string, libone::Object> list_parse(librevenge::RVNGInputStream *input, FileChunkReference ref);
    std::string get_guid();

  private:
    ExtendedGUID oid = ExtendedGUID();

};

}

#endif
