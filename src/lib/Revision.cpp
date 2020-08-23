/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include <iomanip>
#include "libone_utils.h"

#include "libone_types.h"

#include "Revision.h"
#include "CompactID.h"

namespace libone
{

void Revision::list_parse(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference ref)
{
  FileNodeList list(ref.stp(), ref.cb());
  FileNode node;
//    ObjectGroup group;
  ExtendedGUID temp;
//    Object object;
  input->seek(ref.stp(), librevenge::RVNG_SEEK_SET);
  ONE_DEBUG_MSG(("trying to revision at %lu\n", input->tell()));

  list.parse(input);

}

std::string Revision::to_string()
{
  std::stringstream stream;
  stream << "Revision guid " << guid.to_string() << "\n";
  stream << "Revision dep " << dependent.to_string() << "\n";
  stream << "Revision root " << root_object.to_string() << "\n";
  stream << "Revision role " << role << "\n";
  stream << "Revision context " << context.to_string() << "\n";


  return stream.str();
}

void Revision::parse_dependencies(const libone::RVNGInputStreamPtr_t &input, FileNode node)
{
  CompactID temp;
  uint32_t n_8bitoverrides;
  uint32_t n_32bitoverrides;
  uint32_t crc;
  uint32_t i = 0;
  long old = -1;

  (void) crc;
  (void) i;
  (void) n_8bitoverrides;
  (void) n_32bitoverrides;

  if (!node.get_fncr().is_fcrNil())
  {
    ONE_DEBUG_MSG((" for dependencies\n"));
    old = input->tell();
    input->seek(node.get_fncr().stp(), librevenge::RVNG_SEEK_SET);
  }

  n_8bitoverrides = readU32(input, false);
  n_32bitoverrides = readU32(input, false);
  ONE_DEBUG_MSG((" 32bit overrides\n"));
  crc = readU32(input, false);
  /*    for (i = 0; i < n_8bitoverrides; i++) {
        temp.parse(input);
        group.objects[temp.to_EGUID().to_string()].ref_count = readU8 (input);
        ONE_DEBUG_MSG(("\n"));
      }
      for (i = 0; i < n_32bitoverrides; i++) {
        temp.parse(input);
        group.objects[temp.to_EGUID().to_string()].ref_count = readU32(input);
        ONE_DEBUG_MSG(("\n"));
      } */

  if (!node.get_fncr().is_fcrNil())
    input->seek(old, librevenge::RVNG_SEEK_SET);

}

void Revision::to_document(librevenge::RVNGDrawingInterface *document)
{
  (void) document;

  for (auto i: root_objects)
  {
    ONE_DEBUG_MSG(("\n"));
    //objects[i.first].to_document(document, objects);
  }

}

}

