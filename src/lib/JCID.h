/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_JCID_H
#define INCLUDED_LIBONE_JCID_H

#include <string>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>

namespace libone {

class JCID {
  public:
    JCID(uint32_t val) { value = val; }
    uint16_t index() { return (value & 0xFFFF); }
    uint16_t IsBinary() { return (value & 0x100000) >> 15; }
    uint16_t IsPropertySet() { return (value & 0x200000) >> 14; }
    uint16_t IsGraphNode() { return (value & 0x400000) >> 13; }
    uint16_t IsFileData() { return (value & 0x800000) >> 12; }
    uint16_t IsReadOnly() { return (value & 0x1000000) >> 11; }
    void set_IsReadOnly(bool val) { value |= (val << 11); }
    void set_IsFileData(bool val) { value |= (val << 12); }
    void set_IsGraphNode(bool val) { value |= (val << 13); }
    void set_IsPropertySet(bool val) { value |= (val << 14); }
    void set_IsBinary(bool val) { value |= (val << 15); }
    void set_index(uint16_t val) { value |= val; }
  private:
    uint32_t value = 0;
};

}

#endif
