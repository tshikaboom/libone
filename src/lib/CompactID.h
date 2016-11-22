/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_COMPACTID_H
#define INCLUDED_LIBONE_COMPACTID_H

#include "libone_utils.h"

namespace libone {

class CompactID {
  public:
    void parse(librevenge::RVNGInputStream *input);

  private:
    uint8_t n;
    uint32_t guidIndex; // 24 bits used only

};

}

#endif
