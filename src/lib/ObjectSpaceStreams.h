/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_OBJECTSPACESTREAMS_H
#define INCLUDED_OBJECTSPACESTREAMS_H

#include <string>
#include <cstdint>
#include <vector>
#include <librevenge-stream/librevenge-stream.h>

#include "libone_utils.h"
#include "ExtendedGUID.h"

namespace libone {

class ObjectSpaceStream {
  public:

    void parse_header(librevenge::RVNGInputStream *input);
    std::string header_string();
    virtual ~ObjectSpaceStream() { };
    uint16_t get_A();
    uint16_t get_B();
    uint32_t get_Count();

    virtual std::vector<ExtendedGUID> parse(librevenge::RVNGInputStream *input) = 0;
  protected:
    uint32_t Count = 0;
    uint16_t a = 0;
    uint16_t b = 0;
};

class ObjectSpaceStreamOfOIDs: public ObjectSpaceStream {
  public:
    ObjectSpaceStreamOfOIDs(ExtendedGUID new_guid) { guid = new_guid; }
    std::vector<ExtendedGUID> parse(librevenge::RVNGInputStream *input);
  private:
    ExtendedGUID guid = ExtendedGUID();
};

class ObjectSpaceStreamOfOSIDs: public ObjectSpaceStream {
  public:
    std::vector<ExtendedGUID>  parse(librevenge::RVNGInputStream *input);
  private:
};

class ObjectSpaceStreamOfContextIDs: public ObjectSpaceStream {
  public:
    std::vector<ExtendedGUID>  parse(librevenge::RVNGInputStream *input);
  private:
};

}

#endif
