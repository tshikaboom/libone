## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

if PLATFORM_WIN32
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -avoid-version
else
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
endif

lib_LTLIBRARIES = libone-@ONE_MAJOR_VERSION@.@ONE_MINOR_VERSION@.la
libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_includedir = $(includedir)/libone-@ONE_MAJOR_VERSION@.@ONE_MINOR_VERSION@/libone
libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_include_HEADERS = \
	$(top_srcdir)/inc/libone/ONEDocument.h \
	$(top_srcdir)/inc/libone/libone.h

AM_CXXFLAGS = \
	-DLIBONE_BUILD=1 \
	-I$(top_srcdir)/inc \
	$(REVENGE_CFLAGS) \
	$(REVENGE_STREAM_CFLAGS) \
	$(BOOST_CFLAGS) \
	$(DEBUG_CXXFLAGS)

libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_la_LIBADD = \
	$(REVENGE_LIBS) \
	@LIBONE_WIN32_RESOURCE@

libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_la_DEPENDENCIES = @LIBONE_WIN32_RESOURCE@
libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic -no-undefined
libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_la_SOURCES = \
	ONEDocument.cpp \
	libone_utils.cpp \
	guid.cpp \
	FileChunkReference32.cpp \
	FileChunkReference64.cpp \
	FileChunkReference64x32.cpp \
	FileNodeListFragment.cpp \
	FileNode.cpp \
	libone_utils.h

if OS_WIN32

@LIBONE_WIN32_RESOURCE@ : libone.rc $(libone_@ONE_MAJOR_VERSION@_@ONE_MINOR_VERSION@_la_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource libone.rc @LIBONE_WIN32_RESOURCE@

endif

EXTRA_DIST = \
	libone.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	libone.rc

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
