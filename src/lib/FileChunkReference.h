/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILECHUNKREFERENCE_H
#define INCLUDED_LIBONE_FILECHUNKREFERENCE_H

#include "libone_utils.h"

using namespace std;


namespace libone {
/*
class FileChunkReference {
  public:
    FileChunkReference();
    virtual ~FileChunkReference() = 0;
    virtual void parse(librevenge::RVNGInputStream *input);
    virtual string to_string();
};
*/
class FileChunkReference32 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint32_t get_location();
    uint32_t get_size();
    string to_string();

  private:
    uint32_t stp = 0;
    uint32_t cb = 0;
};

class FileChunkReference64 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint64_t get_location();
    uint64_t get_size();
    string to_string();

  private:
    uint64_t stp = 0;
    uint64_t cb = 0;
};

class FileChunkReference64x32 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint64_t get_location();
    uint32_t get_size();
    string to_string();

  private:
    uint64_t stp = 0;
    uint32_t cb = 0;
};

}

#endif
