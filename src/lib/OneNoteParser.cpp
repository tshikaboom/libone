/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "OneNoteParser.h"

namespace libone {
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
