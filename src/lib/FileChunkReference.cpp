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

FileChunkReference::FileChunkReference(enum FileChunkReferenceSize fcr_size) :
  m_type(fcr_size),
  m_offset(0),
  m_size_in_file(0),
  m_stp(0),
  m_cb(0)
{}

void FileChunkReference::parse(librevenge::RVNGInputStream *input)
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

long FileChunkReference::get_location()
{
  return m_stp;
}
long FileChunkReference::get_size()
{
  return m_cb;
}

std::string FileChunkReference::to_string()
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

bool FileChunkReference::is_fcrNil()
{
  bool cbval = (m_cb == 0);
  switch (m_type)
  {
  case Size32x32:
    return (cbval && (m_stp & 0xFFFFFFFF));
  case Size64x64:
  case Size64x32:
    return (cbval && (m_stp & 0xFFFFFFFFFFFFFFFF));
  case fcr_size_invalid:
  default:
    return false;
  }
}

bool FileChunkReference::is_fcrZero()
{
  return ((m_stp == 0) && (m_cb == 0));
}

void FileChunkReference::set_zero()
{
  m_stp = 0;
  m_cb = 0;
  m_size_in_file = 0;
  m_type = fcr_size_invalid;
}

// Size of the structure in bytes. Used for seeking
long FileChunkReference::get_size_in_file()
{
  return m_size_in_file;
}
}
