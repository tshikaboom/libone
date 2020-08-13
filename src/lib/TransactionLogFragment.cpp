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
#include <bitset>
#include <libone/libone.h>
#include "libone_utils.h"
#include <sstream>

#include "TransactionLog.h"
#include "TransactionLogFragment.h"

namespace libone
{

TransactionLogFragment::TransactionLogFragment() :
  m_offset(0), m_size(0), m_transactions_to_parse(0),
  m_transactions(std::vector<TransactionEntry>()),
  m_next_fragment(FileChunkReference(FileChunkReferenceSize::Size64x32))
{}


int TransactionLogFragment::parse(const libone::RVNGInputStreamPtr_t &input,
                                  uint64_t location, uint32_t size,
                                  uint32_t transactions_to_parse)
{
  m_offset = location;
  m_size = size;
  m_transactions_to_parse = transactions_to_parse;

  DBMSG << "Trying to parse " << m_transactions_to_parse << " transactions" << std::endl;

  for (uint32_t i=0; i < m_transactions_to_parse; i++)
  {
    TransactionEntry entry = TransactionEntry();
    entry.parse(input);

    DBMSG << "Parsed entry " << entry.to_string() << std::endl;
    m_transactions.push_back(entry);
  }
  m_next_fragment.parse(input);

  DBMSG << "Parsed chunk referece pointing to " << m_next_fragment.get_location() << std::endl;

  return m_transactions.size();
}

std::string TransactionLogFragment::to_string()
{
  std::stringstream stream;
//      stream << "TransactionLog srcID " << srcID << " Switch " << TransactionLogSwitch;

  return stream.str();
}

}
