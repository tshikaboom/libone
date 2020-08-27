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
#include <vector>
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

  uint32_t fileNodeCount = 0xFFFFFFFF;
  /* TODO: not sure how to satisfy the 'Transaction' requirement */
// TODO: set the Transaction's count to fileNodeCount, something like:
//
//  if (getFileNodeCountMapping().contains(m_fnd_list_id)) {
//   fileNodeCount = getFileNodeCountMapping()[m_fnd_list_id];
//   }
  do
  {
    FileNode node;
    node.parse(input);

    DBMSG << "input@" << input->tell() << ", node " << node.to_string() << std::endl;

    if (node.get_FileNodeID() != FndId::fnd_invalid_id)
    {
      if (node.get_FileNodeID() != FndId::ChunkTerminatorFND)
      {
        fileNodeCount--;
        m_fnd_list.push_back(node);
        DBMSG << "Added node to node list of size " << m_fnd_list.size() << std::endl;
      }
      else
      {
        DBMSG << "Returning because ChunkTerminatorFND" << std::endl;
        break;
      }
    }
    else
    {
      DBMSG << "Returning because padding found" << std::endl;
      break;
    }
  }
  while ((m_offset + m_size - input->tell() - 20 > 4) && (fileNodeCount > 0));
  // the footer structure is 20 bytes long (FileChunkReference (12bytes), and magic (8bytes)

  // skip padding and ChunkTerminatorFND
  input->seek(m_offset + m_size - 20, librevenge::RVNG_SEEK_SET);

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


std::string FileNodeListFragment::to_string()
{
  return std::string();
}

std::vector<FileNodeListFragment> parseFileNodeListFragments(const libone::RVNGInputStreamPtr_t &input, const FileChunkReference &ref)
{
  uint64_t originalLocation = input->tell();

  std::vector<FileNodeListFragment> fragments {};


  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
  FileNodeListFragment fragment(ref.get_location(), ref.get_size());

  fragment.parse(input);
  fragments.push_back(fragment);


  FileChunkReference nextFragmentRef = fragment.get_next_fragment();

  while (!nextFragmentRef.is_fcrNil() && !nextFragmentRef.is_fcrZero())
  {
    FileNodeListFragment nextFragment(nextFragmentRef.get_location(), nextFragmentRef.get_size());
    input->seek(nextFragmentRef.get_location(), librevenge::RVNG_SEEK_SET);
    fragment.parse(input);

    nextFragmentRef = nextFragment.get_next_fragment();
    fragments.push_back(fragment);
  }


  input->seek(originalLocation, librevenge::RVNG_SEEK_SET);
  return fragments;
}

}
