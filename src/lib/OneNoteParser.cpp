/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "libone_utils.h"
#include "libone_types.h"
#include "OneNoteParser.h"
#include "Object.h"
#include "FileDataStore.h"

namespace libone {

  libone::ExtendedGUID RootObject;
  libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();

    OneNoteParser::OneNoteParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *const document) {

      long old;

      header.parse(input);

      input->seek(0, librevenge::RVNG_SEEK_SET);

      ONE_DEBUG_MSG(("trying transactions, jumping to %ld\n", header.fcrTransactionLog.get_location()));
      old = input->tell();
      input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);
      input->seek(old, librevenge::RVNG_SEEK_SET);



      ONE_DEBUG_MSG(("test fileNodeList\n"));
      parse_root_file_node_list(input);
      ONE_DEBUG_MSG(("root object is %s\n", RootObject.to_string().c_str()));

      for (auto i: ObjectSpaces) {
        ONE_DEBUG_MSG(("object space %s\n", i.first.c_str()));
      }

      parse_transactions(input);

      ObjectSpaces[RootObject.to_string()].to_document(document);

      ONE_DEBUG_MSG(("nothing broke!\n"));

    }

    void OneNoteParser::parse_root_file_node_list(librevenge::RVNGInputStream *input) {
      FileNode node;
      ExtendedGUID guid;
      ObjectSpace space;
      FileDataStore store;
      FileNodeList list(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());
      FileNodeList list2(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());
      (void) store;

      input->seek(header.fcrFileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);

      /* Iterate twice through the list: the first time is to get the root
         object and the FileDataStores. Then parse the root object space. */
      while (!list.is_end()) {
      node = list.get_next_node(input);
        switch (node.get_FileNodeID()) {
           break;
          case FileNode::ObjectSpaceManifestRootFND:
            RootObject.parse(input);
            ONE_DEBUG_MSG(("RootFileNodeList ObjectSpaceManifestRootFND\n"));
            break;
          case FileNode::FileDataStoreListReferenceFND:
            ONE_DEBUG_MSG(("RootFileNodeList FileDataStoreListReferenceFND"));
            store.parse(input, node.get_fnd());
            break;
          case FileNode::ObjectSpaceManifestListReferenceFND: // parse this later
            ONE_DEBUG_MSG(("RootFileNodeList ObjectSpaceManifestListReferenceFND skipping\n"));
            node.skip_node(input);
            break;
          default:
            node.skip_node(input);
            ONE_DEBUG_MSG(("\n"));
            break;
        }
      }

      input->seek(header.fcrFileNodeListRoot.get_location(), librevenge::RVNG_SEEK_SET);
      while (!list2.is_end()) {
        node = list2.get_next_node(input);
        switch (node.get_FileNodeID()) {
          case FileNode::ObjectSpaceManifestListReferenceFND:
  				  guid.parse(input);
  				  if (guid.is_equal(RootObject)) {
				      ONE_DEBUG_MSG(("RootFileNodeList2 parsing root object space\n"));
				      } else {
				        ONE_DEBUG_MSG(("RootFileNodeList2 parsing object space %s\n", guid.to_string().c_str()));
				      }
              space.list_parse(input, guid, node.get_fnd());
              ObjectSpaces[guid.to_string()] = space;
            break;
          case FileNode::ObjectSpaceManifestRootFND:
            node.skip_node(input);
            break;
          case FileNode::FileDataStoreListReferenceFND:
            node.skip_node(input);
            break;
          default:
            node.skip_node(input);
            ONE_DEBUG_MSG(("\n"));
            break;
          }
        }
    }


    void OneNoteParser::parse_transactions(librevenge::RVNGInputStream *input) {
      uint32_t total_transactions = header.cTransactionsInLog;
      uint32_t transactions = 0;
      TransactionEntry entry;
      FileChunkReference nextFragment = FileChunkReference(FileChunkReferenceSize::Size64x32);

      input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);

      entry.parse(input);
      while (transactions < total_transactions) {
        entry.parse(input);
        DBMSG << "parsed transaction " << entry.to_string() << "\n";
        if (entry.get_srcID() != 0x00000001) {
          header.Transactions.push_back(entry);
        }
        else {
          transactions++;
          ONE_DEBUG_MSG(("parsed %d transactions\n", transactions));
        }
      }
//      ONE_DEBUG_MSG << "position " << input->tell() << " before next fragment\n";
      nextFragment.parse(input);
      ONE_DEBUG_MSG(("%s position %ld\n", nextFragment.to_string().c_str(), input->tell()));
//      ONE_DEBUG_MSG << "last entry " << entry.to_string () << "\n";
      ONE_DEBUG_MSG(("parsed %d, total %d\n", transactions, total_transactions));
    }

    std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

    std::unordered_map<std::string, struct FileData> filedata = std::unordered_map<std::string, struct FileData>();

}
