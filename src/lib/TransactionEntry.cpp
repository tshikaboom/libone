/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "libone_utils.h"
#include <sstream>

#include "TransactionEntry.h"

namespace libone
{

TransactionEntry::TransactionEntry() :
  m_offset(0),
  m_fnd_list_changes(std::vector<struct fnd_list_change>()),
  m_crc(0)
{}

void TransactionEntry::parse(librevenge::RVNGInputStream *input)
{
  m_offset = input->tell();
  while (true)
  {
    struct fnd_list_change element =
    {
      readU32(input),
      readU32(input)
    };

    if (element.fnd_list_id == val_sentinel)
    {
      m_crc = element.nodes_changed;
      break;
    }
    else
    {
      m_fnd_list_changes.push_back(element);
    }
  }
}

std::string TransactionEntry::to_string()
{
  std::stringstream stream;

  for (struct fnd_list_change &iter : m_fnd_list_changes)
  {
    stream << "fnd_list " << iter.fnd_list_id;
    stream << "; " << iter.nodes_changed << " changes; ";
  }

  stream << "crc " << m_crc;

  return stream.str();
}

}
