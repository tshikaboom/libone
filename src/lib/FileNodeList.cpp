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

#include "libone_types.h"

namespace libone {

  FileNodeList::FileNodeList(uint64_t new_location, uint64_t new_size) {
    location = new_location;
    size = new_size;
  }

  void FileNodeList::parse_header(librevenge::RVNGInputStream *input) {
    uint32_t expected_fragment_sequence;
    bool found = false;
//		ONE_DEBUG_MSG(("fragment position begin ")) << std::hex << input->tell() << '\n';
		next_fragment_location = input->tell() + size - 8 - 12;
//		ONE_DEBUG_MSG(("\n"));
		uintMagic = readU64 (input, false);
		if (uintMagic != 0xa4567ab1f5f7f4c4) {
		  ONE_DEBUG_MSG(("uintMagic not correct; position %ld\n", input->tell()));
		  end = true;
		}
		FileNodeListID = readU32 (input, false);/*
		for (auto i: Transactions) {
		  if (i.first == FileNodeListID) {
		    list_length = i.second;*/
//  		  ONE_DEBUG_MSG((" from transactions\n"));
/*  		  found = true;
		    break;
		  }
		}*/
		if (!found) {
		  ONE_DEBUG_MSG(("length not found for list %d\n", FileNodeListID));
		}
		expected_fragment_sequence = readU32 (input, false);
		if (expected_fragment_sequence != nFragmentSequence) {
		  ONE_DEBUG_MSG(("expected fragment %d, got %d\n", nFragmentSequence, expected_fragment_sequence));
		}
		else nFragmentSequence++;

//		ONE_DEBUG_MSG((" nFragmentSequence ")) << nFragmentSequence << '\n';
  }

	std::string FileNodeList::to_string() {
		std::stringstream stream;
		stream << std::hex << "uintMagic " << uintMagic << '\n';
		stream << std::dec << "FileNodeListID " << FileNodeListID << '\n';
		stream << "nFragmentSequence " << nFragmentSequence << '\n';
		for (FileNode i: rgFileNodes)
			stream << i.to_string() << '\n';
		return stream.str();
	}

	FileNode FileNodeList::get_next_node(librevenge::RVNGInputStream *input) {
	  bool next_fragment_wanted = false;
	  FileChunkReference next_fragment = FileChunkReference(FileChunkReferenceSize::Size64x32);
	  FileNode node;
	  if (!header_parsed) {
	    parse_header(input);
	    header_parsed = true;
	  }

//    ONE_DEBUG_MSG((node.to_string));

	  if ((input->tell() >= next_fragment_location) || (next_fragment_location - input->tell() <= 4)) {
	    ONE_DEBUG_MSG(("wanting next fragment\n"));
	    next_fragment_wanted = true;
    }

    if (!next_fragment_wanted) {
  	  node.parse(input);
  	  if (node.get_FileNodeID() == FileNode::ChunkTerminatorFND)
  	    next_fragment_wanted = true;
  	  else
    	  elements_parsed++;
  	}



	  if (next_fragment_wanted) {
      input->seek(next_fragment_location, librevenge::RVNG_SEEK_SET);
      next_fragment.parse(input);

      if (readU64(input, false) != 0x8BC215C38233BA4B) {
        FileNode zero;
        ONE_DEBUG_MSG(("footer not correct, position %ld\n", input->tell()));
        end = true;
        zero.zero();
        return zero;
      }

      if (next_fragment.is_fcrNil()) end = true;
      else {
        location = next_fragment.get_location();
        size = next_fragment.get_size();
        input->seek(location, librevenge::RVNG_SEEK_SET);
        ONE_DEBUG_MSG(("what's up in here? %ld\n", input->tell()));
        parse_header(input);
        node.parse(input);
    	  elements_parsed++;
      }
      next_fragment_wanted = false;
	  }

    if (node.get_FileNodeID() == FileNode::DUNNO)
      end = true;

    if (elements_parsed == list_length) {
      end = true;
      ONE_DEBUG_MSG(("got to list length %d, parsed %d\n", list_length, elements_parsed));
    } else {
  	  ONE_DEBUG_MSG(("list id %d, element %d, length %d, position %ld, next fragment@%ld\n", FileNodeListID, elements_parsed, list_length, input->tell(), next_fragment_location));
  	}
	  return node;
	}

	FileNode FileNodeList::force_get_next_node(librevenge::RVNGInputStream *input) {
	  FileNode node = force_get_next_node(input);
	  end = false;
	  return node;
	}

	bool FileNodeList::is_end() {
	  return end;
	}
}


