## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

conf_data = configuration_data()
conf_data.set('DOXYGEN_INPUT', meson.source_root() + '/src/lib')
conf_data.set('DOXYGEN_OUTPUT', meson.current_build_dir())
conf_data.set('HTML_HEADER', meson.source_root() + '/docs/doxygen/header.html.in')
conf_data.set('HTML_FOOTER', meson.source_root() + '/docs/doxygen/footer.html.in')

doxyfile = configure_file(
input: 'doxygen.cfg',
output: 'Doxyfile',
configuration: conf_data
)

custom_target('docs',
build_by_default: true,
command: [doxygen, doxyfile],
output: ['html']
)
## vim:set shiftwidth=4 tabstop=4 noexpandtab:
