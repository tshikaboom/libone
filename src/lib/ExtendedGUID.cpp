/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

using std::string;

namespace libone {

	void ExtendedGUID::parse(librevenge::RVNGInputStream *input) {
		guid.parse(input);

		n = readU32(input, false);
	}

	string ExtendedGUID::to_string() {
		std::stringstream stream;
		stream << guid.to_string() << " n=" << n;

		return stream.str();
	}

	uint32_t ExtendedGUID::get_n() {
		return n;
	}

}
