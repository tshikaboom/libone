/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_GUID_H
#define INCLUDED_LIBONE_GUID_H

#include <string>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>

namespace libone {
class GUID {
public:

    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();
    bool is_equal(GUID other);
    uint32_t Data1 = 0;
    uint16_t Data2 = 0;
    uint16_t Data3 = 0;
    uint16_t Data4[4] = { 0 };
    void zero();
};


}

#endif
