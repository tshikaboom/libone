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
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <librevenge-stream/librevenge-stream.h>

#include <libone/libone.h>
#include <libone/ONEDocument.h>
#include "libone_utils.h"

using boost::scoped_ptr;
using boost::shared_ptr;

using librevenge::RVNGInputStream;

using std::equal;



namespace libone
{

//std::unordered_map<std::string ,libone::Object> RootObjectSpace = std::unordered_map<std::string ,libone::Object>();
libone::ExtendedGUID RootObject;

std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces = std::unordered_map<std::string, libone::ObjectSpace>();
// the string is the Object's guid

std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

std::unordered_map<uint32_t, uint32_t> Transactions = std::unordered_map<uint32_t, uint32_t>({{0, 0}});

libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();
libone::Header header;

std::unordered_map<std::string, struct FileData> filedata = std::unordered_map<std::string, struct FileData>();

int debug = 0;


ONEAPI ONEDocument::Confidence ONEDocument::isSupported(librevenge::RVNGInputStream *const input, Type *const type) try
{
  (void) input;
  if (type)
    *type = TYPE_UNKNOWN;

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
  header.parse(input);
  RootFileNodeList root_list;
  long old;

  (void) document;
  // sanity check
  if (ONEDocument::TYPE_UNKNOWN == type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;
  if (ONEDocument::TYPE_RESERVED1 <= type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;

  const RVNGInputStreamPtr_t input_(input, ONEDummyDeleter());

  input_->seek(0, librevenge::RVNG_SEEK_SET);
  TransactionLogFragment log_fragment(header.cTransactionsInLog);

  std::cout << "trying transactions, jumping to " << header.fcrTransactionLog.get_location() << '\n';
  old = input->tell();
  input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);
  log_fragment.parse(input);
  input->seek(old, librevenge::RVNG_SEEK_SET);
  std::cout << "TransactionLog" << '\n' << log_fragment.to_string() << '\n';
  std::cout << header.cTransactionsInLog << " transactions in header\n";




  std::cout << "test fileNodeList " << '\n';
  root_list.parse(input);
  std::cout << "root object is " << RootObject.to_string() << "\n";

  for (auto i: ObjectSpaces)
    std::cout << "object space " << i.first << "\n";

  ObjectSpaces[RootObject.to_string()].to_document(document);

  std::cout << "nothing broke!\n";

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
