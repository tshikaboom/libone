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
    FileNodeList(uint64_t, uint64_t);
    FileNode get_next_node(librevenge::RVNGInputStream *input);
    bool is_end();
    std::string to_string();

  private:
    void parse_header(librevenge::RVNGInputStream *input);
    uint64_t uintMagic = 0;
    uint32_t FileNodeListID = 0;
    uint32_t nFragmentSequence = 0;
    std::vector<FileNode> rgFileNodes = std::vector<FileNode>();
    uint16_t nextFragment = 0;
    uint64_t footer = 0;
    uint64_t location = 0;
    uint64_t size = 0;
    long old_seek = 0;
    long seek = 0;
    bool end = false;
    bool header_parsed = false;
    long next_fragment_location = 0;

};


}

#endif
