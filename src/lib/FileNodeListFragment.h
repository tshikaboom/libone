/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODELISTFRAGMENT_H
#define INCLUDED_LIBONE_FILENODELISTFRAGMENT_H

#include <librevenge-stream/librevenge-stream.h>

#include <vector>

#include "FileChunkReference.h"
#include "FileNode.h"

namespace libone
{

class FileNodeListFragment
{
public:
  FileNodeListFragment(uint64_t location, uint64_t size);
  void parse(librevenge::RVNGInputStream *input);
  std::string to_string();
  uint32_t get_list_id()
  {
    return m_fnd_list_id;
  }
  uint32_t get_fragment_sequence()
  {
    return m_fragment_sequence;
  }
  std::vector<FileNode> &get_file_nodes()
  {
    return m_fnd_list;
  }
  FileChunkReference get_next_fragment()
  {
    return m_next_fragment;
  }

private:
  // Location and size
  uint64_t m_offset;
  uint64_t m_size;

  // Header
  uint32_t m_fnd_list_id;
  uint32_t m_fragment_sequence;

  // File node list
  std::vector<FileNode> m_fnd_list;

  // Next fragment's location
  uint64_t m_next_fragment_offset;
  FileChunkReference m_next_fragment;

  bool is_end_of_list(FileNode current_node, long current_offset);
  void skip_padding(librevenge::RVNGInputStream *input);

  const uint64_t header_magic_id = 0xA4567AB1F5F7F4C4;
  const uint64_t footer_magic_id = 0x8BC215C38233BA4B;
  const size_t field_size_next_fragment = 12;
  const size_t field_size_footer = sizeof(footer_magic_id);
};


}

#endif
