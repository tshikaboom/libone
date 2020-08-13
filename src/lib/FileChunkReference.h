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

#include "libone_utils.h"
namespace libone
{

enum FileChunkReferenceSize
{
  Size32x32,
  Size64x64,
  Size64x32,
  fcr_size_invalid
};

class FileChunkReference
{
public:
  FileChunkReference(enum FileChunkReferenceSize fcr_size);


  void parse(const libone::RVNGInputStreamPtr_t &input);
  std::string to_string();
  long get_location();
  long get_size();
  bool is_fcrNil();
  bool is_fcrZero();
  void set_zero();
  long get_size_in_file();

private:
  enum FileChunkReferenceSize m_type;
  long m_offset;
  long m_size_in_file;
  uint64_t m_stp;
  uint64_t m_cb;
};

}

#endif
