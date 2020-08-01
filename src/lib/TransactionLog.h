/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_TRANSACTIONLOG_H
#define INCLUDED_LIBONE_TRANSACTIONLOG_H

#include "TransactionLogFragment.h"
#include "TransactionEntry.h"

namespace libone
{

class TransactionLog
{
public:
  TransactionLog(uint64_t location, uint64_t size, uint32_t max_transactions);
  void parse(librevenge::RVNGInputStream *input);
  std::string to_string();
  uint32_t get_srcID();
  uint32_t get_Switch();

private:
  uint64_t m_offset;
  uint64_t m_size;
  uint64_t m_total_transactions;
  std::vector<TransactionLogFragment> m_fragments;
  std::vector<TransactionEntry> m_transactions;

};

}

#endif
