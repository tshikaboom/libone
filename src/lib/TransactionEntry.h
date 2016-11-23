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

#include "libone_utils.h"

namespace libone {

class TransactionEntry {
  public:
    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();
    uint32_t get_srcID();

  private:
    uint32_t srcID;
    uint32_t TransactionEntrySwitch;

};

}

#endif
