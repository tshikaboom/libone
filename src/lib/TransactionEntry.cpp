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

#include "TransactionEntry.h"

namespace libone {

    void TransactionEntry::parse(librevenge::RVNGInputStream *input) {
    	srcID = readU32(input);
    	TransactionEntrySwitch = readU32(input);
    }

    std::string TransactionEntry::to_string() {
		std::stringstream stream;
		stream << "TransactionEntry srcID " << srcID << " Switch " << TransactionEntrySwitch;

		return stream.str();

	}

	uint32_t TransactionEntry::get_srcID() {
	  return srcID;
	}

	uint32_t TransactionEntry::get_Switch() {
	  return TransactionEntrySwitch;
	}

}
