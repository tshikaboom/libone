/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeList.h"
#include "libone_utils.h"

#include "libone_types.h"

namespace libone
{

FileNodeList::FileNodeList(uint64_t new_location, uint64_t new_size) :
  m_offset(new_location),
  m_fnd_list_id(0),
  m_fragment_sequence(0),
  m_size(new_size),
  m_fragment_list(std::vector<FileNodeListFragment>())
{}

void FileNodeList::parse(librevenge::RVNGInputStream *input)
{
  input->seek(m_offset, librevenge::RVNG_SEEK_SET);

  FileNodeListFragment fragment = FileNodeListFragment(m_offset, m_size);

  do
  {
    DBMSG << "FileNodeList, going to parse a FileNodeListFragment" << std::endl;
    fragment.parse(input);

    m_fragment_list.push_back(fragment);

    DBMSG << "inserted fragment in list, now size " << m_fragment_list.size() << std::endl;

    rgFileNodes.insert(std::end(rgFileNodes), std::begin(fragment.get_file_nodes()), std::end(fragment.get_file_nodes()));

    if (fragment.get_next_fragment().is_fcrNil())
    {
      break;
    }
    else
    {
      input->seek(fragment.get_next_fragment().get_location(), librevenge::RVNG_SEEK_SET);
    }
  }
  while (!fragment.get_next_fragment().is_fcrNil());

  DBMSG << m_fragment_list.size() << " fragment(s) parsed, "
        << rgFileNodes.size() << " nodes parsed" << std::endl;

}

std::string FileNodeList::to_string()
{
  std::stringstream stream;
  stream << std::dec << "m_fnd_list_id " << m_fnd_list_id << '\n';
  stream << "nFragmentSequence " << m_fragment_sequence << '\n';
  for (FileNode i: rgFileNodes)
    stream << i.to_string() << '\n';
  return stream.str();
}
}


