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

#include "libone_types.h"

#include "Revision.h"
#include "CompactID.h"

namespace libone {

  void Revision::list_parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    FileNodeList list(ref.get_location(), ref.get_size());
    FileNode node;
//    ObjectGroup group;
    long old = input->tell();
    ExtendedGUID temp;
//    Object object;
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    ONE_DEBUG_MSG(("trying to revision at %lu\n", input->tell()));

    while (!list.is_end()) {
    node = list.get_next_node(input);
        switch(node.get_FileNodeID()) {
          case FileNode::RevisionManifestListStartFND:
            ONE_DEBUG_MSG(("RevisionManifestListStartFND\n"));
            temp.parse(input);
            skip(input, 4);
            break;
          case FileNode::RevisionManifestStart4FND:
            ONE_DEBUG_MSG(("RevisionManifestStart4FND\n"));
            skip(input, 8);
            role = readU32(input, false);
            skip(input, 2);
            break;
          case FileNode::RevisionManifestStart7FND:
            ONE_DEBUG_MSG(("RevisionManifestStart7FND NOT 6\n"));
            break;
          case FileNode::RevisionManifestStart6FND:
            ONE_DEBUG_MSG(("RevisionManifestStart6FND\n"));
            guid.parse(input);
            dependent.parse(input);
            role = readU32(input, false);
            odcsDefault = readU16(input, false);
            break;
          case FileNode::ObjectGroupListReferenceFND:
            ONE_DEBUG_MSG(("ObjectGroupListReferenceFND\n"));
            objects = group.list_parse(input, node.get_ref());
            ONE_DEBUG_MSG(("got these objects:\n"));
            break;

          case FileNode::RevisionManifestEndFND:
            ONE_DEBUG_MSG(("RevisionManifestEndFND\n"));
            DataSignatureGroup.zero();
            GlobalIdentificationTable.clear();
            break;
          case FileNode::ObjectInfoDependencyOverridesFND:
            ONE_DEBUG_MSG(("ObjectInfoDependencyOverridesFND\n"));
            parse_dependencies (input, node);
            break;
          case FileNode::RootObjectReference3FND:
            temp.parse(input);
            root_objects[temp.to_string()] = readU32 (input);
            ONE_DEBUG_MSG(("RootObjectReference3FND: parsed %s = %u\n", temp.to_string().c_str(), root_objects[temp.to_string()]));
            break;
          default:
            ONE_DEBUG_MSG(("Revision.cpp filenodeid unknown %u\n", node.get_FileNodeID()));
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
    (void) n_8bitoverrides;
    (void) n_32bitoverrides;

    if (!node.get_ref().is_fcrNil()) {
      ONE_DEBUG_MSG((" for dependencies\n"));
      old = input->tell();
      input->seek(node.get_ref().get_location(), librevenge::RVNG_SEEK_SET);
    }

    n_8bitoverrides = readU32 (input, false);
    n_32bitoverrides = readU32(input, false);
    ONE_DEBUG_MSG((" 32bit overrides\n"));
    crc = readU32(input, false);
/*    for (i = 0; i < n_8bitoverrides; i++) {
      temp.parse(input);
      group.objects[temp.to_EGUID().to_string()].ref_count = readU8 (input);
      ONE_DEBUG_MSG(("\n"));
    }
    for (i = 0; i < n_32bitoverrides; i++) {
      temp.parse(input);
      group.objects[temp.to_EGUID().to_string()].ref_count = readU32(input);
      ONE_DEBUG_MSG(("\n"));
    } */

    if (!node.get_ref().is_fcrNil())
      input->seek(old, librevenge::RVNG_SEEK_SET);

  }

  void Revision::to_document(librevenge::RVNGDrawingInterface *document) {
    (void) document;

    for (auto i: root_objects) {
      ONE_DEBUG_MSG(("\n"));
        //objects[i.first].to_document(document, objects);
    }

  }

}

