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

  Revision rev;
  void ObjectSpace::list_parse(librevenge::RVNGInputStream *input, ExtendedGUID expected_guid, FileChunkReference64 ref) {
  FileNodeList list;
  FileNode node;
  ExtendedGUID temp;
  temp.zero();
  long old = input->tell();
  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
  list.parse_header(input);
  std::cout << "list_parse\n" << list.to_string() << "\n";
  node.parse(input);
  while (!node.isEnd()) {
    switch (node.get_FileNodeID()) {
      case FileNodeDescriptor::ObjectSpaceManifestListStartFND:
        std::cout << "list_parse ObjectSpaceManifestListStartFND\n";
        guid.parse(input);
        if (!guid.is_equal(expected_guid)) {
          if (guid.is_equal(temp))
            std::cout << "pos " << input->tell() << " not a good guid! " << guid.to_string() << expected_guid.to_string();
        }
        break;
      case FileNodeDescriptor::RevisionManifestListReferenceFND:
        rev.list_parse(input, node.get_ref());
        break;
      default:
        cout << "what?\n";
        break;
      }
    node.parse(input);
  }

  input->seek(old, librevenge::RVNG_SEEK_SET);
  }
}


