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

#include "libone_utils.h"

#include <bitset>
using namespace std;
using std::string;

namespace libone {

	void FileNode::parse(librevenge::RVNGInputStream *input) {
//		uint16_t tmp1;
//		uint16_t tmp2;
		unsigned int temp;

		temp = readU32 (input, false);
		Revision rev;
		ExtendedGUID guid;
		ObjectSpace space;
		d = temp >> 31;
		c = (temp >> 27) & 0xF;
		b = (temp >> 25) & 0x3;
		a = (temp >> 23) & 0x3;
		Size = (temp >> 10) & 0x1FFF;
		FileNodeID = temp & 0x3FF;
		std::bitset<10> y(FileNodeID);

		std::cout << "filenodeid " << FileNodeID << " " << y << '\n';
		Size = (temp & SizeMask) >> 9;
		std::bitset<13> z(Size);
		std::cout << "Size " << Size << " " << z << '\n';
		std::cout << "A " << a << " B " << b << " C " << c << " D " << d << '\n';


		uint32_t l = 0, s = 0;
		if (get_C()) {
			switch (get_A()) {
				case 1:
					l = readU32 (input, false);
					break;
				case 2:
					l = readU16 (input, false) * 8;
					break;
				case 3:
					l = readU32 (input, false);
					break;
				case 0:
					l = readU64 (input, false);
					break;
				default:
					break;
			}
			switch (get_B()) {
				case 0:
					s = readU32(input, false);
					break;
				case 1:
					s = readU64(input, false);
					break;
				case 2:
					s = readU8(input) * 8;
					break;
				case 3:
					s = readU16(input, false) * 8;
					break;
				default:
					break;
				}
		}
		ref.set_all(l, s);
		cout << "ref " << ref.to_string() << " position " << input->tell() << "\n\n";
		switch (FileNodeID) {
			case FileNodeDescriptor::ObjectSpaceManifestListStartFND:
				guid.parse(input);
				cout << std::hex << guid.to_string () << '\n';
				break;
			case FileNodeDescriptor::ChunkTerminatorFND:
				is_end = true;
				break;
			case FileNodeDescriptor::RevisionManifestStart4FND:
			case FileNodeDescriptor::RevisionManifestStart6FND:
			case FileNodeDescriptor::RevisionManifestStart7FND:
				rev.parse(input, FileNodeID);
				break;
			case FileNodeDescriptor::RevisionManifestListReferenceFND:
				try_parse_ref (input, 0);
				break;
			case FileNodeDescriptor::RevisionManifestListStartFND:
				guid.parse(input);
				cout << guid.to_string () << " " << readU32(input) << '\n';

				break;
			case FileNodeDescriptor::ObjectSpaceManifestListReferenceFND:
				guid.parse(input);

				 break;
			case FileNodeDescriptor::ObjectSpaceManifestRootFND:
				guid.parse(input);
				RootObject = guid;
				break;
			case FileNodeDescriptor::FileDataStoreListReferenceFND:
				cout << "ref " << ref.to_string() << '\n';
				break;
			case FileNodeDescriptor::TYPES_END:
				cout << "padding everywhere\n";
				is_end = true;
				break;
			default:
				cout << "dunno but value is " << std::hex << FileNodeID << '\n';
				skip(input, Size);
				//is_end = true;
				break;
		}

	}

	void FileNode::try_parse_ref(librevenge::RVNGInputStream *input, uint32_t expected_FileNodeID) {
		long old = input->tell();
		FileNodeListFragment frag;
		input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
		frag.parse(input, expected_FileNodeID);
		frag.to_string ();
		input->seek(old, librevenge::RVNG_SEEK_SET);
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << '\n';
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "A " << a << " B " << b << " C " << c << " D " << d << '\n';

		return stream.str();
	}

	bool FileNode::isEnd() {
		return is_end;
	}

	uint32_t FileNode::get_FileNodeID() {
		return FileNodeID;
	}

	uint32_t FileNode::get_Size() {
		return Size;
	}

	uint32_t FileNode::get_A() {
		return a;
	}

	uint32_t FileNode::get_B() {
		return b;
	}

	uint32_t FileNode::get_C() {
		return c;
	}

	uint32_t FileNode::get_D() {
		return d;
	}
}


