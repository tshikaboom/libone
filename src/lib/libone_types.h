/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#ifndef INCLUDED_LIBONE_TYPES_H
#define INCLUDED_LIBONE_TYPES_H

#include <vector>
#include <unordered_map>
#include "ExtendedGUID.h"
#include "ObjectSpace.h"
#include "Header.h"

namespace libone {

//extern std::unordered_map<std::string ,libone::Object> RootObjectSpace;
extern libone::ExtendedGUID RootObject;

extern std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces;
// the string is the Object's guid

extern std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable;

extern libone::ExtendedGUID DataSignatureGroup;

extern std::unordered_map<uint32_t, uint32_t> Transactions;

struct FileData {
  long location = 0;
  uint64_t length = 0;
};


extern std::unordered_map<std::string, struct FileData> filedata;



}

#endif
