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
      FileNodeList list2(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());
      (void) store;
      long old = input->tell();
      input->seek(header.fcrFileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);

      /* Iterate twice through the list: the first time is to get the root
         object and the FileDataStores. Then parse the root object space. */
      while (!list.is_end()) {
      node = list.get_next_node(input);
        switch (node.get_FileNodeID()) {
           break;
          case FileNode::ObjectSpaceManifestRootFND:
            RootObject.parse(input);
            cout << "RootFileNodeList ObjectSpaceManifestRootFND " << RootObject.to_string() << "\n";
            break;
          case FileNode::FileDataStoreListReferenceFND:
            cout << "RootFileNodeList FileDataStoreObjectReferenceFND\n";
            store.parse(input, node.get_ref());
            break;
          case FileNode::ObjectSpaceManifestListReferenceFND: // parse this later
            std::cout << "RootFileNodeList ObjectSpaceManifestListReferenceFND skipping\n";
            node.skip_node(input);
            break;
          default:
            node.skip_node(input);
            std::cout << "RootFileNodeList unknown filenodeid " << std::hex << node.get_FileNodeID() << "position " << input->tell() << "\n";
            break;
        }
      }

      input->seek(header.fcrFileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);
      while (!list2.is_end()) {
        node = list2.get_next_node(input);
        switch (node.get_FileNodeID()) {
          case FileNode::ObjectSpaceManifestListReferenceFND:
  				  guid.parse(input);
				    cout << "RootFileNodeList2 ObjectSpaceManifestListReferenceFND " << guid.to_string () << "\n";
            ObjectSpaces.insert({ guid.to_string(), space});
            space.list_parse(input, guid, node.get_ref());
            break;
          case FileNode::ObjectSpaceManifestRootFND:
            node.skip_node(input);
            break;
          case FileNode::FileDataStoreListReferenceFND:
            node.skip_node(input);
            break;
          default:
            node.skip_node(input);
            std::cout << "RootFileNodeList2 unknown filenodeid " << std::hex << node.get_FileNodeID() << "position " << input->tell() << "\n";
            break;
          }
        }

      input->seek(old, librevenge::RVNG_SEEK_SET);
    }

}

