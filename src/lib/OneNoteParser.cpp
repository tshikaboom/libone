/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cassert>
#include "libone_utils.h"
#include "libone_types.h"
#include "OneNoteParser.h"
#include "Object.h"
#include "FileDataStore.h"
#include "TransactionLog.h"

namespace libone
{

libone::ExtendedGUID DataSignatureGroup = libone::ExtendedGUID();

OneNoteParser::OneNoteParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *const document)
{
  Header header = Header();
  libone::ExtendedGUID RootObject;

  header.parse(input);

  input->seek(0, librevenge::RVNG_SEEK_SET);

  ONE_DEBUG_MSG(("trying transactions, jumping to %ld\n", header.fcrTransactionLog.get_location()));
  input->seek(header.fcrTransactionLog.get_location(), librevenge::RVNG_SEEK_SET);



  ONE_DEBUG_MSG(("test fileNodeList\n"));
  parse_root_file_node_list(input, header, RootObject);
  ONE_DEBUG_MSG(("root object is %s\n", RootObject.to_string().c_str()));

  for (auto i: ObjectSpaces)
  {
    ONE_DEBUG_MSG(("object space %s\n", i.first.c_str()));
  }

  // TODO: replace with proper transaction implementation
  parse_transactions(input, header);

  ObjectSpaces[RootObject.to_string()].to_document(document);

  ONE_DEBUG_MSG(("nothing broke!\n"));

}

void OneNoteParser::parse_transactions(librevenge::RVNGInputStream *input, Header &header)
{
  TransactionLog log = TransactionLog(header.fcrTransactionLog.get_location(),
                                      header.fcrTransactionLog.get_size(),
                                      header.cTransactionsInLog);
  log.parse(input);
}

void OneNoteParser::parse_root_file_node_list(librevenge::RVNGInputStream *input,
                                              Header &header, ExtendedGUID &root_object)
{
  ExtendedGUID guid;
  std::vector<ObjectSpace> object_spaces = std::vector<ObjectSpace>();
  FileDataStore store;
  FileNodeList list(header.fcrFileNodeListRoot.get_location(), header.fcrFileNodeListRoot.get_size());
  (void) store;

  list.parse(input);

  DBMSG << "iterating on a " << list.get_fnd_list().size() << " size list" << std::endl;

  for (FileNode &node : list.get_fnd_list())
  {
    ObjectSpace object_space = ObjectSpace();
    DBMSG << node.to_string() << std::endl;

    switch (node.get_FileNodeID())
    {
    case ObjectSpaceManifestRootFND:
      input->seek(node.get_location() + node.header_size, librevenge::RVNG_SEEK_SET);
      root_object.parse(input);
      break;
    case ObjectSpaceManifestListReferenceFND:
      object_space.parse(input, node);
      break;
    case FileDataStoreListReferenceFND:
    // TODO: The majority of these file nodes do not appear in
    // the root file node list. Maybe do some more paranoiac checks
    // to that effect instead of just breaking out of the switch.
    case ObjectSpaceManifestListStartFND:
    case RevisionManifestListReferenceFND:
    case RevisionManifestListStartFND:
    case RevisionManifestStart4FND:
    case RevisionManifestEndFND:
    case RevisionManifestStart6FND:
    case RevisionManifestStart7FND:
    case GlobalIdTableStartFNDX:
    case GlobalIdTableStart2FND:
    case GlobalIdTableEntryFNDX:
    case GlobalIdTableEntry2FNDX:
    case GlobalIdTableEntry3FNDX:
    case GlobalIdTableEndFNDX:
    case ObjectDeclarationWithRefCountFNDX:
    case ObjectDeclarationWithRefCount2FNDX:
    case ObjectRevisionWithRefCountFNDX:
    case ObjectRevisionWithRefCount2FNDX:
    case RootObjectReference2FNDX:
    case RootObjectReference3FND:
    case RevisionRoleDeclarationFND:
    case RevisionRoleAndContextDeclarationFND:
    case ObjectDeclarationFileData3RefCountFND:
    case ObjectDeclarationFileData3LargeRefCountFND:
    case ObjectDataEncryptionKeyV2FNDX:
    case ObjectInfoDependencyOverridesFND:
    case DataSignatureGroupDefinitionFND:
    case FileDataStoreObjectReferenceFND:
    case ObjectDeclaration2RefCountFND:
    case ObjectDeclaration2LargeRefCountFND:
    case ObjectGroupListReferenceFND:
    case ObjectGroupStartFND:
    case ObjectGroupEndFND:
    case HashedChunkDescriptor2FND:
    case ReadOnlyObjectDeclaration2RefCountFND:
    case ReadOnlyObjectDeclaration2LargeRefCountFND:
    case ChunkTerminatorFND:
      break;
    case fnd_invalid_id:
    default:
      assert(false);
      break;
    }
  }

}

std::unordered_map<uint32_t, libone::GUID> GlobalIdentificationTable = std::unordered_map<uint32_t, libone::GUID>();

}
