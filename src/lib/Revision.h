/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_REVISION_H
#define INCLUDED_LIBONE_REVISION_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include "ExtendedGUID.h"
#include "Object.h"
#include "ObjectSpace.h"

namespace libone {

class Revision {
  public:
    void list_parse(librevenge::RVNGInputStream *input, FileChunkReference64 ref);
    std::string get_guid();
    std::string to_string();

  private:
    ExtendedGUID guid = ExtendedGUID();
    ExtendedGUID dependent = ExtendedGUID();
    CompactID root_object = CompactID();
    bool read_only = false;
    unsigned int ref_count = 0;
    uint32_t role = 0;
    uint16_t odcsDefault = 0;
    ExtendedGUID context = ExtendedGUID();

};

}

#endif
