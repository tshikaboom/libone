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
#include "TransactionLogFragment.h"

namespace libone {

  libone::ExtendedGUID RootObject;
  libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();
  std::unordered_map<uint32_t, uint32_t> Transactions = std::unordered_map<uint32_t, uint32_t>{{{0, 0}}};

    OneNoteParser::OneNoteParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *const document) {

      long old;

      header.parse(input);

      input->seek(0, librevenge::RVNG_SEEK_SET);
      TransactionLogFragment log_fragment(header.cTransactionsInLog);

      ONE_DEBUG_MSG(("trying transactions, jumping to %ld\n", header.fcrTransactionLog.get_location()));
      old = input->tell();
      input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);
      log_fragment.parse(input);
      input->seek(old, librevenge::RVNG_SEEK_SET);
      ONE_DEBUG_MSG(("TransactionLog\n%s\n", log_fragment.to_string().c_str()));



      ONE_DEBUG_MSG(("test fileNodeList\n"));
      root_list.parse(input, header);
      ONE_DEBUG_MSG(("root object is %s\n", RootObject.to_string().c_str()));

      for (auto i: ObjectSpaces) {
        ONE_DEBUG_MSG(("object space %s\n", i.first.c_str()));
      }

      ObjectSpaces[RootObject.to_string()].to_document(document);

      ONE_DEBUG_MSG(("nothing broke!\n"));

    }

    //std::unordered_map<std::string ,libone::Object> RootObjectSpace = std::unordered_map<std::string ,libone::Object>();
//    libone::ExtendedGUID RootObject;

    std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces = std::unordered_map<std::string, libone::ObjectSpace>();
    // the string is the Object's guid

    std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

    std::unordered_map<std::string, struct FileData> filedata = std::unordered_map<std::string, struct FileData>();

}
