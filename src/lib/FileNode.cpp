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
			  ONE_DEBUG_MSG(("ChunkTerminatorFND\n"));
				is_end = true;
				break;
			case FileNode::TYPES_END:
				ONE_DEBUG_MSG(("padding everywhere\n"));
//				while (readU16 (input) ==  0) {}
//				input->seek(-2, librevenge::RVNG_SEEK_CUR);
//        ref.parse(input, FileChunkReference::mode::Type64x32);
				is_end = true;
				break;
			default:
				ONE_DEBUG_MSG(("dunno but value is %x\n", FileNodeID));
				FileNodeID = DUNNO;
//				input->seek(-4, librevenge::RVNG_SEEK_CUR);
//				skip(input, Size);
				is_end = true;
				break;
		}
	}

	std::string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << " ";

		switch (FileNodeID) {
			case FileNode::ObjectSpaceManifestListStartFND:
				ONE_DEBUG_MSG(("ObjectSpaceManifestListStartFND\n"));
				break;
			case FileNode::ChunkTerminatorFND:
				ONE_DEBUG_MSG(("ChunkTerminatorFND\n"));
				break;
		  case FileNode::RevisionManifestListStartFND:
				ONE_DEBUG_MSG(("RevisionManifestListStart\n"));
				break;
			case FileNode::RevisionManifestStart4FND:
			  ONE_DEBUG_MSG(("RevisionManifestStart4FND\n"));
			  break;
			case FileNode::RevisionManifestStart6FND:
			  ONE_DEBUG_MSG(("RevisionManifestStart6FND\n"));
			  break;
			case FileNode::RevisionManifestStart7FND:
				ONE_DEBUG_MSG(("RevisionManifestStart\n"));
				break;
			case FileNode::RevisionManifestListReferenceFND:
			    ONE_DEBUG_MSG(("RevisionManifestListReferenceFND\n"));
				break;
			case FileNode::ObjectGroupListReferenceFND:
			  ONE_DEBUG_MSG(("ObjectGroupListReferenceFND\n"));
			  break;
			case FileNode::ObjectSpaceManifestListReferenceFND:
				break;
			case FileNode::ObjectSpaceManifestRootFND:
			  ONE_DEBUG_MSG(("ObjectSpaceManifestListRootFND\n"));
				break;
			case FileNode::FileDataStoreListReferenceFND:
			  ONE_DEBUG_MSG(("FileDataStoreListReferenceFND\n"));
				break;
			case FileNode::ObjectGroupStartFND:
			  ONE_DEBUG_MSG(("ObjectGroupStartFND\n"));
			  break;
			case FileNode::GlobalIdTableStart2FND:
			  ONE_DEBUG_MSG(("GlobalIdTableStart2FND\n"));
			  break;
		  case FileNode::GlobalIdTableEntryFNDX:
		    ONE_DEBUG_MSG(("GlobalIdTableEntryFNDX\n"));
		    break;
		  case FileNode::GlobalIdTableEndFNDX:
		    ONE_DEBUG_MSG(("GlobalIdTableEndFNDX\n"));
		    break;
			case FileNode::TYPES_END:
			  ONE_DEBUG_MSG(("NO TYPE\n"));
				break;
      case FileNode::DataSignatureGroupDefinitionFND:
        ONE_DEBUG_MSG(("DataSignatureGroupDefinitionFND\n"));
        break;
      case FileNode::ObjectDeclaration2RefCountFND:
        ONE_DEBUG_MSG(("ObjectDeclaration2RefCountFND\n"));
        break;
      case FileNode::ObjectGroupEndFND:
        ONE_DEBUG_MSG(("ObjectGroupEndFND\n"));
        break;
			default:
				ONE_DEBUG_MSG(("dunno but value is %x\n", FileNodeID));
				break;
    }
		stream << std::hex << "Size " << Size << std::endl;
		stream << std::hex << m_base_type << std::endl;

		return stream.str();
	}

	void FileNode::parse_header(librevenge::RVNGInputStream *input) {
		uint32_t temp;
		enum stp_format format_stp;
		enum cb_format format_cb;
		int d;

		temp = readU32 (input, false);
		d = temp >> 31;
		format_stp = static_cast<stp_format>((temp >> 23) & 0x3);
		format_cb = static_cast<cb_format>((temp >> 25) & 0x3);
		m_base_type = static_cast<fnd_basetype> ((temp >> 27) & 0xF);
		Size = (temp >> 10) & 0x1FFF;
		FileNodeID = temp & 0x3FF;
		if (d == 0) {
	    std::bitset<13> z(Size);
	    ONE_DEBUG_MSG(("%s\n", z.to_string().c_str()));
	    ONE_DEBUG_MSG(("warning: d is zero\n"));
    }
	FileNodeChunkReference reference(format_stp, format_cb, input->tell());

    std::bitset<32> y(temp);
    ONE_DEBUG_MSG((" filenode bits %s\n", y.to_string().c_str()));
		switch(m_base_type) {
		  case fnd_ref_data:
		  case fnd_ref_filenodelist:
  			reference.parse(input);
    		ONE_DEBUG_MSG(("\n"));
    		break;
    	case fnd_no_data:
    	default:
	      reference.set_zero();
	      ONE_DEBUG_MSG(("\n"));
		}
		m_fnd = reference;
	}

	void FileNode::skip_node(librevenge::RVNGInputStream *input) {
	  int ref_size = 0;
	  switch (get_Basetype()) {
	    case fnd_ref_data:
	    case fnd_ref_filenodelist:
	      switch (m_fnd.get_stp_fmt()) {
	        case stp_uncompressed_8:
            ref_size += 8;
            break;
          case stp_uncompressed_4:
          case stp_compressed_4:
            ref_size += 4;
            break;
          case stp_compressed_2:
            ref_size += 2;
            break;
		  case stp_invalid:
		  default:
		  	break;
	      }
	      switch (m_fnd.get_cb_fmt()) {
	        case cb_uncompressed_4:
	          ref_size += 4;
	          break;
	        case cb_uncompressed_8:
	          ref_size += 8;
	          break;
	        case cb_compressed_1:
	          ref_size += 1;
	          break;
	        case cb_compressed_2:
	          ref_size += 2;
	          break;
			case cb_invalid:
			default:
			  break;
	        }
	      default:
	        break;
	      }

  (void) ref_size;
   input->seek(Size - ref_size - 4, librevenge::RVNG_SEEK_CUR);
	  ONE_DEBUG_MSG(("\n"));
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

	enum fnd_basetype FileNode::get_Basetype() {
		return m_base_type;
	}

	FileNodeChunkReference FileNode::get_fnd() {
	  return m_fnd;
	}
}


