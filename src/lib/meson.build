## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

libone_source_files = [
    'CompactID.cpp',
    'CompactID.h',
    'Object.h',
    'Object.cpp',
    'PageMetaData.h',
    'PageMetaData.cpp',
    'ObjectGroup.h',
    'ObjectGroup.cpp',
    'ObjectSpace.cpp',
    'ObjectSpace.h',
    'ObjectSpaceStreams.cpp',
    'ObjectSpaceStreams.h',
    'ExtendedGUID.cpp',
    'ExtendedGUID.h',
    'FileChunkReference.h',
    'FileChunkReference.cpp',
    'FileNodeChunkReference.h',
    'FileNodeChunkReference.cpp',
    'FileDataStore.cpp',
    'FileDataStore.h',
    'FileNode.cpp',
    'FileNode.h',
    'FileNodeList.cpp',
    'FileNodeList.h',
    'FileNodeListFragment.cpp',
    'FileNodeListFragment.h',
    'Header.cpp',
    'Header.h',
    'JCID.h',
    'JCID.cpp',
    'OneNoteParser.h',
    'OneNoteParser.cpp',
    'PropertySet.h',
    'PropertySet.cpp',
    'PropertyID.h',
    'PropertyID.cpp',
    'Revision.cpp',
    'Revision.h',
    'TransactionEntry.h',
    'TransactionEntry.cpp',
    'TransactionLog.h',
    'TransactionLog.cpp',
    'TransactionLogFragment.h',
    'TransactionLogFragment.cpp',
    'GUID.cpp',
    'GUID.h',
    'ONEDocument.cpp',
    'StringInStorageBuffer.cpp',
    'StringInStorageBuffer.h',
    'libone_utils.cpp',
    'libone_types.h',
	'libone_utils.h'
]

libone_source_dependencies = [
	librevenge_dep,
	librevenge_stream_dep,
	librevenge_generators_dep
]

libone_include_directory = '../../inc/'

libone_target = library(
  'one',
  libone_source_files,
  install : true,
  dependencies : libone_source_dependencies,
  c_args : build_args,
  cpp_args : build_args,
  gnu_symbol_visibility : 'default',
  include_directories : libone_include_directory,
)

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
