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
#include "ObjectGroup.h"
namespace libone {

  void ObjectGroup::list_parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    FileNodeList list (ref.get_location(), ref.get_size());
    Object object;
    uint32_t index;
    GUID temp = GUID();

    oid.parse(input);
    std::cout << "object group before" << oid.to_string() << "\n";
//    long old = input->tell();
//    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
//    list.parse_header(input);
//    node.parse(input);
//    oid.parse(input);
    std::cout << "object group after" << oid.to_string() << "\n";
    FileNode node = list.get_next_node(input);
    while (!node.isEnd()) {
      node.parse(input);

      switch (node.get_FileNodeID()) {
        case FileNode::GlobalIdTableStart2FND:
          GlobalIdentificationTable.clear();
          break;
        case FileNode::GlobalIdTableEntryFNDX:
          index = readU32 (input);
          temp.parse(input);
          GlobalIdentificationTable[index] = temp;
          break;
        case FileNode::DataSignatureGroupDefinitionFND:
          DataSignatureGroup.parse(input);
          break;
        case FileNode::ObjectDeclaration2RefCountFND:
          std::cout << "going to parse " << node.get_ref().get_location() << '\n';
          object.parse(input, node.get_ref());
          std::cout << object.to_string();
          break;
        default:
          break;
      }
    }

//    input->seek(old, librevenge::RVNG_SEEK_SET);

  }

}

