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

  GUID guidFileType;
  FileChunkReference chunk;
  FileChunkReference FileNodeListRoot;
  FileChunkReference TransactionLog;
  TransactionLogFragment log_fragment;

  (void) document;
  // sanity check
  if (ONEDocument::TYPE_UNKNOWN == type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;
  if (ONEDocument::TYPE_RESERVED1 <= type)
    return ONEDocument::RESULT_UNSUPPORTED_FORMAT;

  const RVNGInputStreamPtr_t input_(input, ONEDummyDeleter());

  input_->seek(0, librevenge::RVNG_SEEK_SET);

  guidFileType.parse(input);
  std::cout << "guidFileType: " << guidFileType.to_string() << '\n';

  guidFileType.parse(input);
  std::cout << "guidFile: " << guidFileType.to_string() << '\n';

  guidFileType.parse(input);
  std::cout << "guidLegacyVersion: " << guidFileType.to_string() << '\n';

  guidFileType.parse(input);
  std::cout << "guidFileFormat: " << guidFileType.to_string() << '\n';


  std::cout << "ffvLastCodeThatWroteToThisFile " << std::hex << readU32 (input, false) << '\n';
  std::cout << "ffvOldestCodeThatHasWrittenToThisFile " << std::hex << readU32 (input, false) << '\n';
  std::cout << "ffvNewestCodeThatHasWrittenToThisFile " << std::hex << readU32 (input, false) << '\n';
  std::cout << "ffvOldestCodeThatMayReadThisFile " << std::hex << readU32 (input, false) << '\n';

  chunk.parse(input, FileChunkReference::mode::Type32x32);
  std::cout << "fcrLegacyFreeChunkList stp " << chunk.to_string() << '\n';

  chunk.parse(input, FileChunkReference::mode::Type32x32);
  std::cout << "fcrLegacyTransactionLog " << chunk.to_string() << '\n';

  std::cout << "cTransactionsInLog " << std::hex << readU32 (input, false) << '\n';
  std::cout << "cbLegacyExpectedFileLength " << std::hex << readU32 (input, false) << '\n';
  std::cout << "rgbPlaceholder " << std::hex << readU64 (input, false) << '\n';

  chunk.parse(input, FileChunkReference::mode::Type32x32);
  std::cout << "fcrLegacyFileNodeListRoot " << chunk.to_string() << '\n';

  std::cout << "cbLegacyFreeSpaceInFreeChunkList " << std::hex << readU32 (input, false) << '\n';
/*  std::cout << "fNeedsDefrag " << std::hex << readU8 (input, true) << '\n';
  std::cout << "fRepairedFile " << std::hex << readU8 (input, true) << '\n';
  std::cout << "fNeedsGarbageCollect " << std::hex << readU8 (input, true) << '\n';
  std::cout << "fHasNoEmbeddedFileObjects " << std::hex << readU8 (input, true) << '\n';
*/
  std::cout << "ignored " << readU32 (input) << '\n';

  guidFileType.parse(input);
  std::cout << "guidAncestor: " << guidFileType.to_string() << '\n';

  std::cout << "crcName " << readU32 (input, false) << '\n';

  chunk.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrHashedChunkList " << chunk.to_string() << '\n';

  TransactionLog.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrTransactionLog " << TransactionLog.to_string() << '\n';

  std::cout << "position " << input->tell() << '\n';
  FileNodeListRoot.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrFileNodeListRoot " << FileNodeListRoot.to_string() << '\n';

  chunk.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrFreeChunkList " << chunk.to_string() << '\n';

  std::cout << "cbExpectedFileLength " << readU64 (input, false) << '\n';

  std::cout << "cbFreeSpaceInFreeChunkList " << readU64 (input, false) << '\n';

  guidFileType.parse(input);
  std::cout << "guidFileVersion: " << guidFileType.to_string() << '\n';

  std::cout << "nFileVersionGeneration " << readU64 (input, false) << '\n';

  guidFileType.parse(input);
  std::cout << "guidDenyReadFileVersion: " << guidFileType.to_string() << '\n';

  std::cout << "grfDebugLogFlags " << readU32 (input, false) << '\n';


//  std::cout << "empty32 " << readU32 (input, true) << '\n';

  chunk.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrDebugLog " << chunk.to_string() << '\n';

  chunk.parse(input, FileChunkReference::mode::Type64x32);
  std::cout << "fcrAllocVerificationFreeChunkList " << chunk.to_string() << '\n';

  std::cout << "bnCreated " << readU32 (input, true) << '\n';

    std::cout << "bnLastWroteToThisFile " << readU32 (input, true) << '\n';

    std::cout << "nbOldestWritten " << readU32 (input, true) << '\n';
    std::cout << "bnNewestWritten " << readU32 (input, true) << '\n';

    std::cout << "position " << input->tell() << '\n';

    std::cout << "test fileNodeList " << '\n';
//    long old = input->tell();
    input->seek (FileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);
    FileNodeList first_fragment(FileNodeListRoot.get_location(), FileNodeListRoot.get_size());
//    std::cout << FileNodeListRoot.get_location() << " seeking to " << input->tell() << '\n';
    first_fragment.parse(input, 0);
 //   std::cout << first_fragment.to_string();

  std::cout << "trying transactions, jumping to " << TransactionLog.get_location() << '\n';
  input->seek(TransactionLog.get_location(), librevenge::RVNG_SEEK_SET);
  log_fragment.parse(input);
  std::cout << "TransactionLog" << '\n' << log_fragment.to_string() << '\n';

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
