/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_OBJECTSPACE_H
#define INCLUDED_LIBONE_OBJECTSPACE_H

#include "Revision.h"
#include "Object.h"
#include "FileChunkReference.h"
#include "FileNodeList.h"
#include "ExtendedGUID.h"
#include <sstream>
#include <unordered_map>
#include <librevenge-stream/librevenge-stream.h>

namespace libone
{

class ObjectSpace
{
public:
  ObjectSpace();
  void parse(const libone::RVNGInputStreamPtr_t &input, FileNode &node);
  void list_parse(const libone::RVNGInputStreamPtr_t &input, ExtendedGUID guid, FileNodeChunkReference ref); // Assume we're at the beginning of a FileNode list
//    std::unordered_map<std::string, libone::Object> ObjectMap = std::unordered_map<std::string, libone::Object>();
  std::unordered_map<std::string, libone::Revision> RevisionMap = std::unordered_map<std::string, libone::Revision>();
  void to_document(librevenge::RVNGDrawingInterface *document);
  std::string to_string();

private:
  uint64_t m_offset = 0;
  FileNodeChunkReference m_fnd_list_ref = FileNodeChunkReference(StpFormat::stp_invalid, CbFormat::cb_invalid);
  ExtendedGUID guid = ExtendedGUID();
  ExtendedGUID context = ExtendedGUID();
  std::vector<Revision> revisions = std::vector<Revision>();
};

}

#endif
