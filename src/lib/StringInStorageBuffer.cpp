/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include <unordered_map>
#include <iostream>
#include <iostream>
#include <iomanip>
#include "StringInStorageBuffer.h"
#include "libone_utils.h"

namespace libone {

  void StringInStorageBuffer::parse(librevenge::RVNGInputStream *input) {
    char16_t temp;
    std::stringstream stream;
    uint32_t i;
    length = readU32(input);
    std::cout << "reading ";
    for (i=0; i<length; i++) {
      temp = tolower(readU16(input));
      chars += temp;
      std::cout << (char) temp;
    }
    std::cout << "\n";
    std::cout << "read " << length << " chars?\n";

  }

  std::string StringInStorageBuffer::to_string() {
    return chars;
  }


}

