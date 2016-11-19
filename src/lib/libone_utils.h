/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_UTILS_H
#define INCLUDED_LIBONE_UTILS_H

#ifdef DEBUG
#include <cstdio>
#endif

#include <string>

#include <boost/shared_ptr.hpp>

#include <librevenge-stream/librevenge-stream.h>
#include <librevenge/librevenge.h>

#ifdef _MSC_VER

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned uint32_t;
typedef int int32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;

#else

#ifdef HAVE_CONFIG_H

#include "config.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#else

// assume that the headers are there inside LibreOffice build when no HAVE_CONFIG_H is defined
#include <stdint.h>
#include <inttypes.h>

#endif

#endif

// debug message includes source file and line number
//#define VERBOSE_DEBUG 1

// do nothing with debug messages in a release compile
#ifdef DEBUG
#ifdef VERBOSE_DEBUG
#define ONE_DEBUG_MSG(M) std::printf("%15s:%5d: ", __FILE__, __LINE__); std::printf M
#define ONE_DEBUG(M) M
#else
#define ONE_DEBUG_MSG(M) std::printf M
#define ONE_DEBUG(M) M
#endif
#else
#define ONE_DEBUG_MSG(M)
#define ONE_DEBUG(M)
#endif

#define ONE_NUM_ELEMENTS(array) (sizeof(array) / sizeof(array[0]))

namespace libone
{

typedef boost::shared_ptr<librevenge::RVNGInputStream> RVNGInputStreamPtr_t;

struct ONEDummyDeleter
{
  void operator()(void *) {}
};

uint8_t readU8(librevenge::RVNGInputStream *input, bool = false);
uint16_t readU16(librevenge::RVNGInputStream *input, bool bigEndian=false);
uint32_t readU32(librevenge::RVNGInputStream *input, bool bigEndian=false);
uint64_t readU64(librevenge::RVNGInputStream *input, bool bigEndian=false);

const unsigned char *readNBytes(librevenge::RVNGInputStream *input, unsigned long numBytes);

std::string readCString(librevenge::RVNGInputStream *input);
std::string readPascalString(librevenge::RVNGInputStream *input);

void skip(librevenge::RVNGInputStream *input, unsigned long numBytes);

void seek(librevenge::RVNGInputStream *input, unsigned long pos);
void seekRelative(librevenge::RVNGInputStream *input, long pos);

unsigned long getLength(librevenge::RVNGInputStream *input);

uint8_t readU8(boost::shared_ptr<librevenge::RVNGInputStream> input, bool = false);
uint16_t readU16(boost::shared_ptr<librevenge::RVNGInputStream> input, bool bigEndian=false);
uint32_t readU32(boost::shared_ptr<librevenge::RVNGInputStream> input, bool bigEndian=false);
uint64_t readU64(boost::shared_ptr<librevenge::RVNGInputStream> input, bool bigEndian=false);

const unsigned char *readNBytes(boost::shared_ptr<librevenge::RVNGInputStream> input, unsigned long numBytes);

std::string readCString(boost::shared_ptr<librevenge::RVNGInputStream> input);
std::string readPascalString(boost::shared_ptr<librevenge::RVNGInputStream> input);

void skip(boost::shared_ptr<librevenge::RVNGInputStream> input, unsigned long numBytes);

void seek(boost::shared_ptr<librevenge::RVNGInputStream> input, unsigned long pos);
void seekRelative(boost::shared_ptr<librevenge::RVNGInputStream> input, long pos);

unsigned long getLength(boost::shared_ptr<librevenge::RVNGInputStream> input);

class EndOfStreamException
{
public:
  EndOfStreamException();
};

class GenericException
{
};

// parser exceptions

class FileAccessError
{
};

class PackageError
{
};

class ParseError
{
};

class PasswordMismatch
{
};

class UnsupportedEncryption
{
};

class UnsupportedFormat
{
};

} // namespace libone

#endif // INCLUDED_LIBONE_UTILS_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
