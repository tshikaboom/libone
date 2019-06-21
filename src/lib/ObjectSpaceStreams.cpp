/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <bitset>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

#include "ObjectSpaceStreams.h"
#include "CompactID.h"


using std::string;

namespace libone {

	void ObjectSpaceStream::parse_header(librevenge::RVNGInputStream *input) {
		uint32_t temp = readU32(input);
		std::bitset<32> x(temp);
    std::cout << "parsed " << x << '\n';
		b = temp >> 31;
		a = (temp >> 30) & 1;
		Count = temp & 0xFFFFFF;
	}

	std::string ObjectSpaceStream::header_string() {
	  std::stringstream stream;
	  stream << "header count "  << Count << " a " << a << " b " << b;

	  return stream.str();
	}

	uint16_t ObjectSpaceStream::get_A() {
	  return a;
	}

	uint16_t ObjectSpaceStream::get_B() {
	  return b;
	}

  std::vector<ExtendedGUID> ObjectSpaceStreamOfOIDs::parse(librevenge::RVNGInputStream *input) {
    std::vector<ExtendedGUID> ret = std::vector<ExtendedGUID>();
    parse_header(input);
    CompactID temp;
    std::cout << header_string() << "\n";
    for (uint32_t i=0; i < Count; i++) {
      temp.parse(input);
      if (!guid.is_equal(temp.to_EGUID())) {
        std::cout << "pushing " << temp.to_EGUID().to_string() << "\n";
        ret.push_back(temp.to_EGUID());
      } else {
        std::cout << "not pushing " << temp.to_EGUID().to_string() << " because equal to " << guid.to_string() << "\n";
      }
    }
    return ret;
  }

  std::vector<ExtendedGUID> ObjectSpaceStreamOfOSIDs::parse(librevenge::RVNGInputStream *input) {
    std::vector<ExtendedGUID> ret = std::vector<ExtendedGUID>();
    parse_header(input);
    CompactID temp;
      for (uint32_t i=0; i < Count; i++) {
        temp.parse(input);
        ret.push_back(temp.to_EGUID());
    }
    return ret;
  }

  std::vector<ExtendedGUID> ObjectSpaceStreamOfContextIDs::parse(librevenge::RVNGInputStream *input) {
    std::vector<ExtendedGUID> ret = std::vector<ExtendedGUID>();
    parse_header(input);
    CompactID temp;
    for (uint32_t i=0; i < Count; i++) {
      temp.parse(input);
      ret.push_back(temp.to_EGUID());
    }
    return ret;
  }
}
