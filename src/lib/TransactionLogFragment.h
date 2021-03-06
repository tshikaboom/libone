/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_TRANSACTIONLOGFRAGMENT_H
#define INCLUDED_LIBONE_TRANSACTIONLOGFRAGMENT_H

#include "FileChunkReference.h"
#include "TransactionEntry.h"

namespace libone
{

class TransactionLogFragment
{
public:
  TransactionLogFragment();
  /// \todo use FileChunkReference in parse
  int parse(const libone::RVNGInputStreamPtr_t &input,
            uint64_t location, uint32_t size,
            uint32_t transactions_to_parse);
  std::string to_string();
  std::vector<TransactionEntry> &get_transactions()
  {
    return m_transactions;
  }
  FileChunkReference get_next_fragment()
  {
    return m_next_fragment;
  }

private:
  uint64_t m_offset;
  uint32_t m_size;
  uint32_t m_transactions_to_parse;

  std::vector<TransactionEntry> m_transactions;
  FileChunkReference m_next_fragment;
};

}

#endif
