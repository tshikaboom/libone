#ifndef INCLUDED_LIBONE_TYPES_H
#define INCLUDED_LIBONE_TYPES_H

#include "Object.h"
#include "GUID.h"
#include "ExtendedGUID.h"
#include "FileChunkReference.h"
#include "CompactID.h"
#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "FileNodeDescriptor.h"
#include "TransactionEntry.h"
#include "TransactionLogFragment.h"

static std::unordered_map<std::string ,libone::Object> ObjectMap;// = std::unordered_map<struct _guid, Object>();

#endif
