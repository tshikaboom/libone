/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iomanip>
#include <iostream>
#include "libone_utils.h"
#include "Object.h"
#include "ObjectSpaceStreams.h"
#include "JCID.h"

namespace libone {

  void Object::parse(librevenge::RVNGInputStream *input, FileChunkReference ref) {
    CompactID temp;
    uint8_t temp2;
    temp.parse(input);
    guid = temp.to_EGUID();
    jcid = JCID(readU32(input));
    std::cout << "object compact " << temp.to_string () << " eguid " << guid.to_string ();
    temp2 = readU8 (input);
    fHasOsidReferences = temp2 >> 7;
    fHasOidReferences = (temp2 >> 6) & 1;
    ref_count = readU8 (input);
    std::cout << "object ref_count" << ref_count << "\n";
    parse_list(input, ref);
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
	  stream << "Object " << guid.to_string() << " ref_count " << ref_count << " jcid " << jcid.get_value() << "\n";
	  stream << "referencing " << oids.get_list().size() << " objects:\n";
	  stream << oids.to_string() << "\n";
	  stream << "referencing " << osids.get_list().size() << " object spaces:\n";
	  stream << osids.to_string() << "\n";
	  stream << "referencing " << contexts.get_list().size() << " contexts:\n";
	  stream << contexts.to_string() << "\n";
    return stream.str();
	}

	void Object::parse_list(librevenge::RVNGInputStream *input, FileChunkReference ref) {
	  FileNodeList list(ref.get_location(), ref.get_size());
	  FileNode node;
	  long old = input->tell();
	  input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
	  oids.parse(input);
//	  std::cout << oids.to_string();
	  if (!oids.get_B()) {
	    osids.parse(input);
//	    std::cout << osids.to_string();
	  }
	  if (oids.get_A()) {
      contexts.parse(input);
//      std::cout << contexts.to_string();
	  }

	  object_refs = oids.get_list();
	  context_refs = contexts.get_list();
	  object_spaces_refs = osids.get_list();

	  input->seek(old, librevenge::RVNG_SEEK_SET);
	}
}

