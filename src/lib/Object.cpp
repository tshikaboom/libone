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
#include "Object.h"
#include "ObjectSpaceStreams.h"
#include "JCID.h"

namespace libone {

  void Object::parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    parse_ObjectDeclaration2Body (input);
    ref_count = readU8 (input);
    std::cout << "object ref_count" << ref_count << "\n";
    parse_list(input, ref);
  }

  void Object::parse_ObjectDeclaration2Body(librevenge::RVNGInputStream *input) {
    CompactID temp;
    uint8_t temp2;
    temp.parse(input);
    guid = temp.to_EGUID();
    jcid = JCID(readU32 (input));
    std::cout << "object compact " << temp.to_string () << " eguid " << guid.to_string ();
    temp2 = readU8 (input);
    fHasOidReferences = (temp2 >> 7) & 0x01;
    fHasOsidReferences = (temp2 >> 6) & 0x01;
  }

  void Object::parse_3(librevenge::RVNGInputStream *input) {
    CompactID temp;
    GUID temp2;
    StringInStorageBuffer buf;
    StringInStorageBuffer buf2;
    temp.parse(input);
    guid = temp.to_EGUID();

    jcid = JCID(readU32(input));
    ref_count = readU8(input);

    buf.parse(input);
    buf2.parse(input);

    std::cout << "buf to string is " << buf.to_string() << "\n";

    // this is hardcoded but it works kinda
    if (buf.to_string().compare(0, 7, "<ifndf>") == 0) {
      temp2.from_string(buf.to_string ().substr(8, 36));
    }
  }


	bool Object::get_read_only() {
		return read_only;
	}

	void Object::set_read_only(bool new_) {
	  read_only = new_;
	}

	ExtendedGUID Object::get_guid() {
	  return guid;
  }

	std::string Object::to_string() {
	  std::stringstream stream;
	  stream << std::hex;
	  stream << "Object " << guid.to_string() << " ref_count " << ref_count << " jcid " << jcid.to_string() << "\n";
	  stream << "referencing " << object_refs.size() << " objects:\n";
	  for (auto &i: object_refs)
  	  stream << i.to_string() << "\n";
	  stream << "referencing " << object_spaces_refs.size() << " object spaces:\n";
	  for (auto &i: object_spaces_refs)
  	  stream << i.to_string() << "\n";
	  stream << "referencing " << context_refs.size() << " contexts:\n";
	  for (auto &i: context_refs)
  	  stream << i.to_string() << "\n";
//  	stream << set.to_string();
    return stream.str();
	}

	void Object::parse_list(librevenge::RVNGInputStream *input, FileChunkReference ref) {
  	ObjectSpaceStreamOfOIDs oids = ObjectSpaceStreamOfOIDs(guid);
	  ObjectSpaceStreamOfOSIDs osids = ObjectSpaceStreamOfOSIDs();
	  ObjectSpaceStreamOfContextIDs contexts = ObjectSpaceStreamOfContextIDs();
	  FileNodeList list(ref.get_location(), ref.get_size());
	  FileNode node;
	  long old = input->tell();
	  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);

	  object_refs = oids.parse(input);
	  if (!oids.get_B()) {
  	  object_spaces_refs = osids.parse(input);
	  }
	  if (oids.get_A()) {
	    context_refs = contexts.parse(input);
	  }

    for (auto &i: object_refs) {
      if (i.is_equal(guid))
        std::cout << "found duplicate, would remove nah?\n";
    }

    if (jcid.IsPropertySet())
      set.parse(input);

	  input->seek(old, librevenge::RVNG_SEEK_SET);
	}

  void Object::to_document(librevenge::RVNGDrawingInterface *document, std::unordered_map<std::string, Object> objects) {
    (void) document;
    (void) objects;
    std::cout << to_string() << "\n";
    for (auto &i: object_refs) {
      std::cout << "documenting " << i.to_string() << " yas?\n";
      objects[i.to_string()].to_document(document, objects);
    }

    switch (jcid.get_value()) {
      default:
        cout << "unknown JCID " << jcid.to_string() << " for object " << guid.to_string() << "\n";
        break;
    }
  }
}

