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
#include "FileNodeListFragment.h"

namespace libone {

class FileNodeList {
  public:
    FileNodeList(uint64_t new_location, uint64_t new_size);
    void parse(librevenge::RVNGInputStream *input);
    bool is_end();
    std::string to_string();


    std::vector<FileNode> get_fnd_list();
  private:
    long m_offset;
    uint32_t m_fnd_list_id;
    uint32_t m_fragment_sequence;
    std::vector<FileNode> rgFileNodes = std::vector<FileNode>();
    uint16_t nextFragment = 0;
    uint64_t footer = 0;
    uint64_t m_size;
    long old_seek = 0;
    long seek = 0;
    bool end = false;
    bool header_parsed = false;
    long next_fragment_location = 0;
    uint32_t list_length = 0;
    uint32_t elements_parsed = 0;

    std::vector<FileNodeListFragment> m_fragment_list;

    const uint64_t header_magic_id = 0xA4567AB1F5F7F4C4;
    const uint64_t footer_magic_id = 0x8BC215C38233BA4B;
};


}

#endif
