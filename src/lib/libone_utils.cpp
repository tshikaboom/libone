/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstdio>
#include <sstream>
#include <iomanip>

#include "libone_utils.h"

namespace libone
{

namespace
{

void checkStream(librevenge::RVNGInputStream *const input)
{
  if (!input || input->isEnd())
    throw EndOfStreamException();
}

struct SeekFailedException {};

}

uint8_t readU8(librevenge::RVNGInputStream *input, bool /* bigEndian */)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(uint8_t), numBytesRead);

  if (p && numBytesRead == sizeof(uint8_t))
    return *(uint8_t const *)(p);
  throw EndOfStreamException();
}

uint16_t readU16(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(uint16_t), numBytesRead);

  if (p && numBytesRead == sizeof(uint16_t))
  {
    if (bigEndian)
      return static_cast<uint16_t>((uint16_t)p[1]|((uint16_t)p[0]<<8));
    return static_cast<uint16_t>((uint16_t)p[0]|((uint16_t)p[1]<<8));
  }
  throw EndOfStreamException();
}

uint32_t readU32(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(uint32_t), numBytesRead);

  if (p && numBytesRead == sizeof(uint32_t))
  {
    if (bigEndian)
      return (uint32_t)p[3]|((uint32_t)p[2]<<8)|((uint32_t)p[1]<<16)|((uint32_t)p[0]<<24);
    return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);
  }
  throw EndOfStreamException();
}

uint64_t readU64(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(uint64_t), numBytesRead);

  if (p && numBytesRead == sizeof(uint64_t))
  {
    if (bigEndian)
      return (uint64_t)p[7]|((uint64_t)p[6]<<8)|((uint64_t)p[5]<<16)|((uint64_t)p[4]<<24)|((uint64_t)p[3]<<32)|((uint64_t)p[2]<<40)|((uint64_t)p[1]<<48)|((uint64_t)p[0]<<56);
    return (uint64_t)p[0]|((uint64_t)p[1]<<8)|((uint64_t)p[2]<<16)|((uint64_t)p[3]<<24)|((uint64_t)p[4]<<32)|((uint64_t)p[5]<<40)|((uint64_t)p[6]<<48)|((uint64_t)p[7]<<56);
  }
  throw EndOfStreamException();
}

int8_t read8(librevenge::RVNGInputStream *input, bool /* bigEndian */)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(int8_t), numBytesRead);

  if (p && numBytesRead == sizeof(int8_t))
    return static_cast<int8_t>(*(uint8_t const *)(p));
  throw EndOfStreamException();
}

int16_t read16(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(int16_t), numBytesRead);

  if (p && numBytesRead == sizeof(int16_t))
  {
    if (bigEndian)
      return static_cast<int16_t>((uint16_t)p[1]|((uint16_t)p[0]<<8));
    return static_cast<int16_t>((uint16_t)p[0]|((uint16_t)p[1]<<8));
  }
  throw EndOfStreamException();
}

int32_t read32(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(int32_t), numBytesRead);

  if (p && numBytesRead == sizeof(int32_t))
  {
    if (bigEndian)
      return static_cast<int32_t>((uint32_t)p[3]|((uint32_t)p[2]<<8)|((uint32_t)p[1]<<16)|((uint32_t)p[0]<<24));
    return static_cast<int32_t>((uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24));
  }
  throw EndOfStreamException();
}

int64_t read64(librevenge::RVNGInputStream *input, bool bigEndian)
{
  checkStream(input);

  unsigned long numBytesRead;
  uint8_t const *p = input->read(sizeof(int64_t), numBytesRead);

  if (p && numBytesRead == sizeof(int64_t))
  {
    if (bigEndian)
      return static_cast<int64_t>((uint64_t)p[7]|((uint64_t)p[6]<<8)|((uint64_t)p[5]<<16)|((uint64_t)p[4]<<24)|((uint64_t)p[3]<<32)|((uint64_t)p[2]<<40)|((uint64_t)p[1]<<48)|((uint64_t)p[0]<<56));
    return static_cast<int64_t>((uint64_t)p[0]|((uint64_t)p[1]<<8)|((uint64_t)p[2]<<16)|((uint64_t)p[3]<<24)|((uint64_t)p[4]<<32)|((uint64_t)p[5]<<40)|((uint64_t)p[6]<<48)|((uint64_t)p[7]<<56));
  }
  throw EndOfStreamException();
}

const unsigned char *readNBytes(librevenge::RVNGInputStream *const input, const unsigned long numBytes)
{
  checkStream(input);

  unsigned long readBytes = 0;
  const unsigned char *const s = input->read(numBytes, readBytes);

  if (numBytes != readBytes)
    throw EndOfStreamException();

  return s;
}

std::string readCstring(librevenge::RVNGInputStream *input)
{
  checkStream(input);

  std::string str;
  unsigned char c = readU8(input);
  while (0 != c)
  {
    str.push_back(c);
    c = readU8(input);
  }

  return str;
}

std::string readPascalstring(librevenge::RVNGInputStream *input)
{
  checkStream(input);

  const unsigned length = readU8(input);
  std::string str;
  for (unsigned i = 0; length != i; ++i)
    str.push_back(readU8(input));

  return str;
}

void skip(librevenge::RVNGInputStream *input, unsigned long numBytes)
{
  checkStream(input);

  seekRelative(input, static_cast<long>(numBytes));
}

void seek(librevenge::RVNGInputStream *const input, const unsigned long pos)
{
  if (!input)
    throw EndOfStreamException();

  if (0 != input->seek(static_cast<long>(pos), librevenge::RVNG_SEEK_SET))
    throw SeekFailedException();
}

void seekRelative(librevenge::RVNGInputStream *const input, const long pos)
{
  if (!input)
    throw EndOfStreamException();

  if (0 != input->seek(pos, librevenge::RVNG_SEEK_CUR))
    throw SeekFailedException();
}

unsigned long getLength(librevenge::RVNGInputStream *const input)
{
  if (!input)
    throw SeekFailedException();

  const unsigned long begin = input->tell();
  unsigned long end = begin;

  if (0 == input->seek(0, librevenge::RVNG_SEEK_END))
    end = input->tell();
  else
  {
    // librevenge::RVNG_SEEK_END does not work. Use the harder way.
    while (!input->isEnd())
    {
      readU8(input);
      ++end;
    }
  }

  seek(input, begin);

  return end - begin;
}

uint8_t readU8(const std::shared_ptr<librevenge::RVNGInputStream> input, bool)
{
  return readU8(input.get());
}

uint16_t readU16(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return readU16(input.get(), bigEndian);
}

uint32_t readU32(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return readU32(input.get(), bigEndian);
}

uint64_t readU64(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return readU64(input.get(), bigEndian);
}

int8_t read8(const std::shared_ptr<librevenge::RVNGInputStream> input, bool)
{
  return read8(input.get());
}

int16_t read16(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return read16(input.get(), bigEndian);
}

int32_t read32(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return read32(input.get(), bigEndian);
}

int64_t read64(const std::shared_ptr<librevenge::RVNGInputStream> input, const bool bigEndian)
{
  return read64(input.get(), bigEndian);
}

const unsigned char *readNBytes(const std::shared_ptr<librevenge::RVNGInputStream> input, const unsigned long numBytes)
{
  return readNBytes(input.get(), numBytes);
}

std::string readCstring(const std::shared_ptr<librevenge::RVNGInputStream> input)
{
  return readCstring(input.get());
}

std::string readPascalstring(const std::shared_ptr<librevenge::RVNGInputStream> input)
{
  return readPascalstring(input.get());
}

void skip(const std::shared_ptr<librevenge::RVNGInputStream> input, const unsigned long numBytes)
{
  return skip(input.get(), numBytes);
}

void seek(const std::shared_ptr<librevenge::RVNGInputStream> input, const unsigned long pos)
{
  seek(input.get(), pos);
}

void seekRelative(const std::shared_ptr<librevenge::RVNGInputStream> input, const long pos)
{
  seekRelative(input.get(), pos);
}

unsigned long getLength(const std::shared_ptr<librevenge::RVNGInputStream> input)
{
  return getLength(input.get());
}


const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, uint8_t &val)
{
  val = readU8(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, uint16_t &val)
{
  val = readU16(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, uint32_t &val)
{
  val = readU32(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, uint64_t &val)
{
  val = readU64(input, false);
  return input;
}

const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, int8_t &val)
{
  val = read8(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, int16_t &val)
{
  val = read16(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, int32_t &val)
{
  val = read32(input, false);
  return input;
}
const RVNGInputStreamPtr_t &operator>>(const RVNGInputStreamPtr_t &input, int64_t &val)
{
  val = read64(input, false);
  return input;
}


template <typename T>
std::string int_to_hex(const T i)
{
  std::stringstream stream;

  stream << std::hex
         << std::setfill('0')
         << std::setw(sizeof(T)*2)
         << i;

  return stream.str();
}

// instantiate for library built
template std::string int_to_hex<uint8_t>(const uint8_t);
template std::string int_to_hex<uint16_t>(const uint16_t);
template std::string int_to_hex<uint32_t>(const uint32_t);
template std::string int_to_hex<uint64_t>(const uint64_t);
template std::string int_to_hex<int8_t>(const int8_t);
template std::string int_to_hex<int16_t>(const int16_t);
template std::string int_to_hex<int32_t>(const int32_t);
template std::string int_to_hex<int64_t>(const int64_t);


EndOfStreamException::EndOfStreamException()
{
  ONE_DEBUG_MSG(("Throwing EndOfStreamException\n"));
}

}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
