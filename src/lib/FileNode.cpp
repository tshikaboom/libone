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
    m_offset = input->tell();

    parse_header(input);
    switch (FileNodeID) {
      case fnd_id::ObjectSpaceManifestListStartFND:
      case fnd_id::RevisionManifestListStartFND:
      case fnd_id::RevisionManifestStart4FND:
      case fnd_id::RevisionManifestStart6FND:
      case fnd_id::RevisionManifestStart7FND:
      case fnd_id::RevisionManifestListReferenceFND:
      case fnd_id::ObjectGroupListReferenceFND:
      case fnd_id::ObjectSpaceManifestListReferenceFND:
      case fnd_id::ObjectSpaceManifestRootFND:
      case fnd_id::FileDataStoreListReferenceFND:
      case fnd_id::ObjectGroupStartFND:
      case fnd_id::GlobalIdTableStart2FND:
      case fnd_id::GlobalIdTableEntryFNDX:
      case fnd_id::GlobalIdTableEndFNDX:
      case fnd_id::DataSignatureGroupDefinitionFND:
      case fnd_id::ObjectDeclaration2RefCountFND:
      case fnd_id::ObjectGroupEndFND:
      case fnd_id::ObjectInfoDependencyOverridesFND:
      case fnd_id::RootObjectReference3FND:
      case fnd_id::RevisionManifestEndFND:
      case fnd_id::ObjectDeclarationFileData3RefCountFND:
      case fnd_id::ReadOnlyObjectDeclaration2RefCountFND:
      case fnd_id::FileDataStoreObjectReferenceFND:
        break;
      case fnd_id::ChunkTerminatorFND:
        ONE_DEBUG_MSG(("ChunkTerminatorFND\n"));
        is_end = true;
        break;
      case fnd_id::fnd_invalid_id:
        ONE_DEBUG_MSG(("padding everywhere\n"));
//				while (readU16 (input) ==  0) {}
//				input->seek(-2, librevenge::RVNG_SEEK_CUR);
//        ref.parse(input, FileChunkReference::mode::Type64x32);
        is_end = true;
        break;
      default:
        ONE_DEBUG_MSG(("dunno but value is %x\n", FileNodeID));
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
      case fnd_id::ObjectSpaceManifestListStartFND:
        ONE_DEBUG_MSG(("ObjectSpaceManifestListStartFND\n"));
        break;
      case fnd_id::ChunkTerminatorFND:
        ONE_DEBUG_MSG(("ChunkTerminatorFND\n"));
        break;
      case fnd_id::RevisionManifestListStartFND:
        ONE_DEBUG_MSG(("RevisionManifestListStart\n"));
        break;
      case fnd_id::RevisionManifestStart4FND:
        ONE_DEBUG_MSG(("RevisionManifestStart4FND\n"));
        break;
      case fnd_id::RevisionManifestStart6FND:
        ONE_DEBUG_MSG(("RevisionManifestStart6FND\n"));
        break;
      case fnd_id::RevisionManifestStart7FND:
        ONE_DEBUG_MSG(("RevisionManifestStart\n"));
        break;
      case fnd_id::RevisionManifestListReferenceFND:
          ONE_DEBUG_MSG(("RevisionManifestListReferenceFND\n"));
        break;
      case fnd_id::ObjectGroupListReferenceFND:
        ONE_DEBUG_MSG(("ObjectGroupListReferenceFND\n"));
        break;
      case fnd_id::ObjectSpaceManifestListReferenceFND:
        break;
      case fnd_id::ObjectSpaceManifestRootFND:
        ONE_DEBUG_MSG(("ObjectSpaceManifestListRootFND\n"));
        break;
      case fnd_id::FileDataStoreListReferenceFND:
        ONE_DEBUG_MSG(("FileDataStoreListReferenceFND\n"));
        break;
      case fnd_id::ObjectGroupStartFND:
        ONE_DEBUG_MSG(("ObjectGroupStartFND\n"));
        break;
      case fnd_id::GlobalIdTableStart2FND:
        ONE_DEBUG_MSG(("GlobalIdTableStart2FND\n"));
        break;
      case fnd_id::GlobalIdTableEntryFNDX:
        ONE_DEBUG_MSG(("GlobalIdTableEntryFNDX\n"));
        break;
      case fnd_id::GlobalIdTableEndFNDX:
        ONE_DEBUG_MSG(("GlobalIdTableEndFNDX\n"));
        break;
      case fnd_id::DataSignatureGroupDefinitionFND:
        ONE_DEBUG_MSG(("DataSignatureGroupDefinitionFND\n"));
        break;
      case fnd_id::ObjectDeclaration2RefCountFND:
        ONE_DEBUG_MSG(("ObjectDeclaration2RefCountFND\n"));
        break;
      case fnd_id::ObjectGroupEndFND:
        ONE_DEBUG_MSG(("ObjectGroupEndFND\n"));
        break;
      case fnd_id::fnd_invalid_id:
      default:
        ONE_DEBUG_MSG(("dunno but value is %x\n", FileNodeID));
        break;
    }
    stream << std::hex << "Size " << m_size_in_file << std::endl;
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
    m_size_in_file = (temp >> 10) & 0x1FFF;
    FileNodeID = temp & 0x3FF;
    if (d == 0) {
      std::bitset<13> z(m_size_in_file);
      ONE_DEBUG_MSG(("%s\n", z.to_string().c_str()));
      ONE_DEBUG_MSG(("warning: d is zero\n"));
    }
    assert (d == 1);
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
    input->seek(m_offset + m_size_in_file, librevenge::RVNG_SEEK_CUR);
  }

  bool FileNode::isEnd() {
    return is_end;
  }

  uint32_t FileNode::get_FileNodeID() {
    return FileNodeID;
  }

  uint32_t FileNode::get_Size() {
    return m_size_in_file;
  }

  enum fnd_basetype FileNode::get_Basetype() {
    return m_base_type;
  }

  FileNodeChunkReference FileNode::get_fnd() {
    return m_fnd;
  }
}


