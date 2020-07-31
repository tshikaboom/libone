#DNL -*- MODE: AUTOCONF; TAB-WIDTH: 4; INDENT-TABS-MODE: NIL; FILL-COLUMN: 102 -*-
# ==================
# Initialize Project
# ==================
project(
    'libone',
    ['cpp', 'c'],
    version : '0.1.0',
    license : 'MPL 2.0+',
    default_options : [
        'cpp_std=c++11',
        'debug=false',
        'werror=true',
        'warning_level=3',
        ],
    )

project_description = 'A library to read and write MS-ONESTORE files'
project_basename = 'one'

# ====================
# Version informations
# ====================
libone_version = meson.project_version() # set in project() below
ver_arr = libone_version.split('.')

libone_major_version = ver_arr[0].to_int()
libone_minor_version = ver_arr[1].to_int()
libone_micro_version = ver_arr[2].to_int()

# ==========================
# platform specific compiler
# ==========================
cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# ===========
# Auto header
# ===========
cdata = configuration_data()

cdata.set10('HAVE_CONFIG_H', true)

cdata.set_quoted('PACKAGE', meson.project_name())
cdata.set_quoted('PACKAGE_NAME', meson.project_name())
cdata.set_quoted('PACKAGE_TARNAME', meson.project_name())
cdata.set_quoted('PACKAGE_STRING', meson.project_name() + ' ' + libone_version)
cdata.set_quoted('PACKAGE_VERSION', libone_version)
cdata.set_quoted('PACKAGE_URL', 'https://github.com/tshikaboom/libone/')
cdata.set_quoted('PACKAGE_BUGREPORT', '')
cdata.set_quoted('VERSION', libone_version)


# derived from configure script, but seem to only be related to C
#TODO Likely can be replaced with C++ std libraries
have_stdint = false
have_inttypes = false

if cpp.has_header('inttypes.h')
    have_inttypes = true
endif
cdata.set10('HAVE_INTTYPES_H', have_inttypes)

have_stdint = false
if cpp.has_header('stdint.h')
    have_stdint = true
endif
cdata.set10('HAVE_STDINT_H', have_stdint)

doxygen = find_program('doxygen', required : true)
if doxygen.found()
  cdata.set('HAVE_DOXYGEN', 1)
else
    message('*** Could not find doxygen in your PATH.\n')
    message('*** The documentation will not be built.\n')
endif

#
cdata.set10('DEBUG', get_option('debug'))

# Finalize and write config.h
configure_file(output : 'config.h',
               configuration : cdata)

# ====================
# Find additional apps
# ====================
librevenge_dep = dependency('librevenge-0.0', required : true)
librevenge_generators_dep = dependency('librevenge-generators-0.0', required : true)
librevenge_stream_dep     = dependency('librevenge-stream-0.0', required : true)

# =================================
# Libtool equivalent
# =================================
# TODO libary is currently without version spec in compiled file name

# libone_current_version= 100 * libone_major_version + libone_minor_version
# libone_age_version=0
#
# # soversion = current - age
# libone_soversion = '@0@'.format(libone_current_version - libone_age_version)

# ==============
# Platform check
# ==============
os_linux  = false
os_win32  = false
os_cygwin = false
os_macos  = false

host_system = host_machine.system()

if host_system == 'windows'
    os_win32 = true
elif host_system == 'cygwin'
    os_cygwin = true
elif host_system == 'linux'
    os_linux = true
elif host_system == 'darwin'
    os_macos = true
else
    error('Unsopported OS.')
endif

# ==================
# Compiler arguments
# ==================
common_flags = ['-pedantic', '-Wshadow']
add_project_arguments(common_flags, language: 'cpp')

cpp_args = []

# Courtesy of Glib: Ensure MSVC-compatible struct packing convention
# is used when compiling for Win32 with gcc.
win32_cpp_args = []
win32_ldflags = []

if os_win32 and cc.get_id() != 'msvc'
    # Ensure MSVC-compatible struct packing convention is used when
    # compiling for Win32 with gcc. It is used for the whole project and exposed

    win32_cpp_args += ['-mms-bitfields']
    add_project_arguments(win32_cpp_args, language : 'cpp')

    win32_ldflags = ['']
elif os_cygwin
    win32_ldflags = ['']
else
    message('produced libraries might be incompatible with MSVC-compiled code')
endif

if get_option('weffc')
    cpp_args += ['-Weffc++']
endif

if get_option('wparanoic')
    cpp_args += [
        '-Wcast-align',
        '-Wcast-qual',
        '-Wchar-subscripts',
        '-Wcomment',
        '-Wconversion',
        '-Wdisabled-optimization',
        '-Wfloat-equal',
        '-Wformat',
        '-Wformat=2',
        '-Wformat-nonliteral',
        '-Wformat-security',
        '-Wformat-y2k',
        '-Wimport',
        '-Winit-self',
        '-Winvalid-pch',
        '-Wmissing-braces',
        '-Wmissing-field-initializers',
        '-Wmissing-format-attribute',
        '-Wmissing-include-dirs',
        '-Wmissing-noreturn',
        '-Wpacked',
        '-Wparentheses',
        '-Wpointer-arith',
        '-Wredundant-decls',
        '-Wreturn-type',
        '-Wsequence-point',
        '-Wsign-compare',
        '-Wstrict-aliasing',
        '-Wstrict-aliasing=2',
        '-Wswitch',
        '-Wswitch-default',
        '-Wswitch-enum',
        '-Wtrigraphs',
        '-Wunknown-pragmas',
        '-Wunused',
        '-Wunused-function',
        '-Wunused-label',
        '-Wunused-parameter',
        '-Wunused-value',
        '-Wvariadic-macros',
        '-Wvolatile-register-var',
        '-Wwrite-strings',
        ]
endif
add_project_arguments(cpp_args, language: 'cpp')

# ============
# Debug switch
# ============
debug_cpp_args = []

if get_option('debug')
    debug_cpp_args += ['-DDEBUG -g']
    cpp_args += ['-O0']
else
    debug_cpp_args += ['-DNDEBUG']
endif
add_project_arguments(debug_cpp_args, language: 'cpp')

# ==============
# Library Target
# ==============
libone_headers = [
  'inc/libone/libone.h',
  'inc/libone/ONEDocument.h'
]

libone_includes = include_directories('inc')

build_args = [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
]

# Only make public interfaces visible
if target_machine.system() == 'windows' or target_machine.system() == 'cygwin'
  build_args += '-DLIBONE_PUBLIC="__declspec(dllexport)"'
else
  build_args += '-DLIBONE_PUBLIC=__attribute__((visibility("default")))'
endif

subdir('src/lib')

# =========
# Packaging
# =========

# Make this library usable as a Meson subproject.
libone_dep = declare_dependency(
  include_directories: [libone_includes],
  link_with : libone_target
)
set_variable(meson.project_name() + '_dep', libone_dep)

# Make this library usable from the system's
# package manager.
install_headers(libone_headers, subdir : meson.project_name())

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
  libraries : libone_target,
)

# ==========
# Unit Tests
# ==========
if get_option('tests')
    subdir('src/test')
endif

# ================
# Conversion tools
# ================
if get_option('tools')
    subdir('src/conv')
endif

# =============
# Documentation
# =============
if get_option('docs')
  if doxygen.found()
    subdir('docs')
  endif
endif

# ==============================================
# Display final informations about configuration
# ==============================================

#TODO use summary()
lines = [
    'prefix:    ' + get_option('prefix'),
    'libdir:    ' + get_option('libdir'),
    '',
]

lines += 'debug:       ' + (get_option('debug') ? 'yes' : 'no')
lines += 'docs:        ' + (get_option('docs') ? 'yes' : 'no')
lines += 'tests:       ' + (get_option('tests') ? 'yes' : 'no')
lines += 'tools:       ' + (get_option('tools') ? 'yes' : 'no')
lines += 'werror:      ' + (get_option('werror') ? 'yes' : 'no')
lines += 'weffc:       ' + (get_option('weffc') ? 'yes' : 'no')
lines += 'wparanoic:   ' + (get_option('wparanoic') ? 'yes' : 'no')


indent = '    '

params = indent + ('\n' + indent + ('\n' + indent).join(lines))

build_config_info = ('\n\n')
build_config_info += ('==============================================================================\n')
build_config_info += ('Build configuration:\n')
build_config_info += ('@0@\n\n'.format(params))
build_config_info += ('==============================================================================\n')

message(build_config_info)
