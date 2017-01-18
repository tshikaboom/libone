/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "libone_utils.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>
#include "PropertySet.h"

namespace libone {

    void PropertySet::parse(librevenge::RVNGInputStream *input) {
      bool unknown = false;
      count = readU16(input);
      uint32_t temp = 0;
      for (int i=0; i < count; i++) {
        temp = readU32 (input);
        prop_ids.push_back(PropertyID(temp));
      }
      for (int i=0; i < count; i++) {
        switch (prop_ids[i].get_value()) {
          case PropertyID::CachedTitleString:
          default:
          unknown = true;
            break;
        }
        if (unknown) {
          std::cout << "unknown property id " << prop_ids[i].to_string() << " bailing out! position " << input->tell() << endl;
          break;
      }
    }
    }


    std::string PropertySet::to_string() {
      std::stringstream stream;
      if (prop_ids.size()) {
        stream << "property count " << prop_ids.size() << "\n";
        for (auto j: prop_ids)
          stream << j.to_string() << "\n";
      }
      return stream.str();
  }
}
