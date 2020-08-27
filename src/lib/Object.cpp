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
#include "libone_types.h"
#include "libone_utils.h"
#include "Object.h"
#include "ObjectSpaceStreams.h"

namespace libone
{

Object::Object(const libone::RVNGInputStreamPtr_t &input, struct object_header _header)
{
  guid = _header.guid;
  jcid = _header.jcid;
  ref_count = _header.ref_count;
  fHasOidReferences = _header.fHasOidReferences;
  fHasOsidReferences = _header.fHasOsidReferences;
  body = _header.body;
  parse_list(input, body);
}


bool Object::get_read_only()
{
  return read_only;
}

void Object::set_read_only(bool new_)
{
  read_only = new_;
}

ExtendedGUID Object::get_guid()
{
  return guid;
}

std::string Object::to_string()
{
  std::stringstream stream;
  stream << std::hex;
  stream << "Object " << guid.to_string() << " ref_count " << ref_count << " jcid " << jcid.to_string() << "\n";
  if (object_refs.size())
  {
    stream << "referencing " << object_refs.size() << " objects:\n";
    for (auto &i: object_refs)
      stream << i.to_string() << "\n";
  }
  if (object_spaces_refs.size())
  {
    stream << "referencing " << object_spaces_refs.size() << " object spaces:\n";
    for (auto &i: object_spaces_refs)
      stream << i.to_string() << "\n";
  }
  if (context_refs.size())
  {
    stream << "referencing " << context_refs.size() << " contexts:\n";
    for (auto &i: context_refs)
      stream << i.to_string() << "\n";
  }


//  	stream << set.to_string();
  return stream.str();
}



void Object::to_document(librevenge::RVNGDrawingInterface *document, std::unordered_map<std::string, Object> objects)
{
  (void) document;
  (void) objects;
  ONE_DEBUG_MSG(("\n"));
//    for (auto &i: object_refs) {
  ONE_DEBUG_MSG((" yas?\n"));
//      objects[i.to_string()].to_document(document, objects);
//    }

  switch (jcid.get_value())
  {

  default:
    ONE_DEBUG_MSG(("unknown JCID %s for object %s\n", jcid.to_string().c_str(), guid.to_string().c_str()));
    break;
  }
}

void Object::parse_list(const libone::RVNGInputStreamPtr_t &input, FileNodeChunkReference ref)
{
  ObjectSpaceStreamOfOIDs oids = ObjectSpaceStreamOfOIDs(guid);
  ObjectSpaceStreamOfOSIDs osids = ObjectSpaceStreamOfOSIDs();
  ObjectSpaceStreamOfContextIDs contexts = ObjectSpaceStreamOfContextIDs();
  FileNodeList list(ref.stp(), ref.cb());
  FileNode node;

  if (jcid.get_value() == 0) return;

  long old = input->tell();
  input->seek(ref.stp(), librevenge::RVNG_SEEK_SET);

  object_refs = oids.parse(input);
  if (!oids.get_B())
  {
    object_spaces_refs = osids.parse(input);
  }
  if (oids.get_A())
  {
    context_refs = contexts.parse(input);
  }

  for (auto &i: object_refs)
  {
    if (i.is_equal(guid))
    {
      ONE_DEBUG_MSG(("found duplicate, would remove nah?\n"));
    }
  }

  if (jcid.IsPropertySet())
    set.parse(input);

  input->seek(old, librevenge::RVNG_SEEK_SET);
}
}

