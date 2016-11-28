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

#include "FileChunkReference.h"
#include <librevenge-stream/librevenge-stream.h>




namespace libone {

class FileNode {
  public:
    void parse(librevenge::RVNGInputStream *input);
		void try_parse_ref(librevenge::RVNGInputStream *input, uint32_t ExpectedFileNodeID);
    std::string to_string();
    uint32_t get_FileNodeID();
    uint32_t get_Size();
    uint32_t get_A();
    uint32_t get_B();
    uint32_t get_C();
    uint32_t get_D();
    bool isEnd();

  private:
    uint32_t FileNodeID = 0;
    uint32_t Size = 0;
    uint16_t a = 0, b = 0, c = 0, d = 0;
    uint32_t const IDMask = 0xFFC00000;
    uint32_t const SizeMask = 0x3FFE00;
    uint32_t const ABCDMask = 0x1FF;
    bool is_end = false;
		FileChunkReference64 ref = FileChunkReference64();
};


}

#endif
