/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_LIBONE_H
#define INCLUDED_LIBONE_LIBONE_H

#include "ONEDocument.h"

#include <vector>

using std::string;
namespace libone {
class GUID {
public:

    void parse(librevenge::RVNGInputStream *input);
    string to_string();

  private:
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint16_t Data4[4];
};

class FileChunkReference32 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint32_t get_location();
    uint32_t get_size();
    string to_string();

  private:
    uint32_t stp;
    uint32_t cb;
};

class FileChunkReference64 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint64_t get_location();
    uint64_t get_size();
    string to_string();

  private:
    uint64_t stp;
    uint64_t cb;
};

class FileChunkReference64x32 {
  public:

    void parse(librevenge::RVNGInputStream *input);

    uint64_t get_location();
    uint32_t get_size();
    string to_string();

  private:
    uint64_t stp;
    uint32_t cb;
};


class FileNode {
  public:
    void parse(librevenge::RVNGInputStream *input);

  private:
    uint16_t FileNodeID;
    uint16_t Size;
    uint16_t ABCD;
};


class FileNodeListFragment {
  public:
    void parse(librevenge::RVNGInputStream *input);

  private:
    uint64_t uintMagic;
    uint32_t FileNodeListID;
    uint32_t nFragmentSequence;
    std::vector<FileNode> rgFileNodes;
    uint16_t nextFragment;
    uint64_t footer;
};
}
#endif // INCLUDED_LIBONE_LIBONE_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
