/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODE_H
#define INCLUDED_LIBONE_FILENODE_H

#include "libone_utils.h"




namespace libone {

class FileNode {
  public:
    void parse(librevenge::RVNGInputStream *input);
    string to_string();
    uint16_t get_FileNodeID();
    uint16_t get_Size();
    uint16_t get_A();
    uint16_t get_B();
    uint16_t get_C();
    uint16_t get_D();

  private:
    uint16_t FileNodeID = 0;
    uint16_t Size = 0;
    uint32_t ABCD = 0;
    uint32_t IDMask = 0xFFC00000;
    uint32_t SizeMask = 0x3FFE00;
    uint32_t ABCDMask = 0x1FF;
};


}

#endif
