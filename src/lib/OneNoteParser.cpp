/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "libone_types.h"
#include "OneNoteParser.h"

namespace libone {

    OneNoteParser::OneNoteParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *const document) {
      RootFileNodeList root_list;
      long old;

      input->seek(0, librevenge::RVNG_SEEK_SET);
      TransactionLogFragment log_fragment(header.cTransactionsInLog);

      std::cout << "trying transactions, jumping to " << header.fcrTransactionLog.get_location() << '\n';
      old = input->tell();
      input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);
      log_fragment.parse(input);
      input->seek(old, librevenge::RVNG_SEEK_SET);
      std::cout << "TransactionLog" << '\n' << log_fragment.to_string() << '\n';




      std::cout << "test fileNodeList " << '\n';
      root_list.parse(input);
      std::cout << "root object is " << RootObject.to_string() << "\n";

      for (auto i: ObjectSpaces)
        std::cout << "object space " << i.first << "\n";

      ObjectSpaces[RootObject.to_string()].to_document(document);

      std::cout << "nothing broke!\n";

    }

    //std::unordered_map<std::string ,libone::Object> RootObjectSpace = std::unordered_map<std::string ,libone::Object>();
    libone::ExtendedGUID RootObject;

    std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces = std::unordered_map<std::string, libone::ObjectSpace>();
    // the string is the Object's guid

    std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

    std::unordered_map<uint32_t, uint32_t> Transactions = std::unordered_map<uint32_t, uint32_t>({{0, 0}});

    libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();
    libone::Header header;

    std::unordered_map<std::string, struct FileData> filedata = std::unordered_map<std::string, struct FileData>();

}
