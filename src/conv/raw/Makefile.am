## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

bin_PROGRAMS = one2raw

AM_CXXFLAGS = \
	-I$(top_srcdir)/inc \
	$(REVENGE_CFLAGS) \
	$(REVENGE_GENERATORS_CFLAGS) \
	$(REVENGE_STREAM_CFLAGS) \
	$(BOOST_CFLAGS) \
	$(DEBUG_CXXFLAGS)

one2raw_DEPENDENCIES = @ONE2RAW_WIN32_RESOURCE@ 
one2raw_LDADD = \
	../../lib/libone-@ONE_MAJOR_VERSION@.@ONE_MINOR_VERSION@.la \
	$(REVENGE_LIBS) \
	$(REVENGE_GENERATORS_LIBS) \
	$(REVENGE_STREAM_LIBS) \
	@ONE2RAW_WIN32_RESOURCE@

one2raw_SOURCES = one2raw.cpp

if OS_WIN32

@ONE2RAW_WIN32_RESOURCE@ : one2raw.rc $(one2raw_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource && \
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource one2raw.rc @ONE2RAW_WIN32_RESOURCE@

endif

# Include the one2raw_SOURCES in case we build a tarball without stream
EXTRA_DIST = \
	$(one2raw_SOURCES) \
	one2raw.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	one2raw.rc
 
## vim:set shiftwidth=4 tabstop=4 noexpandtab:
