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

#include "FileNode.h"

using namespace std;
using std::string;

namespace libone {

	void FileNode::parse(librevenge::RVNGInputStream *input) {
    parse_header(input);
		switch (FileNodeID) {
			case FileNode::ObjectSpaceManifestListStartFND:
		  case FileNode::RevisionManifestListStartFND:
			case FileNode::RevisionManifestStart4FND:
			case FileNode::RevisionManifestStart6FND:
			case FileNode::RevisionManifestStart7FND:
			case FileNode::RevisionManifestListReferenceFND:
			case FileNode::ObjectGroupListReferenceFND:
			case FileNode::ObjectSpaceManifestListReferenceFND:
			case FileNode::ObjectSpaceManifestRootFND:
			case FileNode::FileDataStoreListReferenceFND:
			case FileNode::ObjectGroupStartFND:
			case FileNode::GlobalIdTableStart2FND:
		  case FileNode::GlobalIdTableEntryFNDX:
		  case FileNode::GlobalIdTableEndFNDX:
      case FileNode::DataSignatureGroupDefinitionFND:
      case FileNode::ObjectDeclaration2RefCountFND:
      case FileNode::ObjectGroupEndFND:
      case FileNode::ObjectInfoDependencyOverridesFND:
      case FileNode::RootObjectReference3FND:
      case FileNode::RevisionManifestEndFND:
      case FileNode::ObjectDeclarationFileData3RefCountFND:
      case FileNode::ReadOnlyObjectDeclaration2RefCountFND:
      case FileNode::FileDataStoreObjectReferenceFND:
        break;
			case FileNode::ChunkTerminatorFND:
			  std::cout << "ChunkTerminatorFND\n";
				is_end = true;
				break;
			case FileNode::TYPES_END:
				cout << "padding everywhere\n";
//				while (readU16 (input) ==  0) {}
//				input->seek(-2, librevenge::RVNG_SEEK_CUR);
//        ref.parse(input, FileChunkReference::mode::Type64x32);
				is_end = true;
				break;
			default:
				cout << "dunno but value is " << std::hex << FileNodeID << '\n';
				FileNodeID = DUNNO;
//				input->seek(-4, librevenge::RVNG_SEEK_CUR);
//				skip(input, Size);
				is_end = true;
				break;
		}
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << " ";

		switch (FileNodeID) {
			case FileNode::ObjectSpaceManifestListStartFND:
				cout << "ObjectSpaceManifestListStartFND\n";
				break;
			case FileNode::ChunkTerminatorFND:
				cout << "ChunkTerminatorFND\n";
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
				break;
			case FileNode::ObjectGroupListReferenceFND:
			  cout << "ObjectGroupListReferenceFND\n";
			  break;
			case FileNode::ObjectSpaceManifestListReferenceFND:
				break;
			case FileNode::ObjectSpaceManifestRootFND:
			  cout << "ObjectSpaceManifestListRootFND\n";
				break;
			case FileNode::FileDataStoreListReferenceFND:
			  cout << "FileDataStoreListReferenceFND\n";
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
			  cout << "NO TYPE\n";
				break;
      case FileNode::DataSignatureGroupDefinitionFND:
        cout << "DataSignatureGroupDefinitionFND\n";
        break;
      case FileNode::ObjectDeclaration2RefCountFND:
        cout << "ObjectDeclaration2RefCountFND\n";
        break;
      case FileNode::ObjectGroupEndFND:
        cout << "ObjectGroupEndFND\n";
        break;
			default:
				cout << "dunno but value is " << std::hex << FileNodeID << '\n';
				break;
    }
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "A " << StpFormat << " B " << CbFormat << " C " << BaseType << " D " << d << "\n";

		return stream.str();
	}

	void FileNode::parse_header(librevenge::RVNGInputStream *input) {
		unsigned int temp;
		FileChunkReference reference;
		temp = readU32 (input, false);
		d = temp >> 31;
		BaseType = (temp >> 27) & 0xF;
		CbFormat = (temp >> 25) & 0x3;
		StpFormat = (temp >> 23) & 0x3;
		Size = (temp >> 10) & 0x1FFF;
		FileNodeID = temp & 0x3FF;
		if (d == 0) {
	    std::bitset<13> z(Size);
	    std::cout << "Size " << std::hex << Size << " " << z << '\n';
	    std::cout << "warning: d is zero\n";
    }
    std::bitset<32> y(temp);
    std::cout << std::hex << "filenodeid " << FileNodeID << " filenode bits " << y << '\n';
		switch(get_Basetype()) {
		  case 1:
  			reference.parse(input, get_StpFormat(), get_CbFormat());
    		cout << "ref data @ " << reference.to_string() << " position " << input->tell() << "\n";
    		break;
    	case 2:
				reference.parse(input, get_StpFormat(), get_CbFormat());
    	  cout << "ref list @ " << reference.to_string () << " position " << input->tell() << "\n";
    	  break;
    	case 0:
    	default:
	      reference.set_zero();
	      cout << "noref position " << input->tell() << "\n";
		}
		ref = reference;
	}

	void FileNode::skip_node(librevenge::RVNGInputStream *input) {
	  int ref_size = 0;
	  switch (get_Basetype()) {
	    case 1:
	    case 2:
	      switch (get_StpFormat()) {
	        case 0:
            ref_size += 8;
            break;
          case 1:
          case 3:
            ref_size += 4;
            break;
          case 2:
            ref_size += 2;
            break;
	      }
	      switch (get_CbFormat()) {
	        case 0:
	          ref_size += 4;
	          break;
	        case 1:
	          ref_size += 8;
	          break;
	        case 2:
	          ref_size += 1;
	          break;
	        case 3:
	          ref_size += 2;
	          break;
	        }
	      default:
	        break;
	      }

  (void) ref_size;
   input->seek(Size - ref_size - 4, librevenge::RVNG_SEEK_CUR);
	  std::cout << "Skipping " << Size - ref_size - 4 << " bytes. size " << Size << " ref_size " << ref_size << ", position " << input->tell() << "\n";
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


