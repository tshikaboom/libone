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

#include "ObjectSpace.h"

namespace libone {


  void ObjectSpace::list_parse(librevenge::RVNGInputStream *input, ExtendedGUID expected_guid, FileNodeChunkReference ref) {
    Revision rev;
    FileNode node;
    FileNode node2;
    FileNodeList list = FileNodeList (ref.get_location(), ref.get_size());
    ExtendedGUID temp;
    temp.zero();
    long old = input->tell();
    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    while (!list.is_end()) {
    node = list.get_next_node(input);
      switch (node.get_FileNodeID()) {
        case FileNode::ObjectSpaceManifestListStartFND:
          guid.parse(input);
          ONE_DEBUG_MSG(("\n"));
          if (!guid.is_equal(expected_guid)) {
            if (!guid.is_equal(temp)) {
              ONE_DEBUG_MSG((" not a good guid! %s expected %s\n", guid.to_string().c_str(), expected_guid.to_string().c_str()));
	    }
          }
          break;
        case FileNode::RevisionManifestListReferenceFND:
          ONE_DEBUG_MSG(("RevisionManifestListReferenceFND\n"));
          node2 = node;
          node.skip_node(input);
          break;
        default:
          ONE_DEBUG_MSG(("ObjectSpace unknown filenodeid %d\n", node.get_FileNodeID()));
          break;
        }
    }

    ONE_DEBUG_MSG(("trying to parse last revision\n"));
    rev.list_parse(input, node2.get_fnd());
    revisions.push_back(rev);
    ONE_DEBUG_MSG(("\n"));
    input->seek(old, librevenge::RVNG_SEEK_SET);
  }

  void ObjectSpace::to_document(librevenge::RVNGDrawingInterface *document) {
    (void) document;
    ONE_DEBUG_MSG(("\n"));
    for (auto i : revisions) {
      i.to_document(document);
    }
    ONE_DEBUG_MSG(("done?\n"));
  }

  std::string ObjectSpace::to_string() {
    std::stringstream stream;
    stream << "ObjectSpace " << guid.to_string() << " context " << context.to_string () << " containing " << revisions.size() << " revisions\n";
    return stream.str();
  }
}


