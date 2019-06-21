/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "libone_types.h"
#include "ObjectGroup.h"

namespace libone {

  std::unordered_map<std::string, libone::Object> ObjectGroup::list_parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    FileNodeList list (ref.get_location(), ref.get_size());
    std::unordered_map<std::string, libone::Object> object_map = std::unordered_map<std::string, libone::Object>();
    uint32_t index;
    GUID temp = GUID();
    oid.parse(input);
    std::cout << "object group before" << oid.to_string() << "\n";
    long old = input->tell();
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
//    oid.parse(input);
    std::cout << "object group after" << oid.to_string() << "\n";
    FileNode node = list.get_next_node(input);
    while (!list.is_end()) {
      switch (node.get_FileNodeID()) {
        case FileNode::GlobalIdTableStart2FND:
          std::cout << "GlobalIdTableStart2FND\n";
          GlobalIdentificationTable.clear();
          break;
        case FileNode::GlobalIdTableEntryFNDX:
          std::cout << "GlobalIdTableEntryFNDX\n";
          index = readU32 (input);
          temp.parse(input);
          GlobalIdentificationTable[index] = temp;
          break;
        case FileNode::DataSignatureGroupDefinitionFND:
          std::cout << "DataSignatureGroupDefinitionFND\n";
          DataSignatureGroup.parse(input);
          break;
        case FileNode::ObjectDeclaration2RefCountFND:
          std::cout << "ObjectDeclaration2RefCountFND\n";
          std::cout << "going to parse " << node.get_ref().get_location() << '\n';
//          node.parse_ObjectDeclaration2RefCountFND(input, ref);
//          object.parse(input, node.get_ref());
//          object_map[object.get_guid().to_string()] = object;
//          std::cout << object.to_string();
          break;
        case FileNode::ObjectGroupStartFND:
          std::cout << "ObjectGroupStartFND\n";
          oid.parse(input);
          break;
        case FileNode::ObjectGroupEndFND:
          std::cout << "ObjectGroupEndFND\n";
          DataSignatureGroup.zero();
          break;
        case FileNode::GlobalIdTableEndFNDX:
          std::cout << "GlobalIdTableEndFNDX\n";
          break;
        case FileNode::ObjectDeclarationFileData3RefCountFND:
          std::cout << "ObjectDeclarationFileData3RefCountFND\n";
//          parser.parse_ObjectDeclarationFileData3RefCountFND(input, ref);

          break;
        case FileNode::ReadOnlyObjectDeclaration2RefCountFND:
          std::cout << "ReadOnlyObjectDeclaration2RefCountFND\n";
//          parser.parse_ObjectDeclaration2RefCountFND(input, ref);
//          object.parse(input, node.get_ref());

//          object_map[object.get_guid().to_string()] = object;
          skip(input, 16);
          break;
        default:
          std::cout << "won't parse " << node.get_FileNodeID() << "?\n";
          break;
      }
      node = list.get_next_node(input);
    }
    std::cout << "end of object group";
    input->seek(old, librevenge::RVNG_SEEK_SET);
    return object_map;
  }

}

