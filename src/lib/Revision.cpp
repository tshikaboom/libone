/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iomanip>
#include "libone_utils.h"

namespace libone {

  void Revision::list_parse(librevenge::RVNGInputStream *input, FileChunkReference64 ref) {
    FileNodeList list;
    FileNode node;
    long old = input->tell();

    input->seek(ref.get_location(), librevenge::RVNG_SEEK_SET);
    list.parse_header(input);
    node.parse(input);
    guid.parse(input);
    dependent.parse(input);
    while (!node.isEnd()) {
      switch(node.get_FileNodeID()) {
        case FileNodeDescriptor::RevisionManifestStart4FND:
          skip(input, 8);
          role = readU32(input, false);
          skip(input, 2);
          break;
        case FileNodeDescriptor::RevisionManifestStart7FND:
        case FileNodeDescriptor::RevisionManifestStart6FND:
          role = readU32(input, false);
          odcsDefault = readU16(input, false);
          break;
        default:
          break;
      }
      if (node.get_FileNodeID() == FileNodeDescriptor::RevisionManifestStart7FND)
        context.parse(input);
      node.parse(input);
    }
    input->seek(old, librevenge::RVNG_SEEK_SET);
  }

  std::string Revision::to_string() {
    std::stringstream stream;
    stream << "Revision guid " << guid.to_string() << "\n";
    stream << "Revision dep " << dependent.to_string() << "\n";
    stream << "Revision root " << root_object.to_string() << "\n";
    stream << "Revision role " << role << "\n";
    stream << "Revision context " << context.to_string() << "\n";


    return stream.str();
  }

}

