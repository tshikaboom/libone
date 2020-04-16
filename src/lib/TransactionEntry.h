/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_TRANSACTIONENTRY_H
#define INCLUDED_LIBONE_TRANSACTIONENTRY_H

#include <cstring>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <libone/libone.h>

namespace libone {

  struct fnd_list_change {
    uint32_t fnd_list_id;
    uint32_t nodes_changed;
  };

class TransactionEntry {
  public:
    TransactionEntry();
    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();
    std::vector<struct fnd_list_change> get_changes() { return m_fnd_list_changes; }

  private:
    long m_offset;
    std::vector<struct fnd_list_change> m_fnd_list_changes;
    uint32_t m_crc;

    static const uint32_t val_sentinel = 0x00000001;
};

}

#endif
