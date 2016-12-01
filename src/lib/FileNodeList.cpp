/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeList.h"
#include "libone_utils.h"
using namespace std;
using std::string;

namespace libone {

  FileNodeList::FileNodeList(uint64_t new_location, uint64_t new_size) {
    location = new_location;
    size = new_size;
  }

  void FileNodeList::parse_header(librevenge::RVNGInputStream *input) {
		std::cout << "fragment position begin " << std::hex << input->tell() << '\n';
		next_fragment_location = input->tell();
		uintMagic = readU64 (input, false);
		if (uintMagic != 0xa4567ab1f5f7f4c4) {
		  cout << "uintMagic not correct; position " << input->tell() << '\n';
		}
		FileNodeListID = readU32 (input, false);
		nFragmentSequence = readU32 (input, false);
		std::cout << "fragment position end " << input->tell() << " nFragmentSequence " << nFragmentSequence << '\n';
  }

	void FileNodeList::parse(librevenge::RVNGInputStream *input, uint32_t ExpectedFileNodeID) {
		FileNode node;
		uint64_t old_fragment_sequence = 0;
		FileChunkReference64x32 next_frag;
		bool list_end = false;

	  old_seek = input->tell();
	  input->seek(location, librevenge::RVNG_SEEK_SET);



	  int i=0;
		while (!list_end) {
		  parse_header(input);
		  node.parse(input);
		  if (ExpectedFileNodeID && ExpectedFileNodeID != node.get_FileNodeID()) {
			  cout << "Expected FileNodeID " << ExpectedFileNodeID << " in " << node.get_FileNodeID();
			  return;
		  }
	    old_fragment_sequence = nFragmentSequence;
	    while (!node.isEnd()) {
		    rgFileNodes.push_back(node);
		    i++;
		    if ((i<=2) && (FileNodeListID == 0x10))
			    node.try_parse_ref(input, ExpectedFileNodeID);
		    node.parse(input);
	    }
      std::cout << "wazzzaaaaa\n";
      // seek out next fragment in the list if any
      while ((i = readU8(input, false)) == 0) {}
      input->seek(-1, librevenge::RVNG_SEEK_CUR);

      next_frag.parse(input);
		  if (next_frag.is_nil()) {
		    std::cout << "done parsing this list\n";
        list_end = true;
        break;
      }
      std::cout << "next fragment " << next_frag.get_location() << "\n";
      input->seek(next_frag.get_location(), librevenge::RVNG_SEEK_SET);
      parse_header(input);
      if (nFragmentSequence != old_fragment_sequence+1) {
        cout << "fragments not correct, expected " << old_fragment_sequence+1 << " got " << nFragmentSequence << "\n";
        break;
      }
      old_fragment_sequence++;

    }
    footer = readU64 (input);
    std::cout << footer << "\n";
    input->seek(old_seek, librevenge::RVNG_SEEK_SET);
    old_seek = 0;
	}

	string FileNodeList::to_string() {
		std::stringstream stream;
		stream << std::hex << "uintMagic " << uintMagic << '\n';
		stream << std::dec << "FileNodeListID " << FileNodeListID << '\n';
		stream << "nFragmentSequence " << nFragmentSequence << '\n';
		for (FileNode i: rgFileNodes)
			stream << i.to_string() << '\n';
		return stream.str();
	}

	void FileNodeList::set_size(uint64_t new_size) {
	  size = new_size;
	}

	FileNode FileNodeList::get_next_node(librevenge::RVNGInputStream *input) {
	  FileNode node;
	  if (!header_parsed) {
	    parse_header(input);
	    header_parsed = true;
	  }
	  node.parse(input);
	  next_fragment_location += node.get_Size(); /*
	  if (node.isEnd()) {
      next_fragment_location

	  }
	  */
	  return node;
	}
}


