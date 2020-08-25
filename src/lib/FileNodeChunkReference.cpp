/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include <libone/libone.h>
#include "FileNodeChunkReference.h"
#include "libone_utils.h"

namespace libone
{

FileNodeChunkReference::FileNodeChunkReference(uint64_t stp, uint64_t cb, StpFormat format_stp, CbFormat format_cb) :
  m_stp(stp),
  m_cb(cb),
  m_format_stp(format_stp),
  m_format_cb(format_cb)
{}

FileNodeChunkReference::FileNodeChunkReference(StpFormat format_stp, CbFormat format_cb) :
  m_stp(0),
  m_cb(0),
  m_format_stp(format_stp),
  m_format_cb(format_cb)
{}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference &obj)
{
  obj.parse(input);
  return input;
}


bool FileNodeChunkReference::is_fcrNil() const
{
  bool cbval = (m_cb == 0);
  switch (m_format_stp)
  {
  case StpFormat::stp_uncompressed_8:
    return (cbval && (m_stp & 0xFFFFFFFFFFFFFFFF));

  case StpFormat::stp_uncompressed_4:
  case StpFormat::stp_compressed_4:
    return (cbval && (m_stp & 0xFFFFFFFF));

  case StpFormat::stp_compressed_2:
    return (cbval && (m_stp & 0xFFFF));

  default:
    return false;
  }
}

bool FileNodeChunkReference::is_fcrZero() const
{
  return ((m_stp == 0) && (m_cb == 0));
}

uint64_t FileNodeChunkReference::stp() const
{
  switch (m_format_stp)
  {
  case StpFormat::stp_uncompressed_8:
  case StpFormat::stp_uncompressed_4:
    return m_stp;
    break;
  case StpFormat::stp_compressed_4:
  case StpFormat::stp_compressed_2:
    return m_stp * 8u;
    break;
  case StpFormat::stp_invalid:
  default:
    return 0;
  }
}

uint64_t FileNodeChunkReference::cb() const
{
  switch (m_format_cb)
  {
  case CbFormat::cb_uncompressed_8:
  case CbFormat::cb_uncompressed_4:
    return m_cb;
    break;
  case CbFormat::cb_compressed_2:
  case CbFormat::cb_compressed_1:
    return m_cb * 8u;
    break;
  case CbFormat::cb_invalid:
  default:
    return 0;
  }
}

uint32_t FileNodeChunkReference::get_size_in_file() const
{
  uint32_t ret = 0;
  switch (m_format_stp)
  {
  case StpFormat::stp_uncompressed_8:
    ret += sizeof(uint64_t);
    break;
  case StpFormat::stp_uncompressed_4:
  case StpFormat::stp_compressed_4:
    ret += sizeof(uint32_t);
    break;
  case StpFormat::stp_compressed_2:
    ret += sizeof(uint16_t);
    break;
  case StpFormat::stp_invalid:
  default:
    // size would be 0
    break;
  }

  switch (m_format_cb)
  {
  case CbFormat::cb_uncompressed_8:
    ret += sizeof(uint64_t);
    break;
  case CbFormat::cb_uncompressed_4:
    ret += sizeof(uint32_t);
    break;
  case CbFormat::cb_compressed_2:
    ret += sizeof(uint16_t);
    break;
  case CbFormat::cb_compressed_1:
    ret += sizeof(uint8_t);
    break;
  case CbFormat::cb_invalid:
  default:
    // size would be 0
    break;
  }

  return ret;
}

void FileNodeChunkReference::parse(const libone::RVNGInputStreamPtr_t &input)
{
  switch (m_format_stp)
  {
  case StpFormat::stp_uncompressed_8:
    m_stp = readU64(input, false);
    break;
  case StpFormat::stp_uncompressed_4:
    m_stp = readU32(input, false);
    break;
  case StpFormat::stp_compressed_2:
    m_stp = readU16(input, false) * 8;
    break;
  case StpFormat::stp_compressed_4:
    m_stp = readU32(input, false) * 8;
    break;
  case StpFormat::stp_invalid:
  default:
    assert(false);
    break;
  }

  switch (m_format_cb)
  {
  case CbFormat::cb_uncompressed_4:
    m_cb = readU32(input, false);
    break;
  case CbFormat::cb_uncompressed_8:
    m_cb = readU64(input, false);
    break;
  case CbFormat::cb_compressed_1:
    m_cb = readU8(input) * 8;
    break;
  case CbFormat::cb_compressed_2:
    m_cb = readU16(input, false);
    break;
  case CbFormat::cb_invalid:
  default:
    assert(false);
    break;
  }

  return;
}

}
