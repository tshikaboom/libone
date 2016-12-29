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

namespace libone {

  void FileDataStore::parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    FileNodeList list(ref.get_location(), ref.get_size());
    FileNode node;
    long old = input->tell();
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    long old2 = 0;
    GUID reference = GUID();
    GUID _header = GUID();
    while (!list.is_end()) {
      struct FileData data;
      node = list.get_next_node(input);
      switch (node.get_FileNodeID()) {
        case FileNode::FileDataStoreObjectReferenceFND:
        std::cout << "FileDataStoreObjectReferenceFND\n";
        reference.parse(input);
        std::cout << "parsed reference " << reference.to_string () << "\n";
        old2 = input->tell();
        input->seek(node.get_ref().get_location(), librevenge::RVNG_SEEK_SET);
        _header.parse(input);
//        std::cout << "parsed filedatastore header " << header.to_string() << "\n";
        data.length = readU64 (input);
        skip(input, 12);
        data.location = input->tell();
        filedata[reference.to_string()] = data;
        _header.parse(input);
//        std::cout << "parsed filedatastore footer " << header.to_string () << "\n";
        input->seek(old2, librevenge::RVNG_SEEK_SET);
        break;
      case FileNode::ChunkTerminatorFND:
        break;
      default:
        std::cout << "FileDataStore: filenodeid not good " << node.get_FileNodeID() << "\n";
        break;
      }
    }

    input->seek(old, librevenge::RVNG_SEEK_SET);
    std::cout << "restored position " << input->tell() << "\n";
  }

  std::string FileDataStore::to_string() {
    return "";
  }


}

