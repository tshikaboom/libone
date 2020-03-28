/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <vector>
#include <sstream>
#include <iostream>
#include "libone_utils.h"

#include "libone_types.h"

#include "TransactionLogFragment.h"

namespace libone {

    TransactionLogFragment::TransactionLogFragment(uint32_t expected_transactions) {
      total_transactions = expected_transactions;
    }

    void TransactionLogFragment::parse(librevenge::RVNGInputStream *input) {
      TransactionEntry entry;
      entry.parse(input);
      while (transactions_parsed < total_transactions) {
        entry.parse(input);
//        ONE_DEBUG_MSG(("%s\n", entry.to_string()));
        if (entry.get_srcID() != 0x00000001) {
          sizeTable.push_back(entry);
          Transactions.insert(std::make_pair(entry.get_srcID(), entry.get_Switch()));
        }
        else {
          transactions_parsed++;
          ONE_DEBUG_MSG(("parsed %d transactions\n", transactions_parsed));
        }
      }
//      ONE_DEBUG_MSG << "position " << input->tell() << " before next fragment\n";
      nextFragment.parse(input, FileChunkReference::mode::Type64x32);
      ONE_DEBUG_MSG(("%s position %ld\n", nextFragment.to_string().c_str(), input->tell()));
//      ONE_DEBUG_MSG << "last entry " << entry.to_string () << "\n";
      ONE_DEBUG_MSG(("parsed %d, total %d\n", transactions_parsed, total_transactions));
    }

    std::string TransactionLogFragment::to_string() {
    std::stringstream stream;

    stream << "TransactionLog" << '\n';
      for (auto i : Transactions) {
        stream << "FileNodeList " << i.first << " length " << i.second << '\n';
      }

    return stream.str();
    }

    TransactionEntry TransactionLogFragment::get_next_entry(librevenge::RVNGInputStream *input) {
      TransactionEntry entry;
      entry.parse(input);

      if (entry.get_srcID() == 0x00000001) {
        if (transactions_parsed < total_transactions)
          skip (input, 4);


      }
      return entry;
    }
}
