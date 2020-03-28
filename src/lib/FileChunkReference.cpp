/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>
#include "FileChunkReference.h"
#include "libone_utils.h"

using std::stringstream;

namespace libone {

	void FileChunkReference::parse(librevenge::RVNGInputStream *input, mode size) {
    size_mode = size;
	  switch (size) {
	    case Type64x64:
	      parse(input, 0, 1);
	      break;
	    case Type32x32:
	      parse(input, 1, 0);
	      break;
	    case Type64x32:
	      parse(input, 0, 0);
	      break;
	    default:
	      ONE_DEBUG_MSG(("FileChunkReference: not good!\n"));
	      break;
	  }
	}

	void FileChunkReference::parse(librevenge::RVNGInputStream *input, uint32_t a, uint32_t b) {
	  bool stp64 = false;
	  bool cb64 = false;
		switch (a) {
			case 1:
				stp = readU32 (input, false);
				size_in_file += 4;
				break;
			case 2:
				stp = readU16 (input, false) * 8;
				size_in_file += 2;
				break;
			case 3:
				stp = readU32 (input, false) * 8;
				size_in_file += 4;
				stp64 = true;
				break;
			case 0:
				stp = readU64 (input, false);
				size_in_file += 8;
				stp64 = true;
				break;
			default:
				break;
		}
		switch (b) {
			case 0:
				cb = readU32(input, false);
				size_in_file += 4;
				break;
			case 1:
				cb = readU64(input, false);
				cb64 = true;
				size_in_file += 8;
				break;
			case 2:
				cb = readU8(input) * 8;
				size_in_file += 1;
				break;
			case 3:
				cb = readU16(input, false) * 8;
				size_in_file += 2;
				break;
			default:
				break;
			}

		if (stp64 && cb64) size_mode = Type64x64;
		if (stp64 && !cb64) size_mode = Type64x32;
		if (!stp64 && !cb64) size_mode = Type32x32;

	}
	long FileChunkReference::get_location() {
		return stp;
	}
	long FileChunkReference::get_size() {
		return cb;
	}

	string FileChunkReference::to_string() {
		std::stringstream stream;
		if (is_fcrNil ()) return "fcrNil";
		if (is_fcrZero ()) return "fcrZero";

    switch (size_mode) {
      case Type32x32:
    		stream << std::hex << "stp32 " << stp << " cb32 " << cb;
    		break;
    	case Type64x32:
    		stream << std::hex << "stp64 " << stp << " cb32 " << cb;
    		break;
    	case Type64x64:
    		stream << std::hex << "stp64 " << stp << " cb64 " << cb;
    		break;
    	case NIL:
    	default:
    	  stream << "NIL invalid FileChunkReference";
    	  break;
    }

		return stream.str();
	}

  bool FileChunkReference::is_fcrNil() {
    bool cbval = (cb == 0);
    switch (size_mode) {
      case Type32x32:
        return (cbval && (stp & 0xFFFFFFFF));
      case Type64x64:
      case Type64x32:
        return (cbval && (stp & 0xFFFFFFFFFFFFFFFF));
      default:
        return false;
    }
  }

  bool FileChunkReference::is_fcrZero() {
    return ((stp == 0) && (cb == 0));
  }

  void FileChunkReference::set_zero() {
    stp = 0;
    cb = 0;
    size_in_file = 0;
    size_mode = NIL;
  }

  // Size of the structure in bytes. Used for seeking
  long FileChunkReference::get_size_on_file() {
    return size_in_file;
  }
}
