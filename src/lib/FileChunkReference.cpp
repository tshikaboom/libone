/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>
#include "FileChunkReference.h"
#include "libone_utils.h"

namespace libone
{

FileChunkReference::FileChunkReference(const enum FileChunkReferenceSize fcr_size) :
  m_type(fcr_size),
  m_offset(0),
  m_stp(0),
  m_cb(0)
{}

FileChunkReference::FileChunkReference(const uint64_t stp, const uint64_t cb, const enum FileChunkReferenceSize fcr_size) :
  m_type(fcr_size),
  m_offset(0),
  m_stp(0),
  m_cb(0)
{
  set_location(stp);
  set_size(cb);
}

void FileChunkReference::parse(const libone::RVNGInputStreamPtr_t &input)
{
  m_offset = input->tell();

  switch (m_type)
  {
  case Size64x64:
    m_stp = readU64(input, false);
    m_cb = readU64(input, false);
    break;
  case Size32x32:
    m_stp = readU32(input, false);
    m_cb = readU32(input, false);
    break;
  case Size64x32:
    m_stp = readU64(input, false);
    m_cb = readU32(input, false);
    break;
  case fcr_size_invalid:
  default:
    ONE_DEBUG_MSG(("FileChunkReference: not good!\n"));
    break;
  }
}

uint64_t FileChunkReference::get_location() const
{
  return m_stp;
}

void FileChunkReference::set_location(const uint64_t stp)
{
  // making sure, stp is not larger than the fcr type specifies
  switch (m_type)
  {
  case Size32x32:
    if (stp > 0xFFFFFFFF)
    {
      m_stp = 0xFFFFFFFF;
    }
    else
    {
      m_stp = stp;
    }
    break;
  case Size64x64:
  case Size64x32:
  case fcr_size_invalid:
  default:
    m_stp = stp;
    break;
  }
}

uint64_t FileChunkReference::get_size() const
{
  return m_cb;
}
void FileChunkReference::set_size(const uint64_t cb)
{
  // making sure, stp is not larger than the fcr type specifies
  switch (m_type)
  {
  case Size64x32:
  case Size32x32:
    if (cb > 0xFFFFFFFF)
    {
      m_cb = 0xFFFFFFFF;
      ONE_DEBUG_MSG(("Warning: FileChunkReference's cb value too large for its type"));
    }
    else
    {
      m_cb = cb;
    }
    break;
  case Size64x64:
  case fcr_size_invalid:
  default:
    m_cb = cb;
    break;
  }
}

std::string FileChunkReference::to_string() const
{
  std::stringstream stream;
  if (is_fcrNil()) return "fcrNil";
  if (is_fcrZero()) return "fcrZero";

  switch (m_type)
  {
  case Size32x32:
    stream << std::hex << "stp32 " << m_stp << " cb32 " << m_cb;
    break;
  case Size64x32:
    stream << std::hex << "stp64 " << m_stp << " cb32 " << m_cb;
    break;
  case Size64x64:
    stream << std::hex << "stp64 " << m_stp << " cb64 " << m_cb;
    break;
  case fcr_size_invalid:
  default:
    stream << "fcr_size_invalid invalid FileChunkReference";
    break;
  }

  return stream.str();
}

bool FileChunkReference::is_fcrNil() const
{
  bool cbval = (m_cb == 0);
  switch (m_type)
  {
  case Size32x32:
    return (cbval && (m_stp & 0xFFFFFFFF));
  case Size64x64:
  case Size64x32:
    return (cbval && (m_stp & 0xFFFFFFFFFFFFFFFF));
  default:
    return false;
  }
}

bool FileChunkReference::is_fcrZero() const
{
  return ((m_stp == 0) && (m_cb == 0));
}

void FileChunkReference::set_zero()
{
  m_stp = 0;
  m_cb = 0;
  m_type = fcr_size_invalid;
}

// Size of the structure in bytes. Used for seeking
uint64_t FileChunkReference::get_size_in_file() const
{
  uint64_t size = 0;
  switch (m_type)
  {
  case Size32x32:
    size += 8;
    break;
  case Size64x32:
    size += 12;
    break;
  case Size64x64:
    size += 16;
    break;
  case fcr_size_invalid:
  default:
    break;
  }

  return size;
}

}
