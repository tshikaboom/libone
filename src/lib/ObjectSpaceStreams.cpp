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

  void ObjectSpaceStreamOfOIDs::parse(librevenge::RVNGInputStream *input) {
    parse_header(input);
    CompactID temp;
    std::cout << header_string() << "\n";
    for (uint32_t i=0; i < Count; i++) {
      temp.parse(input);
      object_ids.push_back(temp.to_EGUID());
    }
  }

  std::string ObjectSpaceStreamOfOIDs::to_string() {
    std::stringstream stream;
    for (uint32_t i=0; i < Count; i++) {
      stream << "object guid " << object_ids[i].to_string();
    }
    return stream.str();
  }

  void ObjectSpaceStreamOfOSIDs::parse(librevenge::RVNGInputStream *input) {
    parse_header(input);
    CompactID temp;
      for (uint32_t i=0; i < Count; i++) {
        temp.parse(input);
        space_ids.push_back(temp.to_EGUID());
    }
  }

  std::string ObjectSpaceStreamOfOSIDs::to_string() {
    std::stringstream stream;
    for (uint32_t i=0; i < Count; i++) {
      stream << "objectspace guid " << space_ids[i].to_string();
    }
    return stream.str();
  }

  void ObjectSpaceStreamOfContextIDs::parse(librevenge::RVNGInputStream *input) {
    parse_header(input);
    CompactID temp;
    for (uint32_t i=0; i < Count; i++) {
      temp.parse(input);
      context_ids.push_back(temp.to_EGUID());
    }
  }

  std::string ObjectSpaceStreamOfContextIDs::to_string() {
    std::stringstream stream;
    for (uint32_t i=0; i < Count; i++) {
      stream << "context guid " << context_ids[i].to_string();
    }
    return stream.str();
  }



}
