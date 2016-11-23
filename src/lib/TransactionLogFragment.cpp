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

#include "libone_utils.h"


namespace libone {

    void TransactionLogFragment::parse(librevenge::RVNGInputStream *input) {
      TransactionEntry entry;
      entry.parse(input);
      while (entry.get_srcID() != 0x00000001) {
        sizeTable.push_back(entry);
        entry.parse(input);
      }
    	(void) input;
    }

    std::string TransactionLogFragment::to_string() {
    std::stringstream stream;

    stream << "TransactionLog" << '\n';
      for (TransactionEntry i : sizeTable) {
        stream << i.to_string() << '\n';
      }

    return stream.str();
    }
}

