## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-


one2raw_sources = [
    'one2raw.cpp'
    ]

one2raw_dependencies = [
    libone_dep,
    librevenge_dep,
    librevenge_generators_dep,
    librevenge_stream_dep
    ]


one2raw_build_args = []

one2raw_target = executable(
  'one2raw',
  one2raw_sources,
  dependencies: one2raw_dependencies,
  install : true,
  c_args : one2raw_build_args,
  cpp_args : one2raw_build_args,
)

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
