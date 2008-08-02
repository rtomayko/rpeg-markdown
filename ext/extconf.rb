require 'mkmf'

dir_config('peg_markdown')

$objs = %w[markdown.o markdown_lib.o markdown_output.o markdown_parser.o]

if pkg_config = find_executable('pkg-config')
  $CFLAGS = `#{pkg_config} --cflags glib-2.0`
  $LDFLAGS = `#{pkg_config} --libs glib-2.0`
else
  fail "glib2 not found"
end

create_header
create_makefile('peg_markdown')
