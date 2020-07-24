/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <librevenge-stream/librevenge-stream.h>
#include <iostream>
#include "libone_utils.h"
#include "libone_types.h"

#include "FileDataStore.h"
#include "FileChunkReference.h"
#include "FileNodeList.h"

namespace libone
{

void FileDataStore::parse(librevenge::RVNGInputStream *input, FileNodeChunkReference ref)
{
  FileNodeList list(ref.get_location(), ref.get_size());
  FileNode node;
  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
  list.parse(input);

  ONE_DEBUG_MSG(("\n"));
}

std::string FileDataStore::to_string()
{
  return "";
}


}

