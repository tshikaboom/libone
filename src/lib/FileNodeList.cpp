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
		next_fragment_location = input->tell() + size;
		uintMagic = readU64 (input, false);
		if (uintMagic != 0xa4567ab1f5f7f4c4) {
		  cout << "uintMagic not correct; position " << input->tell() << '\n';
		  end = true;
		}
		FileNodeListID = readU32 (input, false);
		nFragmentSequence = readU32 (input, false);
		std::cout << "fragment position end " << input->tell() << " nFragmentSequence " << nFragmentSequence << '\n';
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

	void FileNodeList::parse(librevenge::RVNGInputStream *input, uint32_t ExpectedFileNodeID) {
    long old = input->tell();
    int i = 0;
    FileNode node;
    input->seek(location, librevenge::RVNG_SEEK_SET);

    node = get_next_node (input);

	  if (ExpectedFileNodeID && ExpectedFileNodeID != node.get_FileNodeID()) {
		  cout << "Expected FileNodeID " << ExpectedFileNodeID << " in " << node.get_FileNodeID();
		  return;
	  }

    while (!is_end()) {
	    if ((i<=2) && (FileNodeListID == 0x10))
		    node.try_parse_ref(input, ExpectedFileNodeID);
      i++;
      node = get_next_node(input);
    }

    input->seek(old, librevenge::RVNG_SEEK_SET);
  }


	FileNode FileNodeList::get_next_node(librevenge::RVNGInputStream *input) {
	  FileNode node;
	  if (!header_parsed) {
	    parse_header(input);
	    header_parsed = true;
	  }
	  node.parse(input);
    std::cout << node.to_string();
	  std::cout << "next fragment? " << next_fragment_location << "\n";
	  if (node.isEnd()) {
      input->seek(next_fragment_location, librevenge::RVNG_SEEK_SET);
      std::cout << "what's up in here? " << input->tell();
      parse_header(input);
      node.parse(input);
	  }

	  return node;
	}

	bool FileNodeList::is_end() {
	  return end;
	}
}


