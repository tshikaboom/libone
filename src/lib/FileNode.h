/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODE_H
#define INCLUDED_LIBONE_FILENODE_H

#include "FileChunkReference.h"
#include <librevenge-stream/librevenge-stream.h>




namespace libone {

class FileNode {
  public:
    void parse(librevenge::RVNGInputStream *input);
    std::string to_string();
    uint32_t get_FileNodeID();
    uint32_t get_Size();
    uint32_t get_StpFormat();
    uint32_t get_CbFormat();
    uint32_t get_Basetype();
    uint32_t get_D();
    bool isEnd();
    FileChunkReference get_ref();

    enum {
      ObjectSpaceManifestRootFND =          0x004,
      ObjectSpaceManifestListReferenceFND = 0x008,
      ObjectSpaceManifestListStartFND =     0x00C,
      RevisionManifestListReferenceFND =    0x010,
      RevisionManifestListStartFND =        0x014,
      RevisionManifestStart4FND =           0x01B,
      RevisionManifestEndFND =              0x01C,
      RevisionManifestStart6FND =           0x01E,
      RevisionManifestStart7FND =           0x01F,
      GlobalIdTableStartFNDX =              0x021,
      GlobalIdTableStart2FND =              0x022,
      GlobalIdTableEntryFNDX =              0x024,
      GlobalIdTableEntry2FNDX =             0x025,
      GlobalIdTableEntry3FNDX =             0x026,
      GlobalIdTableEndFNDX =                0x028,
      ObjectDeclarationWithRefCountFNDX =   0x02D,
      ObjectDeclarationWithRefCount2FNDX =  0x02E,
      ObjectRevisionWithRefCountFNDX =      0x041,
      ObjectRevisionWithRefCount2FNDX =     0x042,
      RootObjectReference2FNDX =            0x059,
      RootObjectReference3FND =             0x05A,
      RevisionRoleDeclarationFND =          0x05C,
      RevisionRoleAndContextDeclarationFND =0x05D,
      ObjectDeclarationFileData3RefCountFND=0x072,
      ObjectDeclarationFileData3LargeRefCountFND = 0x073,
      ObjectDataEncryptionKeyV2FNDX = 0x07C,
      ObjectInfoDependencyOverridesFND = 0x084,
      DataSignatureGroupDefinitionFND = 0x08C,
      FileDataStoreListReferenceFND = 0x090,
      FileDataStoreObjectReferenceFND = 0x094,
      ObjectDeclaration2RefCountFND = 0x0A4,
      ObjectDeclaration2LargeRefCountFND = 0x0A5,
      ObjectGroupListReferenceFND = 0x0B0,
      ObjectGroupStartFND = 0x0B4,
      ObjectGroupEndFND = 0x0B8,
      HashedChunkDescriptor2FND = 0x0C2,
      ReadOnlyObjectDeclaration2RefCountFND = 0x0C4,
      ReadOnlyObjectDeclaration2LargeRefCountFND = 0x0F5,
      ChunkTerminatorFND = 0x0FF,
      TYPES_END = 0x0
      } types = TYPES_END;


  private:
    uint32_t FileNodeID = 0;
    uint32_t Size = 0;
    uint16_t StpFormat = 0, CbFormat = 0, BaseType = 0, d = 0;
    static uint32_t const IDMask = 0xFFC00000;
    static uint32_t const SizeMask = 0x3FFE00;
    static uint32_t const ABCDMask = 0x1FF;
    bool is_end = false;
    void parse_header(librevenge::RVNGInputStream *input);
		FileChunkReference ref = FileChunkReference();


};


}

#endif
