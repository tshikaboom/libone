## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-


one2svg_sources = [
    'one2svg.cpp'
    ]

one2svg_dependencies = [
    librevenge_dep,
    librevenge_generators_dep,
    librevenge_stream_dep,
    libone_dep,
    ]


one2svg_build_args = []

one2svg_target = executable(
  'one2svg',
  one2svg_sources,
  dependencies: one2svg_dependencies,
  include_directories : '../../../inc',
  install : true,
  cpp_args : one2svg_build_args,
  link_language : 'cpp'
)

test('basic', one2svg_target)
## vim:set shiftwidth=4 tabstop=4 noexpandtab:
