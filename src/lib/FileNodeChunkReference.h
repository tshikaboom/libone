/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODECHUNKREFERENCE_H
#define INCLUDED_LIBONE_FILENODECHUNKREFERENCE_H

#include <librevenge-stream/librevenge-stream.h>

#include "libone_utils.h"

namespace libone
{

enum class StpFormat
{
  stp_uncompressed_8 = 0,
  stp_uncompressed_4 = 1,
  stp_compressed_2 = 2,
  stp_compressed_4 = 3,
  stp_invalid
};

enum class CbFormat
{
  cb_uncompressed_4 = 0,
  cb_uncompressed_8 = 1,
  cb_compressed_1 = 2,
  cb_compressed_2 = 3,
  cb_invalid
};

class FileNodeChunkReference
{
public:
  FileNodeChunkReference(const StpFormat format_stp = StpFormat::stp_invalid, const CbFormat format_cb = CbFormat::cb_invalid);
  FileNodeChunkReference(const uint64_t stp, const uint64_t cb, const StpFormat format_stp = StpFormat::stp_uncompressed_8, const CbFormat format_cb = CbFormat::cb_uncompressed_8);
  bool is_fcrNil();
  bool is_fcrZero();
  uint64_t stp() const
  {
    return m_stp;
  }
  uint64_t cb() const
  {
    return m_cb;
  }
  uint32_t get_size_in_file();
  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference &obj);
  void parse(const libone::RVNGInputStreamPtr_t &input);
  void parse(const libone::RVNGInputStreamPtr_t &input, const uint64_t offset);
  void set_zero();
  StpFormat get_stp_fmt()
  {
    return m_format_stp;
  }
  CbFormat get_cb_fmt()
  {
    return m_format_cb;
  }

private:
  uint64_t m_offset;
  uint64_t m_stp;
  uint64_t m_cb;
  StpFormat m_format_stp;
  CbFormat m_format_cb;
};

}

#endif
