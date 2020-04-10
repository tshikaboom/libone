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
      root_list.parse(input, header);
      ONE_DEBUG_MSG(("root object is %s\n", RootObject.to_string().c_str()));

      for (auto i: ObjectSpaces) {
        ONE_DEBUG_MSG(("object space %s\n", i.first.c_str()));
      }

      parse_transactions(input);

      ObjectSpaces[RootObject.to_string()].to_document(document);

      ONE_DEBUG_MSG(("nothing broke!\n"));

    }



    void OneNoteParser::parse_transactions(librevenge::RVNGInputStream *input) {
      uint32_t total_transactions = header.cTransactionsInLog;
      uint32_t transactions = 0;
      TransactionEntry entry;
      FileChunkReference nextFragment = FileChunkReference();

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
      nextFragment.parse(input, FileChunkReference::mode::Type64x32);
      ONE_DEBUG_MSG(("%s position %ld\n", nextFragment.to_string().c_str(), input->tell()));
//      ONE_DEBUG_MSG << "last entry " << entry.to_string () << "\n";
      ONE_DEBUG_MSG(("parsed %d, total %d\n", transactions, total_transactions));
    }

    //std::unordered_map<std::string ,libone::Object> RootObjectSpace = std::unordered_map<std::string ,libone::Object>();
//    libone::ExtendedGUID RootObject;

    std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces = std::unordered_map<std::string, libone::ObjectSpace>();
    // the string is the Object's guid

    std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

    std::unordered_map<std::string, struct FileData> filedata = std::unordered_map<std::string, struct FileData>();

}
