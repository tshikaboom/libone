/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <iostream>
#include "ObjectSpace.h"
#include "libone_utils.h"
namespace libone {


  void ObjectSpace::list_parse(librevenge::RVNGInputStream *input, ExtendedGUID expected_guid, FileChunkReference ref) {
  Revision rev;
  FileNodeList list = FileNodeList (ref.get_location(), ref.get_size());
  ExtendedGUID temp;
  temp.zero();
  long old = input->tell();
  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
  std::cout << "list_parse\n" << list.to_string() << "\n";
  FileNode node = list.get_next_node(input);
  while (!list.is_end()) {
    switch (node.get_FileNodeID()) {
      case FileNode::ObjectSpaceManifestListStartFND:
        guid.parse(input);
        std::cout << "list_parse ObjectSpaceManifestListStartFND " << guid.to_string() << "\n";
        if (!guid.is_equal(expected_guid)) {
          if (!guid.is_equal(temp))
            std::cout << "pos " << input->tell() << " not a good guid! " << guid.to_string() << expected_guid.to_string();
        }
        break;
      case FileNode::RevisionManifestListReferenceFND:
        cout << "yes? RevisionManifestListReferenceFND\n";
        rev.list_parse(input, node.get_ref());
        break;
      default:
        cout << "what?\n";
        break;
      }
    node = list.get_next_node(input);
  }
  std::cout << "this is the end\n";
  input->seek(old, librevenge::RVNG_SEEK_SET);
  }
}


