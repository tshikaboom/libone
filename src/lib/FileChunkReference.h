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
    virtual ~FileChunkReference() {}
    virtual void parse(librevenge::RVNGInputStream *input) = 0;
    virtual string to_string() = 0;
};

class FileChunkReference32: public FileChunkReference {
  public:
    void parse(librevenge::RVNGInputStream *input);
    string to_string();
    uint32_t get_location();
    uint32_t get_size();
    void location8();
    void set_all(uint32_t location, uint32_t size);

  private:
    uint32_t stp = 0;
    uint32_t cb = 0;
};

class FileChunkReference64: public FileChunkReference {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint64_t get_location();
    uint64_t get_size();
    string to_string();
    void set_all(uint64_t location, uint64_t size);

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
    void location8();
    void set_all(uint64_t location, uint32_t size);
    bool is_nil();

  private:
    uint64_t stp = 0;
    uint32_t cb = 0;
};

}

#endif
