## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-
# ==========
# Unit Tests
# ==========

 test_dir = '.'
# test_incdir = include_directories(join_paths(test_dir, 'inc'), is_system : true)

libone_test = static_library(
  'libone_test',
  cpp_args : ['-w'],
  # include_directories : [include_directories(test_dir), test_incdir],
  sources : [
    join_paths(test_dir, 'test.cpp'),
  ]
)

test_dep = declare_dependency(
  dependencies : [
      dependency('threads'),
      dependency('cppunit'),
      librevenge_dep,
      librevenge_generators_dep,
      librevenge_stream_dep,
      ],

  # include_directories : test_i constncdir,
  link_with : libone_test
)

libone_test_files = [
  'test.cpp',
  'common-types/GUIDTest.h',
  'common-types/GUIDTest.cpp'
]

if not meson.is_subproject()
  test('all_tests',
    executable(
      'run_tests',
      files(libone_test_files),
      dependencies : [libone_dep, test_dep],
      install : false
    )
  )
endif
## vim:set shiftwidth=4 tabstop=4 noexpandtab:
