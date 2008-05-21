require 'mkmf'

$CFLAGS = "-Wall"

dir_config('markdown')
create_makefile('markdown')
