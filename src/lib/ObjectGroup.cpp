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

  std::unordered_map<std::string, libone::Object> ObjectGroup::list_parse(librevenge::RVNGInputStream *input, FileNodeChunkReference ref) {
    FileNodeList list (ref.get_location(), ref.get_size());
    std::unordered_map<std::string, libone::Object> object_map = std::unordered_map<std::string, libone::Object>();
    uint32_t index;
    GUID temp = GUID();
    oid.parse(input);
    ONE_DEBUG_MSG(("\n"));
    long old = input->tell();
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
//    oid.parse(input);
    ONE_DEBUG_MSG(("\n"));
    FileNode node = list.get_next_node(input);
    while (!list.is_end()) {
      switch (node.get_FileNodeID()) {
        case FileNode::GlobalIdTableStart2FND:
          ONE_DEBUG_MSG(("GlobalIdTableStart2FND\n"));
          GlobalIdentificationTable.clear();
          break;
        case FileNode::GlobalIdTableEntryFNDX:
          ONE_DEBUG_MSG(("GlobalIdTableEntryFNDX\n"));
          index = readU32 (input);
          temp.parse(input);
          GlobalIdentificationTable[index] = temp;
          break;
        case FileNode::DataSignatureGroupDefinitionFND:
          ONE_DEBUG_MSG(("DataSignatureGroupDefinitionFND\n"));
          DataSignatureGroup.parse(input);
          break;
        case FileNode::ObjectDeclaration2RefCountFND:
          ONE_DEBUG_MSG(("ObjectDeclaration2RefCountFND\n"));
          ONE_DEBUG_MSG(("going to parse %lu\n",node.get_fnd().get_location()));
//          node.parse_ObjectDeclaration2RefCountFND(input, ref);
//          object.parse(input, node.get_ref());
//          object_map[object.get_guid().to_string()] = object;
//          ONE_DEBUG_MSG((object.to_string()));
          break;
        case FileNode::ObjectGroupStartFND:
          ONE_DEBUG_MSG(("ObjectGroupStartFND\n"));
          oid.parse(input);
          break;
        case FileNode::ObjectGroupEndFND:
          ONE_DEBUG_MSG(("ObjectGroupEndFND\n"));
          DataSignatureGroup.zero();
          break;
        case FileNode::GlobalIdTableEndFNDX:
          ONE_DEBUG_MSG(("GlobalIdTableEndFNDX\n"));
          break;
        case FileNode::ObjectDeclarationFileData3RefCountFND:
          ONE_DEBUG_MSG(("ObjectDeclarationFileData3RefCountFND\n"));
//          parser.parse_ObjectDeclarationFileData3RefCountFND(input, ref);

          break;
        case FileNode::ReadOnlyObjectDeclaration2RefCountFND:
          ONE_DEBUG_MSG(("ReadOnlyObjectDeclaration2RefCountFND\n"));
//          parser.parse_ObjectDeclaration2RefCountFND(input, ref);
//          object.parse(input, node.get_ref());

//          object_map[object.get_guid().to_string()] = object;
          skip(input, 16);
          break;
        default:
          ONE_DEBUG_MSG(("?\n"));
          break;
      }
      node = list.get_next_node(input);
    }
    ONE_DEBUG_MSG(("end of object group"));
    input->seek(old, librevenge::RVNG_SEEK_SET);
    return object_map;
  }

}

