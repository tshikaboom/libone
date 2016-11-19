/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_ONEDOCUMENT_H
#define INCLUDED_LIBONE_ONEDOCUMENT_H

#include <librevenge/librevenge.h>
#include <librevenge-stream/librevenge-stream.h>

#ifdef DLL_EXPORT
#ifdef LIBONE_BUILD
#define ONEAPI __declspec(dllexport)
#else
#define ONEAPI __declspec(dllimport)
#endif
#else // !DLL_EXPORT
#ifdef LIBONE_VISIBILITY
#define ONEAPI __attribute__((visibility("default")))
#else
#define ONEAPI
#endif
#endif

namespace libone
{

class ONEDocument
{
public:
  /** Likelihood that the file format is supported.
    */
  enum Confidence
  {
    CONFIDENCE_NONE, //< not supported
    CONFIDENCE_WEAK, //< maybe supported
    CONFIDENCE_UNSUPPORTED_ENCRYPTION, //< the format is supported, but the used encryption method is not
    CONFIDENCE_SUPPORTED_ENCRYPTION, //< the format is supported, but encrypted
    CONFIDENCE_SUPPORTED_PART, //< the file is only a part of a supported structured format
    CONFIDENCE_EXCELLENT //< supported
  };

  /** Result of parsing the file.
    */
  enum Result
  {
    RESULT_OK, //< parsed without any problem
    RESULT_FILE_ACCESS_ERROR, //< problem when accessing the file
    RESULT_PACKAGE_ERROR, //< problem with parsing structured file's content
    RESULT_PARSE_ERROR, //< problem when parsing the file
    RESULT_PASSWORD_MISMATCH, //< problem with given password
    RESULT_UNSUPPORTED_ENCRYPTION, //< unsupported encryption
    RESULT_UNSUPPORTED_FORMAT, //< unsupported file format
    RESULT_UNKNOWN_ERROR //< an unspecified error
  };

  /** Type of document.
    */
  enum Type
  {
    TYPE_UNKNOWN, //< unrecognized file
    TYPE_ONE2016,
    TYPE_RESERVED1, //< reserved for future use
    TYPE_RESERVED2, //< reserved for future use
    TYPE_RESERVED3, //< reserved for future use
    TYPE_RESERVED4, //< reserved for future use
    TYPE_RESERVED5, //< reserved for future use
    TYPE_RESERVED6, //< reserved for future use
    TYPE_RESERVED7, //< reserved for future use
    TYPE_RESERVED8, //< reserved for future use
    TYPE_RESERVED9 //< reserved for future use
  };

  static ONEAPI Confidence isSupported(librevenge::RVNGInputStream *input, Type *type = 0);
  static ONEAPI Result parse(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *document, const char *password = 0);
  static ONEAPI Result parse(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *document, Type type, const char *password = 0);
};

} // namespace libone

#endif // INCLUDED_LIBONE_ONEDOCUMENT_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
