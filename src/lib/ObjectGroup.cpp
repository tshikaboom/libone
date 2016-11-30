/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include "libone_utils.h"
#include "FileNodeDescriptor.h"
#include "ObjectGroup.h"
namespace libone {

  void ObjectGroup::list_parse(librevenge::RVNGInputStream *input, FileChunkReference64 ref) {
    FileNodeList list (ref.get_location(), ref.get_size());
    FileNode node;
    uint32_t index;
    GUID temp = GUID();
    long old = input->tell();
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    list.parse_header(input);
    node.parse(input);
    oid.parse(input);
    std::cout << "object group " << oid.to_string() << "\n";
    while (!node.isEnd()) {
      node.parse(input);

      switch (node.get_FileNodeID()) {
        case FileNodeDescriptor::GlobalIdTableStart2FND:
          GlobalIdentificationTable.clear();
          break;
        case FileNodeDescriptor::GlobalIdTableEntryFNDX:
          index = readU32 (input);
          temp.parse(input);
          GlobalIdentificationTable[index] = temp;
          break;
        case FileNodeDescriptor::DataSignatureGroupDefinitionFND:
          DataSignatureGroup.parse(input);
          break;
        default:
          break;
      }
    }

    input->seek(old, librevenge::RVNG_SEEK_SET);

  }

}

