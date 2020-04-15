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
#include <libone/libone.h>

#include "libone_utils.h"
#include "libone_types.h"

#include "Header.h"
#include "FileChunkReference.h"
#include "GUID.h"
#include "FileDataStore.h"

namespace libone {

  void Header::parse(librevenge::RVNGInputStream *input) {
    input->seek(OFFSET_HEADER, librevenge::RVNG_SEEK_SET);

    guidFileType.parse(input);

    guidFile.parse(input);

    guidLegacyFileVersion.parse(input);

    guidFileFormat.parse(input);

    ffvLastCodeThatWroteToThisFile = readU32 (input, false);
    ffvOldestCodeThatMayReadThisFile = readU32 (input, false);
    ffvOldestCodeThatHasWrittenToThisFile = readU32 (input, false);
    ffvNewestCodeThatHasWrittenToThisFile = readU32 (input, false);

    fcrLegacyFreeChunkList.parse(input);

    fcrLegacyTransactionLog.parse(input);

    cTransactionsInLog = readU32 (input, false);

    cbLegacyExpectedFileLength = readU32 (input, false);

    rgbPlaceholder = readU64 (input, false);

    fcrLegacyFileNodeListRoot.parse(input);

    cbLegacyFreeSpaceInFreeChunkList = readU32 (input, false);

    ignored = readU32 (input, false);

    guidAncestor.parse(input);

    crcName = readU32 (input, false);

    fcrHashedChunkList.parse(input);

    fcrTransactionLog.parse(input);

    fcrFileNodeListRoot.parse(input);

    fcrFreeChunkList.parse(input);

    cbExpectedFileLength = readU64 (input, false);

    cbFreeSpaceInFreeChunkList = readU64 (input, false);

    guidFileVersion.parse(input);

    nFileVersionGeneration = readU64 (input, false);

    guidDenyReadFileVersion.parse(input);

    grfDebugLogFlags = readU32 (input, false);

    fcrDebugLog.parse(input);

    fcrAllocVerificationFreeChunkList.parse(input);

    bnCreated = readU32 (input, false);
    bnLastWroteToThisFile = readU32 (input, false);
    bnOldestWritten = readU32 (input, false);
    bnNewestWritten = readU32 (input, false);
  }

}
