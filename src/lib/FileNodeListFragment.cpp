/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeListFragment.h"
#include "libone_utils.h"

#include "libone_types.h"

namespace libone
{

FileNodeListFragment::FileNodeListFragment(uint64_t location, uint64_t size) :
  m_offset(location),
  m_size(size),
  m_fnd_list_id(0),
  m_fragment_sequence(0),
  m_fnd_list(std::vector<FileNode>()),
  m_next_fragment_offset(0),
  m_next_fragment(FileChunkReference(FileChunkReferenceSize::Size64x32))
{
  m_next_fragment_offset = location + size - field_size_footer - field_size_next_fragment;
  DBMSG << "location " << m_offset << " size " << m_size << " field_size_footer " << field_size_footer << " field_size_next_fragment " << field_size_next_fragment << std::endl;
}

void FileNodeListFragment::parse(const libone::RVNGInputStreamPtr_t &input)
{
  uint64_t magic;
  DBMSG << "input@" << input->tell() << ", beginning" << std::endl;

  magic = readU64(input, false);
  if (magic != header_magic_id)
  {
    DBMSG << "Parsed magic " << magic << " does not match expected header magic" << header_magic_id << std::endl;
    assert(false);
  }


  m_fnd_list_id = readU32(input, false);
  m_fragment_sequence = readU32(input, false);

  FileNode node;

  do
  {
    node.parse(input);

    DBMSG << "input@" << input->tell() << ", node " << node.to_string() << std::endl;

    if (node.get_FileNodeID() != fnd_id::ChunkTerminatorFND)
    {
      m_fnd_list.push_back(node);
      DBMSG << "Added node to node list of size " << m_fnd_list.size() << std::endl;
    }

    node.skip_node(input);
    skip_padding(input);
  }
  while (!is_end_of_list(node, input->tell()));

  m_next_fragment.parse(input);

  DBMSG << "Parsed next fragment, got " << m_next_fragment.to_string() << std::endl;

  magic = readU64(input, false);
  if (magic != footer_magic_id)
  {
    DBMSG << "Parsed magic " << magic << " does not match expected footer magic" << footer_magic_id << std::endl;
    assert(false);
  }

  return;
}

void FileNodeListFragment::skip_padding(const libone::RVNGInputStreamPtr_t &input)
{
  int i;
  for (i=0;; i++)
  {
    if (readU8(input, false) != 0)
    {
      input->seek(- sizeof(uint8_t), librevenge::RVNG_SEEK_CUR);
      break;
    }
  }
  DBMSG << "Skipped " << i << " bytes" << std::endl;
}

/* TODO: not sure how to satisfy the 'Transaction' requirement */
bool FileNodeListFragment::is_end_of_list(FileNode current_node, long current_offset)
{
  if (current_node.get_FileNodeID() == fnd_id::ChunkTerminatorFND)
  {
    DBMSG << "Returning true because ChunkTerminatorFND" << std::endl;
    return true;
  }

  if (m_next_fragment_offset - current_offset < 4)
  {
    DBMSG << "Returning true because < 4 bytes" << std::endl;
    return true;
  }

  DBMSG << "Returning false (current_node " << fnd_id_to_string(current_node.get_FileNodeID())
        << ", current_offset@" << current_offset << ", next_fragment@" << m_next_fragment_offset
        << std::endl;
  return false;
}

std::string FileNodeListFragment::to_string()
{
  return std::string();
}
}


