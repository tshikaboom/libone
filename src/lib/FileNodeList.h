/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODELIST_H
#define INCLUDED_LIBONE_FILENODELIST_H

#include <librevenge-stream/librevenge-stream.h>

#include <vector>

#include "FileNode.h"

namespace libone {

class FileNodeList {
  public:
    FileNodeList() {}
//    FileNodeList(uint64_t new_location, uint64_t new_size);
    void parse(librevenge::RVNGInputStream *input, uint32_t ExpectedFileNodeID);
    void parse_header(librevenge::RVNGInputStream *input);
    void set_size(uint64_t new_size);
    std::string to_string();

  private:
    uint64_t uintMagic = 0;
    uint32_t FileNodeListID = 0;
    uint32_t nFragmentSequence = 0;
    std::vector<FileNode> rgFileNodes = std::vector<FileNode>();
    uint16_t nextFragment = 0;
    uint64_t footer = 0;
    uint64_t size = 0;

};


}

#endif
