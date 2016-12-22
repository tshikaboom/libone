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


#include "TransactionEntry.h"

namespace libone {

class TransactionLogFragment {
  public:
    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();

  private:
    std::vector<TransactionEntry> sizeTable = std::vector<TransactionEntry>();
    FileChunkReference nextFragment = FileChunkReference();

};

}

#endif
