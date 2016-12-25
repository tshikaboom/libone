/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <cstdint>
#include <iostream>
#include <librevenge-stream/librevenge-stream.h>
#include "RootFileNodeList.h"

namespace libone {

    void RootFileNodeList::parse(librevenge::RVNGInputStream *input) {
      FileNode node;
      ExtendedGUID guid;
      ObjectSpace space;
      FileDataStore store;
      FileNodeList list(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());

      long old = input->tell();
      input->seek(header.fcrFileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);



      while (!list.is_end()) {
      node = list.get_next_node(input);
        switch (node.get_FileNodeID()) {
          case FileNode::ObjectSpaceManifestListReferenceFND:
				    guid.parse(input);
				    cout << "ObjectSpaceManifestListReferenceFND " << guid.to_string () << "\n";
            ObjectSpaces.insert({ guid.to_string(), space});
            space.list_parse(input, guid, node.get_ref());
            break;
          case FileNode::ObjectSpaceManifestRootFND:
            RootObject.parse(input);
            cout << "ObjectSpaceManifestRootFND " << RootObject.to_string() << "\n";
            break;
          case FileNode::FileDataStoreListReferenceFND:
            cout << "FileDataStoreObjectReferenceFND\n";
            store.parse(input, node.get_ref());
            break;
          default:
            std::cout << __FUNCTION__ << " unknown filenodeid " << std::hex << node.get_FileNodeID() << "\n";
            break;
        }
      }

      input->seek(old, librevenge::RVNG_SEEK_SET);
    }

}

