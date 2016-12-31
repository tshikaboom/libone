/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <iomanip>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>
#include "JCID.h"

namespace libone {

    std::string JCID::to_string() {
      std::stringstream stream;
      switch (get_value()) {
        case jcidPageNode:
          stream << "jcidPageNode";
          break;
        case jcidPageSeriesNode:
          stream << "jcidPageSeriesNode";
          break;
        case jcidSectionNode:
          stream << "jcidSectionNode";
          break;
        default:
          stream << std::hex << get_value() << " unknown";
          break;
      }
      return stream.str();
    }

}

