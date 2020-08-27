/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_OBJECT_H
#define INCLUDED_LIBONE_OBJECT_H

#include <string>
#include <librevenge-stream/librevenge-stream.h>
#include <librevenge/librevenge.h>
#include <unordered_map>

#include "ExtendedGUID.h"
#include "JCID.h"
#include "FileNodeList.h"
#include "FileNodeChunkReference.h"
#include "PropertySet.h"

namespace libone
{

struct object_header
{
  ExtendedGUID guid = ExtendedGUID();
  FileNodeChunkReference body = FileNodeChunkReference(StpFormat::stp_invalid, CbFormat::cb_invalid);
  JCID jcid = JCID(0);
  uint32_t ref_count = 0;
  uint16_t fHasOidReferences = 0;
  uint16_t fHasOsidReferences = 0;
};

class Object
{

public:
  Object(const libone::RVNGInputStreamPtr_t &input, struct object_header _header);
  bool get_read_only();
  void set_read_only(bool new_);
  ExtendedGUID get_guid();
  std::string to_string();
  void to_document(librevenge::RVNGDrawingInterface *document, std::unordered_map<std::string, Object> objects);

protected:
  void parse_list(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference ref);

private:
  FileNodeChunkReference body = FileNodeChunkReference(StpFormat::stp_invalid, CbFormat::cb_invalid);
  PropertySet set = PropertySet();

  bool read_only = false;
  ExtendedGUID guid = ExtendedGUID();
  JCID jcid = JCID(0);
  uint32_t ref_count = 0;
  uint16_t fHasOidReferences = 0;
  uint16_t fHasOsidReferences = 0;
  std::vector<ExtendedGUID> object_refs = std::vector<ExtendedGUID>();
  std::vector<ExtendedGUID> context_refs = std::vector<ExtendedGUID>();
  std::vector<ExtendedGUID> object_spaces_refs = std::vector<ExtendedGUID>();

};

}

#endif
