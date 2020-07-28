/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <algorithm>
#include <cstring>
#include <iostream>

#include <librevenge-stream/librevenge-stream.h>

#include <libone/libone.h>
#include <libone/ONEDocument.h>
#include "libone_utils.h"
#include "OneNoteParser.h"

namespace
{

enum OneNoteVersion
{
  ONENOTE_UNKNOWN_VERSION,
  ONENOTE,
  ONETOC2
};

}


namespace libone
{

int debug = 0;


ONEAPI ONEDocument::Confidence ONEDocument::isSupported(librevenge::RVNGInputStream *const input, Type *const type) try
{
  (void) input;
  if (type)
    *type = TYPE_UNKNOWN;

  if (type)
    *type = TYPE_ONE2016;

  return CONFIDENCE_EXCELLENT;
  return CONFIDENCE_NONE;
}
catch (...)
{
  return CONFIDENCE_NONE;
}

ONEAPI ONEDocument::Result ONEDocument::parse(librevenge::RVNGInputStream *const input, librevenge::RVNGDrawingInterface *const document, const char *const)
{
  Type type;
  Confidence confidence = isSupported(input, &type);
  if (CONFIDENCE_NONE == confidence)
    return RESULT_UNSUPPORTED_FORMAT;
  else if (CONFIDENCE_SUPPORTED_PART == confidence)
    return RESULT_UNSUPPORTED_FORMAT;
  else if (CONFIDENCE_UNSUPPORTED_ENCRYPTION == confidence)
    return RESULT_UNSUPPORTED_ENCRYPTION;

  return parse(input, document, type);
}

ONEAPI ONEDocument::Result ONEDocument::parse(librevenge::RVNGInputStream *const input, librevenge::RVNGDrawingInterface *const document, const ONEDocument::Type type, const char *const) try
{
  Header header;
  header.parse(input);

  (void) document;
  // sanity check
  if (ONEDocument::TYPE_UNKNOWN == type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;
  if (ONEDocument::TYPE_RESERVED1 <= type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;

  const RVNGInputStreamPtr_t input_(input, ONEDummyDeleter());

  OneNoteParser parser = OneNoteParser(input, document);
  (void) parser;
  return RESULT_UNKNOWN_ERROR;
}
catch (const FileAccessError &)
{
  return RESULT_FILE_ACCESS_ERROR;
}
catch (const PackageError &)
{
  return RESULT_PACKAGE_ERROR;
}
catch (const PasswordMismatch &)
{
  return RESULT_PASSWORD_MISMATCH;
}
catch (const UnsupportedEncryption &)
{
  return RESULT_UNSUPPORTED_ENCRYPTION;
}
catch (const UnsupportedFormat &)
{
  return RESULT_UNSUPPORTED_FORMAT;
}
catch (...)
{
  return RESULT_UNKNOWN_ERROR;
}

} // namespace libone

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
