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
#include "FileNodeList.h"
#include "GUID.h"

namespace libone {

class Object {
  public:
    void parse(librevenge::RVNGInputStream *input);
    bool get_read_only();
    void set_read_only(bool new_);
    std::string get_guid();

  private:
    bool read_only = false;
    unsigned int ref_count = 0;
    GUID guid;

};

}

#endif
