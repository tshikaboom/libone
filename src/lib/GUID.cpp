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
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

#include "GUID.h"

namespace libone {

  void GUID::zero() {
    Data1 = 0;
    Data2 = 0;
    Data3 = 0;
    for (int i=0; i < 4; i++)
      Data4[i] = 0;
  }

	void GUID::parse(librevenge::RVNGInputStream *input) {
		  Data1 = readU32 (input, false);
		  Data2 = readU16 (input, false);
		  Data3 = readU16 (input, false);
		  for (int i=0; i<4; i++)
		    Data4[i] = readU16 (input, true);
	}

	std::string GUID::to_string() {
		std::stringstream stream;
		stream << "{" << std::hex << Data1 << "-" << Data2 << "-" << Data3 << "-" << Data4[0] << "-";

		for (int i=1; i<4; i++)
			stream << std::hex << Data4[i];

		stream << "}";
		return stream.str();
	}

	bool GUID::is_equal(GUID other) {
	  if ((Data1 == other.Data1) &&
	      (Data2 == other.Data2) &&
	      (Data3 == other.Data3)) {
	      for (int i=0; i<4; i++) {
	        if (Data4[i] != other.Data4[i])
	          return false;
	        }
	        return true;
	      }
	  return false;
	}

  // This is used for FileDataStores. The GUID is given as a string in the file
	void GUID::from_string(std::string str) {
    ONE_DEBUG_MSG(("\n"));

    Data1 = strtol(str.substr(0, 8).c_str(), NULL, 16);
    Data2 = strtol(str.substr(9, 4).c_str(), NULL, 16);
    Data3 = strtol(str.substr(14, 4).c_str(), NULL, 16);
    Data4[0] = strtol(str.substr(19, 4).c_str(), NULL, 16);
    Data4[1] = strtol(str.substr(24, 4).c_str(), NULL, 16);
    Data4[2] = strtol(str.substr(28, 4).c_str(), NULL, 16);
    Data4[3] = strtol(str.substr(32, 4).c_str(), NULL, 16);

	  ONE_DEBUG_MSG((" from string, dat good?\n"));

	  (void) str;
	}
}
