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

namespace libone
{

TransactionLog::TransactionLog(uint64_t location, uint32_t size, uint32_t max_transactions) :
  m_offset(location), m_size(size), m_total_transactions(max_transactions),
  m_fragments(std::vector<TransactionLogFragment>()),
  m_transactions(std::vector<TransactionEntry>())
{
  DBMSG << m_total_transactions << " transactions to parse" << std::endl;
}


void TransactionLog::parse(librevenge::RVNGInputStream *input)
{
  TransactionLogFragment fragment = TransactionLogFragment();
  uint64_t location = m_offset;
  uint32_t transactions_parsed = 0;

  DBMSG << "begin, input@" << input->tell() << std::endl;

  for (uint32_t i=0; i<m_total_transactions;)
  {
    DBMSG << "seeking to fragment @" << location << std::endl;
    input->seek(location, librevenge::RVNG_SEEK_SET);
    i += fragment.parse(input, m_offset, m_size, m_total_transactions-i);
    transactions_parsed += i;

    DBMSG << "Parsed one fragment, got " << i << " transactions" << std::endl;

    m_fragments.push_back(fragment);

    DBMSG << "pushed back fragment" << std::endl;

    m_transactions.insert(std::end(m_transactions), std::begin(fragment.get_transactions()), std::end(fragment.get_transactions()));

    DBMSG << "inserted fragment transactions" << std::endl;

    location = fragment.get_next_fragment().get_location();
  }

  DBMSG << "parsed " << transactions_parsed << " transactions" << std::endl;
}

std::string TransactionLog::to_string()
{
  std::stringstream stream;

  return stream.str();

}
}