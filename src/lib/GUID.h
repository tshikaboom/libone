/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_GUID_H
#define INCLUDED_LIBONE_GUID_H


namespace libone {
class GUID {
public:

    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();

  protected:
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint16_t Data4[4];
};


}

#endif
