/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include <iomanip>
#include "libone_utils.h"

namespace libone {

  void Revision::list_parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    FileNodeList list(ref.get_location(), ref.get_size());
    FileNode node;
//    ObjectGroup group;
    long old = input->tell();
    ExtendedGUID temp;
    Object object;
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    cout << "trying to revision at " << input->tell() << "\n";

    while (!list.is_end()) {
    node = list.get_next_node(input);
//      std::cout << node.to_string ();
        switch(node.get_FileNodeID()) {
          case FileNode::RevisionManifestListStartFND:
            cout << "RevisionManifestListStartFND\n";
            temp.parse(input);
            skip(input, 4);
            break;
          case FileNode::RevisionManifestStart4FND:
            cout << "RevisionManifestStart4FND\n";
            skip(input, 8);
            role = readU32(input, false);
            skip(input, 2);
            break;
          case FileNode::RevisionManifestStart7FND:
            cout << "RevisionManifestStart7FND NOT 6\n";
            break;
          case FileNode::RevisionManifestStart6FND:
            cout << "RevisionManifestStart6FND\n";
            guid.parse(input);
            dependent.parse(input);
            role = readU32(input, false);
            odcsDefault = readU16(input, false);
            std::cout << to_string();
            break;
          case FileNode::ObjectGroupListReferenceFND:
            cout << "ObjectGroupListReferenceFND\n";
            objects = group.list_parse(input, node.get_ref());
            std::cout << "got these objects:\n";
            for (auto i : objects) {
              std::cout << i.first << " " << i.second.to_string() << "\n";
            }
            break;

          case FileNode::RevisionManifestEndFND:
            std::cout << "RevisionManifestEndFND\n";
            DataSignatureGroup.zero();
            GlobalIdentificationTable.clear();
            break;
          case FileNode::ObjectInfoDependencyOverridesFND:
            cout << "ObjectInfoDependencyOverridesFND\n";
            parse_dependencies (input, node);
            break;
          case FileNode::RootObjectReference3FND:
            temp.parse(input);
            root_objects[temp.to_string()] = readU32 (input);
            std::cout << "RootObjectReference3FND: parsed" << temp.to_string () << " = " << root_objects[temp.to_string()] << "\n";
            break;
          default:
            cout << "Revision.cpp filenodeid unknown " << node.get_FileNodeID() << "\n";
            break;
        }
        if (node.get_FileNodeID() == FileNode::RevisionManifestStart7FND)
          context.parse(input);
    }
    input->seek(old, librevenge::RVNG_SEEK_SET);
  }

  std::string Revision::to_string() {
    std::stringstream stream;
    stream << "Revision guid " << guid.to_string() << "\n";
    stream << "Revision dep " << dependent.to_string() << "\n";
    stream << "Revision root " << root_object.to_string() << "\n";
    stream << "Revision role " << role << "\n";
    stream << "Revision context " << context.to_string() << "\n";


    return stream.str();
  }

  void Revision::parse_dependencies(librevenge::RVNGInputStream *input, FileNode node) {
    CompactID temp;
    uint32_t n_8bitoverrides;
    uint32_t n_32bitoverrides;
    uint32_t crc;
    uint32_t i = 0;
    long old = -1;

    (void) crc;
    (void) i;

    if (!node.get_ref().is_fcrNil()) {
      std::cout << "seeking to " << node.get_ref().get_location() << " for dependencies\n";
      old = input->tell();
      input->seek(node.get_ref().get_location(), librevenge::RVNG_SEEK_SET);
    }

    n_8bitoverrides = readU32 (input, false);
    n_32bitoverrides = readU32(input, false);
    std::cout << (unsigned) n_8bitoverrides << " 8bit overrides, " << n_32bitoverrides << " 32bit overrides\n";
    crc = readU32(input, false);
/*    for (i = 0; i < n_8bitoverrides; i++) {
      temp.parse(input);
      group.objects[temp.to_EGUID().to_string()].ref_count = readU8 (input);
      std::cout << "updated refcount for " << temp.to_EGUID().to_string() << "\n";
    }
    for (i = 0; i < n_32bitoverrides; i++) {
      temp.parse(input);
      group.objects[temp.to_EGUID().to_string()].ref_count = readU32(input);
      std::cout << "updated refcount for " << temp.to_EGUID().to_string() << "\n";
    } */

    if (!node.get_ref().is_fcrNil())
      input->seek(old, librevenge::RVNG_SEEK_SET);

  }

  void Revision::to_document(librevenge::RVNGDrawingInterface *document) {
    (void) document;

    for (auto i: root_objects) {
      std::cout << "revision root object " << i.first << " role " << i.second << "\n";
        objects[i.first].to_document(document, objects);
    }

  }

}

