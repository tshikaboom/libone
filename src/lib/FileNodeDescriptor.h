/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODEFND_H
#define INCLUDED_LIBONE_FILENODEFND_H

#include "libone_utils.h"




namespace libone {

class FileNodeDescriptor {
  public:
    void parse(librevenge::RVNGInputStream *input);
    string to_string();

  private:
    uint16_t FileNodeID = 0;
    uint16_t Size = 0;
    uint16_t ABCD = 0;
    uint32_t IDMask = 0xFFC00000;
    uint32_t SizeMask = 0x3FFE00;
    uint32_t ABCDMask = 0x1FF;
};


}

#endif
