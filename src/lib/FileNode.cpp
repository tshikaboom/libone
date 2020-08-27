/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <libone/libone.h>

#include "libone_utils.h"

#include <bitset>

#include "FileNode.h"
#include "FileNodeData/FileNodeData.h"

namespace libone
{

FileNode::~FileNode()
{
  delete m_fnd;
}

std::string fnd_id_to_string(FndId id_fnd)
{
  std::stringstream stream;

  switch (id_fnd)
  {
  case FndId::ObjectSpaceManifestListStartFND:
    stream << "ObjectSpaceManifestListStartFND";
    break;
  case FndId::ChunkTerminatorFND:
    stream << "ChunkTerminatorFND";
    break;
  case FndId::RevisionManifestListStartFND:
    stream << "RevisionManifestListStart";
    break;
  case FndId::RevisionManifestStart4FND:
    stream << "RevisionManifestStart4FND";
    break;
  case FndId::RevisionManifestStart6FND:
    stream << "RevisionManifestStart6FND";
    break;
  case FndId::RevisionManifestStart7FND:
    stream << "RevisionManifestStart";
    break;
  case FndId::RevisionManifestListReferenceFND:
    stream << "RevisionManifestListReferenceFND";
    break;
  case FndId::ObjectGroupListReferenceFND:
    stream << "ObjectGroupListReferenceFND";
    break;
  case FndId::ObjectSpaceManifestListReferenceFND:
    stream << "ObjectSpaceManifestListReferenceFND";
    break;
  case FndId::ObjectSpaceManifestRootFND:
    stream << "ObjectSpaceManifestListRootFND";
    break;
  case FndId::FileDataStoreListReferenceFND:
    stream << "FileDataStoreListReferenceFND";
    break;
  case FndId::ObjectGroupStartFND:
    stream << "ObjectGroupStartFND";
    break;
  case FndId::GlobalIdTableStart2FND:
    stream << "GlobalIdTableStart2FND";
    break;
  case FndId::GlobalIdTableEntryFNDX:
    stream << "GlobalIdTableEntryFNDX";
    break;
  case FndId::GlobalIdTableEndFNDX:
    stream << "GlobalIdTableEndFNDX";
    break;
  case FndId::DataSignatureGroupDefinitionFND:
    stream << "DataSignatureGroupDefinitionFND";
    break;
  case FndId::ObjectDeclaration2RefCountFND:
    stream << "ObjectDeclaration2RefCountFND";
    break;
  case FndId::ObjectGroupEndFND:
    stream << "ObjectGroupEndFND";
    break;
  case FndId::fnd_invalid_id:
  default:
    stream << "Invalid FND";
    break;
  }
  return stream.str();
}

void FileNode::parse(const libone::RVNGInputStreamPtr_t &input)
{
  m_offset = input->tell();

  DBMSG << "Will parse at " << m_offset << std::endl;

  uint32_t temp;
  StpFormat format_stp;
  CbFormat format_cb;
  int d;

  temp = readU32(input, false);
  d = temp >> 31;
  format_stp = static_cast<StpFormat>((temp >> shift_format_stp) & mask_format_stp);
  format_cb = static_cast<CbFormat>((temp >> shift_format_cb) & mask_format_cb);
  m_base_type = static_cast<fnd_basetype>((temp >> shift_base_type) & mask_fnd_base_type);
  m_fnd_id = static_cast<FndId>(temp & mask_fnd_id);
  m_size_in_file = (temp >> shift_fnd_size) & mask_fnd_size;
  if (d == 0)
  {
    std::bitset<13> z(m_size_in_file);
    ONE_DEBUG_MSG(("%s\n", z.to_string().c_str()));
    ONE_DEBUG_MSG(("warning: d is zero\n"));
  }
  assert(d == 1);
  FileNodeChunkReference reference(format_stp, format_cb);

  std::bitset<32> y(temp);
  ONE_DEBUG_MSG((" filenode bits %s\n", y.to_string().c_str()));
  switch (m_base_type)
  {
  case fnd_ref_data:
  case fnd_ref_filenodelist:
    reference.parse(input, input->tell());
    ONE_DEBUG_MSG(("\n"));
    break;
  case fnd_no_data:
    reference.set_zero();
    break;
  default:
    assert(false);
    break;
  }
  m_fncr = reference;

  switch (m_fnd_id)
  {
    break;
  case FndId::DataSignatureGroupDefinitionFND:
    break;
  case FndId::FileDataStoreListReferenceFND:
    break;
  case FndId::FileDataStoreObjectReferenceFND:
    break;
  case FndId::GlobalIdTableEntry2FNDX:
    break;
  case FndId::GlobalIdTableEntry3FNDX:
    break;
  case FndId::GlobalIdTableEntryFNDX:
    break;
  case FndId::GlobalIdTableStartFNDX:
    break;
  case FndId::HashedChunkDescriptor2FND:
    break;
  case FndId::ObjectDataEncryptionKeyV2FNDX:
    break;
  case FndId::ObjectDeclaration2LargeRefCountFND:
    break;
  case FndId::ObjectDeclaration2RefCountFND:
    break;
  case FndId::ObjectDeclarationFileData3LargeRefCountFND:
    break;
  case FndId::ObjectDeclarationFileData3RefCountFND:
    break;
  case FndId::ObjectDeclarationWithRefCount2FNDX:
    break;
  case FndId::ObjectDeclarationWithRefCountFNDX:
    break;
  case FndId::ObjectGroupListReferenceFND:
    break;
  case FndId::ObjectGroupStartFND:
    break;
  case FndId::ObjectInfoDependencyOverridesFND:
    break;
  case FndId::ObjectRevisionWithRefCount2FNDX:
    break;
  case FndId::ObjectRevisionWithRefCountFNDX:
    break;
  case FndId::ObjectSpaceManifestListReferenceFND:
    break;
  case FndId::ObjectSpaceManifestListStartFND:
    break;
  case FndId::ObjectSpaceManifestRootFND:
    break;
  case FndId::ReadOnlyObjectDeclaration2LargeRefCountFND:
    break;
  case FndId::ReadOnlyObjectDeclaration2RefCountFND:
    break;
  case FndId::RevisionManifestListReferenceFND:
    break;
  case FndId::RevisionManifestListStartFND:
    break;
  case FndId::RevisionManifestStart4FND:
    break;
  case FndId::RevisionManifestStart6FND:
    break;
  case FndId::RevisionManifestStart7FND:
    break;
  case FndId::RevisionRoleAndContextDeclarationFND:
    break;
  case FndId::RevisionRoleDeclarationFND:
    break;
  case FndId::RootObjectReference2FNDX:
    break;
  case FndId::RootObjectReference3FND:
    break;

  // nodes without data
  case FndId::RevisionManifestEndFND:
  case FndId::GlobalIdTableStart2FND:
  case FndId::GlobalIdTableEndFNDX:
  case FndId::ObjectGroupEndFND:
  case FndId::ChunkTerminatorFND:
    break;
  case FndId::fnd_invalid_id:
  default:
    assert(false);
    m_fnd = nullptr;
    break;
  }

  if (m_fnd != nullptr)
  {
    input >> *m_fnd;
  }

}

std::string FileNode::to_string()
{
  std::stringstream stream;

  stream << fnd_id_to_string(m_fnd_id);
  stream << "; ";
  stream << "size " << m_size_in_file << "; ";

  stream << std::hex << "base_type ";
  switch (m_base_type)
  {
  case fnd_no_data:
    stream << "fnd_no_data";
    break;
  case fnd_ref_data:
    stream << "fnd_ref_data@0x" << m_fncr.stp();
    break;
  case fnd_ref_filenodelist:
    stream << "fnd_ref_filenodelist@0x" << m_fncr.stp();
    break;
  default:
    stream << "UNKNOWN BASETYPE";
    assert(false);
    break;
  }

  return stream.str();
}

void FileNode::skip_node(const libone::RVNGInputStreamPtr_t &input)
{
  DBMSG << "Skipping file node by jumping over " << m_size_in_file << " bytes to " << m_offset + m_size_in_file << std::endl;
  input->seek(m_offset + m_size_in_file, librevenge::RVNG_SEEK_SET);
}
}


