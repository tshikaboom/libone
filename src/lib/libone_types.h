/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#ifndef INCLUDED_LIBONE_TYPES_H
#define INCLUDED_LIBONE_TYPES_H

#include "Object.h"
#include "ObjectSpace.h"
#include "GUID.h"
#include "ExtendedGUID.h"
#include "FileChunkReference.h"
#include "CompactID.h"
#include "Revision.h"
#include "FileNode.h"
#include "FileNodeList.h"
#include "FileNodeDescriptor.h"
#include "TransactionEntry.h"
#include "TransactionLogFragment.h"

static std::unordered_map<std::string ,libone::Object> RootObjectSpace;
static libone::ExtendedGUID RootObject;

static std::unordered_map<std::string, libone::ObjectSpace> ObjectSpaces;
// the string is the Object's guid

static std::unordered_map<std::string, libone::ExtendedGUID> GlobalIdentificationTable;

#endif
