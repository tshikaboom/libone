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
    std::stringstream stream;
    length = readU32(input);
    std::vector<char> string;
    char *buf = (char *) readNBytes(input, length*2);
    string.assign(buf, buf+length*2);
    ustring = librevenge::RVNGString((char *) &string[0]);

    std::cout << "read length1 " << length << " length2 " << ustring.len() << " string1 " << &string[0] << " string2 " << ustring.cstr() << " end\n";
  }

  std::string StringInStorageBuffer::to_string() {
    return ustring.cstr();
  }


}

