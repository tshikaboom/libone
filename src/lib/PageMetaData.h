/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_PAGEMETADATA_H
#define INCLUDED_LIBONE_PAGEMETADATA_H

#include <librevenge-stream/librevenge-stream.h>
#include "libone_types.h"

#include "Object.h"

namespace libone
{
class PageMetaData: public Object
{
public:
  PageMetaData(librevenge::RVNGInputStream *input, struct object_header _header);
};



}

#endif
