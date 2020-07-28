/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_ONENOTEPARSER_H
#define INCLUDED_LIBONE_ONENOTEPARSER_H

#include <librevenge-stream/librevenge-stream.h>
#include "libone_types.h"

#include <algorithm>
#include <cstring>
#include <iostream>

#include <librevenge-stream/librevenge-stream.h>

#include <libone/libone.h>
#include <libone/ONEDocument.h>
#include "libone_utils.h"

namespace libone
{
class OneNoteParser
{
public:
  OneNoteParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *const document);

private:
  std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces = std::unordered_map<std::string, libone::ObjectSpace>();

  void parse_root_file_node_list(librevenge::RVNGInputStream *input,
                                 Header &header, ExtendedGUID &root_object);
  void parse_transactions(librevenge::RVNGInputStream *input, Header &header);
};



}

#endif
