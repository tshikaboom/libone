/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_ROOTFILENODELIST_H
#define INCLUDED_LIBONE_ROOTFILENODELIST_H

#include <string>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>
#include "libone_types.h"

namespace libone {

class RootFileNodeList {

public:
    void parse(librevenge::RVNGInputStream *input);
};


}

#endif