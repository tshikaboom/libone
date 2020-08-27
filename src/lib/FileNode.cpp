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
  case FndId::DataSignatureGroupDefinitionFND:
    m_fnd = new DataSignatureGroupDefinitionFND();
    break;
  case FndId::FileDataStoreListReferenceFND:
    m_fnd = new FileDataStoreListReferenceFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::FileDataStoreObjectReferenceFND:
    m_fnd = new FileDataStoreObjectReferenceFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::GlobalIdTableEntry2FNDX:
    m_fnd = new GlobalIdTableEntry2FNDX();
    break;
  case FndId::GlobalIdTableEntry3FNDX:
    m_fnd = new GlobalIdTableEntry3FNDX();
    break;
  case FndId::GlobalIdTableEntryFNDX:
    m_fnd = new GlobalIdTableEntryFNDX();
    break;
  case FndId::GlobalIdTableStartFNDX:
    m_fnd = new GlobalIdTableStartFNDX();
    break;
  case FndId::HashedChunkDescriptor2FND:
    m_fnd = new HashedChunkDescriptor2FND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDataEncryptionKeyV2FNDX:
    m_fnd = new ObjectDataEncryptionKeyV2FNDX(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclaration2LargeRefCountFND:
    m_fnd =
      new ObjectDeclaration2LargeRefCountFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclaration2RefCountFND:
    m_fnd = new ObjectDeclaration2RefCountFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclarationFileData3LargeRefCountFND:
    m_fnd = new ObjectDeclarationFileData3LargeRefCountFND();
    break;
  case FndId::ObjectDeclarationFileData3RefCountFND:
    m_fnd = new ObjectDeclarationFileData3RefCountFND();
    break;
  case FndId::ObjectDeclarationWithRefCount2FNDX:
    m_fnd =
      new ObjectDeclarationWithRefCount2FNDX(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectDeclarationWithRefCountFNDX:
    m_fnd =
      new ObjectDeclarationWithRefCountFNDX(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectGroupListReferenceFND:
    m_fnd = new ObjectGroupListReferenceFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectGroupStartFND:
    m_fnd = new ObjectGroupStartFND();
    break;
  case FndId::ObjectInfoDependencyOverridesFND:
    m_fnd = new ObjectInfoDependencyOverridesFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectRevisionWithRefCount2FNDX:
    m_fnd = new ObjectRevisionWithRefCount2FNDX(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectRevisionWithRefCountFNDX:
    m_fnd = new ObjectRevisionWithRefCountFNDX(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectSpaceManifestListReferenceFND:
    m_fnd =
      new ObjectSpaceManifestListReferenceFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::ObjectSpaceManifestListStartFND:
    m_fnd = new ObjectSpaceManifestListStartFND();
    break;
  case FndId::ObjectSpaceManifestRootFND:
    m_fnd = new ObjectSpaceManifestRootFND();
    break;
  case FndId::ReadOnlyObjectDeclaration2LargeRefCountFND:
    m_fnd = new ReadOnlyObjectDeclaration2LargeRefCountFND(m_fncr.get_stp_fmt(),
                                                           m_fncr.get_cb_fmt());
    break;
  case FndId::ReadOnlyObjectDeclaration2RefCountFND:
    m_fnd =
      new ReadOnlyObjectDeclaration2RefCountFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::RevisionManifestListReferenceFND:
    m_fnd = new RevisionManifestListReferenceFND(m_fncr.get_stp_fmt(), m_fncr.get_cb_fmt());
    break;
  case FndId::RevisionManifestListStartFND:
    m_fnd = new RevisionManifestListStartFND();
    break;
  case FndId::RevisionManifestStart4FND:
    m_fnd = new RevisionManifestStart4FND();
    break;
  case FndId::RevisionManifestStart6FND:
    m_fnd = new RevisionManifestStart6FND();
    break;
  case FndId::RevisionManifestStart7FND:
    m_fnd = new RevisionManifestStart7FND();
    break;
  case FndId::RevisionRoleAndContextDeclarationFND:
    m_fnd = new RevisionRoleAndContextDeclarationFND();
    break;
  case FndId::RevisionRoleDeclarationFND:
    m_fnd = new RevisionRoleDeclarationFND();
    break;
  case FndId::RootObjectReference2FNDX:
    m_fnd = new RootObjectReference2FNDX();
    break;
  case FndId::RootObjectReference3FND:
    m_fnd = new RootObjectReference3FND();
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


