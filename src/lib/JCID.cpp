/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>
#include "JCID.h"

namespace libone
{

JCID::JCID() : value{} {}

void JCID::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> value;
}

const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, JCID &obj)
{
  obj.parse(input);
  return input;
}

std::string JCID::to_string()
{
  std::stringstream stream;
  switch (get_value())
  {
  case jcidReadOnlyPersistablePropertyContainerForAuthor:
    stream << "jcidReadOnlyPersistablePropertyContainerForAuthor";
    break;
  case jcidPersistablePropertyContainerForTOC:
    stream << "jcidPersistablePropertyContainerTOC";
    break;
  case jcidSectionNode:
    stream << "jcidSectionNode";
    break;
  case jcidPageSeriesNode:
    stream << "jcidPageSeriesNode";
    break;
  case jcidPageNode:
    stream << "jcidPageNode";
    break;
  case jcidOutlineNode:
    stream << "jcidOutlineNode";
    break;
  case jcidOutlineElementNode:
    stream << "jcidOutlineElementNode";
    break;
  case jcidRichTextOENode:
    stream << "jcidRichTextOENode";
    break;
  case jcidImageNode:
    stream << "jcidImageNode";
    break;
  case jcidNumberListNode:
    stream << "jcidNumberListNode";
    break;
  case jcidOutlineGroup:
    stream << "jcidOutlineGroup";
    break;
  case jcidTableNode:
    stream << "jcidTableNode";
    break;
  case jcidTableRowNode:
    stream << "jcidTableRowNode";
    break;
  case jcidTableCellNode:
    stream << "jcidTableCellNode";
    break;
  case jcidTitleNode:
    stream << "jcidTitleNode";
    break;
  case jcidPageMetaData:
    stream << "jcidPageMetaData";
    break;
  case jcidSectionMetaData:
    stream << "jcidSectionMetaData";
    break;
  case jcidEmbeddedFileNode:
    stream << "jcidEmbeddedFileNode";
    break;
  case jcidPageManifestNode:
    stream << "jcidPageManifestNode";
    break;
  case jcidConflictPageMetaData:
    stream << "jcidConflictPageMetaData";
    break;
  case jcidVersionHistoryContent:
    stream << "jcidVersionHistoryContent";
    break;
  case jcidVersionProxy:
    stream << "jcidVersionProxy";
    break;
  case jcidNoteTagSharedDefinitionContainer:
    stream << "jcidNoteTagSharedDefinitionContainer";
    break;
  case jcidRevisionMetaData:
    stream << "jcidRevisionMetaData";
    break;
  case jcidVersionHistoryMetaData:
    stream << "jcidVersionHistoryMetaData";
    break;
  case jcidParagraphStyleObject:
    stream << "jcidParagraphStyle";
    break;
  default:
    stream << std::hex << get_value() << " unknown";
    break;
  }
  return stream.str();
}

}

