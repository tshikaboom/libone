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

namespace libone
{

std::string fnd_id_to_string(enum fnd_id id_fnd)
{
  std::stringstream stream;

  switch (id_fnd)
  {
  case fnd_id::ObjectSpaceManifestListStartFND:
    stream << "ObjectSpaceManifestListStartFND";
    break;
  case fnd_id::ChunkTerminatorFND:
    stream << "ChunkTerminatorFND";
    break;
  case fnd_id::RevisionManifestListStartFND:
    stream << "RevisionManifestListStart";
    break;
  case fnd_id::RevisionManifestStart4FND:
    stream << "RevisionManifestStart4FND";
    break;
  case fnd_id::RevisionManifestStart6FND:
    stream << "RevisionManifestStart6FND";
    break;
  case fnd_id::RevisionManifestStart7FND:
    stream << "RevisionManifestStart";
    break;
  case fnd_id::RevisionManifestListReferenceFND:
    stream << "RevisionManifestListReferenceFND";
    break;
  case fnd_id::ObjectGroupListReferenceFND:
    stream << "ObjectGroupListReferenceFND";
    break;
  case fnd_id::ObjectSpaceManifestListReferenceFND:
    stream << "ObjectSpaceManifestListReferenceFND";
    break;
  case fnd_id::ObjectSpaceManifestRootFND:
    stream << "ObjectSpaceManifestListRootFND";
    break;
  case fnd_id::FileDataStoreListReferenceFND:
    stream << "FileDataStoreListReferenceFND";
    break;
  case fnd_id::ObjectGroupStartFND:
    stream << "ObjectGroupStartFND";
    break;
  case fnd_id::GlobalIdTableStart2FND:
    stream << "GlobalIdTableStart2FND";
    break;
  case fnd_id::GlobalIdTableEntryFNDX:
    stream << "GlobalIdTableEntryFNDX";
    break;
  case fnd_id::GlobalIdTableEndFNDX:
    stream << "GlobalIdTableEndFNDX";
    break;
  case fnd_id::DataSignatureGroupDefinitionFND:
    stream << "DataSignatureGroupDefinitionFND";
    break;
  case fnd_id::ObjectDeclaration2RefCountFND:
    stream << "ObjectDeclaration2RefCountFND";
    break;
  case fnd_id::ObjectGroupEndFND:
    stream << "ObjectGroupEndFND";
    break;
  case fnd_id::GlobalIdTableStartFNDX:
    stream << "GlobalIdTableStartFNDX";
    break;
  case fnd_id::GlobalIdTableEntry2FNDX:
    stream << "GlobalIdTableEntry2FNDX";
    break;
  case fnd_id::GlobalIdTableEntry3FNDX:
    stream << "GlobalIdTableEntry3FNDX";
    break;
  case fnd_id::ObjectDeclarationWithRefCountFNDX:
    stream << "ObjectDeclarationWithRefCountFNDX";
    break;
  case fnd_id::ObjectDeclarationWithRefCount2FNDX:
    stream << "ObjectDeclarationWithRefCount2FNDX";
    break;
  case fnd_id::ObjectRevisionWithRefCountFNDX:
    stream << "ObjectRevisionWithRefCountFNDX";
    break;
  case fnd_id::ObjectRevisionWithRefCount2FNDX:
    stream << "ObjectRevisionWithRefCount2FNDX";
    break;
  case fnd_id::RootObjectReference2FNDX:
    stream << "RootObjectReference2FNDX";
    break;
  case fnd_id::RootObjectReference3FND:
    stream << "RootObjectReference3FND";
    break;
  case fnd_id::RevisionRoleDeclarationFND:
    stream << "RevisionRoleDeclarationFND";
    break;
  case fnd_id::RevisionRoleAndContextDeclarationFND:
    stream << "RevisionRoleAndContextDeclarationFND";
    break;
  case fnd_id::ObjectDeclarationFileData3RefCountFND:
    stream << "ObjectDeclarationFileData3RefCountFND";
    break;
  case fnd_id::ObjectDeclarationFileData3LargeRefCountFND:
    stream << "ObjectDeclarationFileData3LargeRefCountFND";
    break;
  case fnd_id::ObjectDataEncryptionKeyV2FNDX:
    stream << "ObjectDataEncryptionKeyV2FNDX";
    break;
  case fnd_id::ObjectInfoDependencyOverridesFND:
    stream << "ObjectInfoDependencyOverridesFND";
    break;
  case fnd_id::FileDataStoreObjectReferenceFND:
    stream << "FileDataStoreObjectReferenceFND";
    break;
  case fnd_id::ObjectDeclaration2LargeRefCountFND:
    stream << "ObjectDeclaration2LargeRefCountFND";
    break;
  case fnd_id::HashedChunkDescriptor2FND:
    stream << "HashedChunkDescriptor2FND";
    break;
  case fnd_id::ReadOnlyObjectDeclaration2RefCountFND:
    stream << "ReadOnlyObjectDeclaration2RefCountFND";
    break;
  case fnd_id::ReadOnlyObjectDeclaration2LargeRefCountFND:
    stream << "ReadOnlyObjectDeclaration2LargeRefCountFND";
    break;
  case fnd_id::RevisionManifestEndFND:
    stream << "RevisionManifestEndFND";
    break;
  case fnd_id::fnd_invalid_id:
  default:
    stream << "dunno but value is " << id_fnd;
    break;
  }
  return stream.str();
}

void FileNode::parse(librevenge::RVNGInputStream *input)
{
  m_offset = input->tell();

  DBMSG << "Will parse at " << m_offset << std::endl;

  parse_header(input);
  switch (m_fnd_id)
  {
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
  case fnd_id::GlobalIdTableStartFNDX:
  case fnd_id::GlobalIdTableEntry2FNDX:
  case fnd_id::GlobalIdTableEntry3FNDX:
  case fnd_id::ObjectDeclarationWithRefCountFNDX:
  case fnd_id::ObjectDeclarationWithRefCount2FNDX:
  case fnd_id::ObjectRevisionWithRefCountFNDX:
  case fnd_id::ObjectRevisionWithRefCount2FNDX:
  case fnd_id::RootObjectReference2FNDX:
  case fnd_id::RevisionRoleDeclarationFND:
  case fnd_id::RevisionRoleAndContextDeclarationFND:
  case fnd_id::ObjectDeclarationFileData3LargeRefCountFND:
  case fnd_id::ObjectDataEncryptionKeyV2FNDX:
  case fnd_id::ObjectDeclaration2LargeRefCountFND:
  case fnd_id::HashedChunkDescriptor2FND:
  case fnd_id::ReadOnlyObjectDeclaration2LargeRefCountFND:
  case fnd_id::ChunkTerminatorFND:
    break;
  case fnd_id::fnd_invalid_id:
  default:
    DBMSG << "dunno but value is " << m_fnd_id << std::endl;
    assert(false);
    break;
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
    stream << "fnd_ref_data@0x" << m_fnd.get_location();
    break;
  case fnd_ref_filenodelist:
    stream << "fnd_ref_filenodelist@0x" << m_fnd.get_location();
    break;
  case fnd_invalid_basetype:
  default:
    stream << "UNKNOWN BASETYPE";
    assert(false);
    break;
  }

  return stream.str();
}

void FileNode::parse_header(librevenge::RVNGInputStream *input)
{
  uint32_t temp;
  enum stp_format format_stp;
  enum cb_format format_cb;
  int d;

  temp = readU32(input, false);
  d = temp >> 31;
  format_stp = static_cast<stp_format>((temp >> shift_format_stp) & mask_format_stp);
  format_cb = static_cast<cb_format>((temp >> shift_format_cb) & mask_format_cb);
  m_base_type = static_cast<fnd_basetype>((temp >> shift_base_type) & mask_fnd_base_type);
  m_fnd_id = static_cast<fnd_id>(temp & mask_fnd_id);
  m_size_in_file = (temp >> shift_fnd_size) & mask_fnd_size;
  if (d == 0)
  {
    std::bitset<13> z(m_size_in_file);
    ONE_DEBUG_MSG(("%s\n", z.to_string().c_str()));
    ONE_DEBUG_MSG(("warning: d is zero\n"));
  }
  assert(d == 1);
  FileNodeChunkReference reference(format_stp, format_cb, input->tell());

  std::bitset<32> y(temp);
  ONE_DEBUG_MSG((" filenode bits %s\n", y.to_string().c_str()));
  switch (m_base_type)
  {
  case fnd_ref_data:
  case fnd_ref_filenodelist:
    reference.parse(input);
    ONE_DEBUG_MSG(("\n"));
    break;
  case fnd_no_data:
    reference.set_zero();
    break;
  case fnd_invalid_basetype:
  default:
    assert(false);
    break;
  }
  m_fnd = reference;
}

void FileNode::skip_node(librevenge::RVNGInputStream *input)
{
  DBMSG << "Skipping file node by jumping over " << m_size_in_file << " bytes to " << m_offset + m_size_in_file << std::endl;
  input->seek(m_offset + m_size_in_file, librevenge::RVNG_SEEK_SET);
}
}


