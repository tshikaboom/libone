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

#include <librevenge-stream/librevenge-stream.h>

using namespace std;


namespace libone {

class FileChunkReference {
  public:
    enum mode {
      Type32x32,
      Type64x64,
      Type64x32,
      NIL } size_mode = NIL;

    void parse(librevenge::RVNGInputStream *input, enum FileChunkReference::mode size);
    void parse(librevenge::RVNGInputStream *input, int a, int c);
    string to_string();
    long get_location();
    long get_size();
    bool is_fcrNil();
    bool is_fcrZero();
    void set_zero();

  private:
    uint64_t stp = 0;
    uint64_t cb = 0;
};

}

#endif
