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
#include <vector>

#include "FileChunkReference.h"
#include "TransactionEntry.h"

namespace libone {

class TransactionLogFragment {
  public:
    TransactionLogFragment(uint32_t expected_transactions);
    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();

  private:
    uint32_t transactions_parsed = 0;
    uint32_t total_transactions = 0;
    std::vector<TransactionEntry> sizeTable = std::vector<TransactionEntry>();
    TransactionEntry get_next_entry(librevenge::RVNGInputStream *input);
    FileChunkReference nextFragment = FileChunkReference();
    bool end = false;

};

}

#endif
