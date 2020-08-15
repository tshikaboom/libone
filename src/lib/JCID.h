/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_JCID_H
#define INCLUDED_LIBONE_JCID_H

#include <string>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>
#include "libone_utils.h"

namespace libone
{

class JCID
{
public:
  JCID();
  JCID(uint32_t val)
  {
    value = val;
  }
  uint32_t get_value()
  {
    return value;
  }
  uint16_t index()
  {
    return (value & 0xFFFF);
  }
  uint16_t IsBinary()
  {
    return (value & 0x10000) >> 16;
  }
  uint16_t IsPropertySet()
  {
    return (value & 0x20000) >> 17;
  }
  uint16_t IsGraphNode()
  {
    return (value & 0x40000) >> 18;
  }
  uint16_t IsFileData()
  {
    return (value & 0x80000) >> 19;
  }
  uint16_t IsReadOnly()
  {
    return (value & 0x100000) >> 20;
  }
  void set_IsReadOnly(bool val)
  {
    value |= (val << 20);
  }
  void set_IsFileData(bool val)
  {
    value |= (val << 19);
  }
  void set_IsGraphNode(bool val)
  {
    value |= (val << 18);
  }
  void set_IsPropertySet(bool val)
  {
    value |= (val << 17);
  }
  void set_IsBinary(bool val)
  {
    value |= (val << 16);
  }
  void set_index(uint16_t val)
  {
    value |= val;
  }
  std::string to_string();

  enum
  {
    jcidReadOnlyPersistablePropertyContainerForAuthor = 0x00120001,
    jcidPersistablePropertyContainerForTOC = 0x00020001,
    jcidPersistablePropertyContainerForTOCSection = 0x00020001,
    jcidSectionNode = 0x00060007,
    jcidPageSeriesNode = 0x00060008,
    jcidPageNode = 0x0006000B,
    jcidOutlineNode = 0x0006000C,
    jcidOutlineElementNode = 0x0006000D,
    jcidRichTextOENode = 0x0006000E,
    jcidImageNode = 0x00060011,
    jcidNumberListNode = 0x00060012,
    jcidOutlineGroup = 0x00060019,
    jcidTableNode = 0x00060022,
    jcidTableRowNode = 0x00060023,
    jcidTableCellNode = 0x00060024,
    jcidTitleNode = 0x0006002C,
    jcidPageMetaData = 0x00020030,
    jcidSectionMetaData = 0x00020031,
    jcidEmbeddedFileNode = 0x00060035,
    jcidPageManifestNode = 0x00060037,
    jcidConflictPageMetaData = 0x00020038,
    jcidVersionHistoryContent = 0x0006003C,
    jcidVersionProxy = 0x0006003D,
    jcidNoteTagSharedDefinitionContainer = 0x00120043,
    jcidRevisionMetaData = 0x00020044,
    jcidVersionHistoryMetaData = 0x00020046,
    jcidParagraphStyleObject = 0x0012004D,
    jcidParagraphStyleObjectForText = 0x0012004D,
    NIL = 0
  } JCID_types = NIL;


  void parse(const libone::RVNGInputStreamPtr_t &input);

  friend const libone::RVNGInputStreamPtr_t &operator>>(const libone::RVNGInputStreamPtr_t &input, JCID &obj);

private:
  uint32_t value = 0;
};

}

#endif
