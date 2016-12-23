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
		Revision rev;
		ExtendedGUID guid;
		ObjectSpace space;
    parse_header(input);

		switch (FileNodeID) {
			case FileNode::ObjectSpaceManifestListStartFND:
				cout << "ObjectSpaceManifestListStartFND\n";
				break;
			case FileNode::ChunkTerminatorFND:
				cout << "ChunkTerminatorFND\n";
				is_end = true;
				break;
		  case FileNode::RevisionManifestListStartFND:
				cout << "RevisionManifestListStart\n";
				break;
			case FileNode::RevisionManifestStart4FND:
			  cout << "RevisionManifestStart4FND\n";
			  break;
			case FileNode::RevisionManifestStart6FND:
			  cout << "RevisionManifestStart6FND\n";
			  break;
			case FileNode::RevisionManifestStart7FND:
				cout << "RevisionManifestStart\n";
				break;
			case FileNode::RevisionManifestListReferenceFND:
			    cout << "RevisionManifestListReferenceFND\n";
//				try_parse_ref (input, 0);
				break;
			case FileNode::ObjectGroupListReferenceFND:
			  cout << "ObjectGroupListReferenceFND\n";
			  break;
			case FileNode::ObjectSpaceManifestListReferenceFND:
				guid.parse(input);
				cout << "ObjectSpaceManifestListReferenceFND " << guid.to_string () << "\n";
        space.list_parse(input, guid, ref);
        ObjectSpaces.insert({ guid.to_string(), space});
				break;
			case FileNode::ObjectSpaceManifestRootFND:
			  cout << "ObjectSpaceManifestListRootFND\n";
				guid.parse(input);
				RootObject = guid;
				break;
			case FileNode::FileDataStoreListReferenceFND:
			  cout << "FileDataStoreListReferenceFND\n";
				cout << "ref " << ref.to_string() << '\n';
				break;
			case FileNode::ObjectGroupStartFND:
			  cout << "ObjectGroupStartFND\n";
			  break;
			case FileNode::GlobalIdTableStart2FND:
			  cout << "GlobalIdTableStart2FND\n";
			  break;
		  case FileNode::GlobalIdTableEntryFNDX:
		    cout << "GlobalIdTableEntryFNDX\n";
		    break;
		  case FileNode::GlobalIdTableEndFNDX:
		    cout << "GlobalIdTableEndFNDX\n";
		    break;
			case FileNode::TYPES_END:
				cout << "padding everywhere\n";
				while (readU16 (input) ==  0) {}
				input->seek(-2, librevenge::RVNG_SEEK_CUR);
        ref.parse(input, FileChunkReference::mode::Type64x32);
				is_end = true;
				break;
      case FileNode::DataSignatureGroupDefinitionFND:
        cout << "DataSignatureGroupDefinitionFND\n";
        break;
      case FileNode::ObjectDeclaration2RefCountFND:
        cout << "ObjectDeclaration2RefCountFND position " << input->tell() << "\n";
        break;
      case FileNode::ObjectGroupEndFND:
        cout << "ObjectGroupEndFND\n";
        break;
			default:
				cout << "dunno but value is " << std::hex << FileNodeID << '\n';
				input->seek(-4, librevenge::RVNG_SEEK_CUR);
//				skip(input, Size);
				is_end = true;
				break;
		}
  std::cout << "\n\n";
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << '\n';
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "A " << StpFormat << " B " << CbFormat << " C " << BaseType << " D " << d;

		return stream.str();
	}

	void FileNode::parse_header(librevenge::RVNGInputStream *input) {
		unsigned int temp;
		temp = readU32 (input, false);

		d = temp >> 31;
		BaseType = (temp >> 27) & 0xF;
		CbFormat = (temp >> 25) & 0x3;
		StpFormat = (temp >> 23) & 0x3;
		Size = (temp >> 10) & 0x1FFF;
		FileNodeID = temp & 0x3FF;
		std::bitset<10> y(FileNodeID);

		std::cout << "filenodeid " << FileNodeID << " " << y << '\n';
		Size = (temp & SizeMask) >> 9;
		std::bitset<13> z(Size);
		std::cout << "Size " << Size << " " << z << '\n';
		std::cout << "A " << StpFormat << " B " << CbFormat << " C " << BaseType << " D " << d << '\n';


		switch(get_Basetype()) {
		  case 1:
  			ref.parse(input, get_StpFormat(), get_CbFormat());
    		cout << "ref data @ " << ref.to_string() << " position " << input->tell() << "\n";
    		break;
    	case 2:
				ref.parse(input, get_StpFormat(), get_CbFormat());
    	  cout << "ref list @ " << ref.to_string () << " position " << input->tell() << "\n";
    	  break;
    	case 0:
    	default:
	      ref.set_zero();
	      cout << "noref position " << input->tell() << "\n";
		}
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

	uint32_t FileNode::get_StpFormat() {
		return StpFormat;
	}

	uint32_t FileNode::get_CbFormat() {
		return CbFormat;
	}

	uint32_t FileNode::get_Basetype() {
		return BaseType;
	}

	uint32_t FileNode::get_D() {
		return d;
	}

	FileChunkReference FileNode::get_ref() {
	  return ref;
	}
}


