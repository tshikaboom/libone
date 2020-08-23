/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "libone_types.h"
#include "ObjectGroup.h"

namespace libone
{

std::unordered_map<std::string, libone::Object> ObjectGroup::list_parse(libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference ref)
{
  FileNodeList list(ref.stp(), ref.cb());
  std::unordered_map<std::string, libone::Object> object_map = std::unordered_map<std::string, libone::Object>();
  GUID temp = GUID();
  DBMSG << "GUID " << temp.to_string();
  oid.parse(input);
  list.parse(input);
  ONE_DEBUG_MSG(("end of object group"));
  return object_map;
}

}

