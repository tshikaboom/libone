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
  FileNodeChunkReference(uint64_t stp, uint64_t cb, StpFormat format_stp = StpFormat::stp_uncompressed_8, CbFormat format_cb = CbFormat::cb_uncompressed_8);
  FileNodeChunkReference(StpFormat format_stp = StpFormat::stp_uncompressed_8, CbFormat format_cb = CbFormat::cb_uncompressed_8);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference &obj);

  void parse(const libone::RVNGInputStreamPtr_t &input);

  bool is_fcrNil() const;
  bool is_fcrZero() const;

  /** returns the uncompressed stream position of the referenced chunk. */
  uint64_t stp() const;

  /** returns the uncompressed byte count of the referenced chunk. */
  uint64_t cb() const;

  /** returns the size of the FileNodeChunkReference object in number of bytes. */
  uint32_t get_size_in_file() const;


  StpFormat get_stp_fmt() const
  {
    return m_format_stp;
  }
  CbFormat get_cb_fmt() const
  {
    return m_format_cb;
  }

private:
  uint64_t m_stp;
  uint64_t m_cb;
  StpFormat m_format_stp;
  CbFormat m_format_cb;
};

}

#endif
