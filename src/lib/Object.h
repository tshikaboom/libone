/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_OBJECT_H
#define INCLUDED_LIBONE_OBJECT_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>

#include "ExtendedGUID.h"
#include "FileNodeList.h"
#include "GUID.h"

namespace libone {

class Object {
  public:
    void parse(librevenge::RVNGInputStream *input, FileChunkReference ref);
    bool get_read_only();
    void set_read_only(bool new_);
    ExtendedGUID get_guid();
    std::string to_string();

  private:
    bool read_only = false;
    unsigned int ref_count = 0;
    ExtendedGUID guid = ExtendedGUID();
    uint32_t jcid = 0;
    uint16_t fHasOidReferences = 0;
    uint16_t fHasOsidReferences = 0;

};

}

#endif
