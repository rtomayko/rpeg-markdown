
require 'rake/clean'

DLEXT = Config::CONFIG['DLEXT']


desc 'Gather required peg-markdown sources into extension directory'
task :gather do |t|
  sh 'cd peg-markdown && make markdown_parser.c'
  cp FileList['peg-markdown/markdown_{peg.h,parser.c,output.c}'], 'ext/',
    :preserve => true,
    :verbose => true
end
CLOBBER.include 'ext/markdown_{peg.h,parser.c,output.c}'

file 'ext/Makefile' => FileList['ext/{extconf.rb,*.c,*.h,*.rb}'] do
  chdir('ext') { ruby 'extconf.rb' }
end
CLEAN.include 'ext/Makefile'

file "ext/markdown.#{DLEXT}" => FileList['ext/Makefile', 'ext/*.{c,h,rb}'] do |f|
  sh 'cd ext && make'
end
CLEAN.include 'ext/*.{o,bundle,so}'

file "lib/markdown.#{DLEXT}" => "ext/markdown.#{DLEXT}" do |f|
  cp f.prerequisites, "lib/", :preserve => true
end

desc 'Build the peg-markdown extension'
task :build => "lib/markdown.#{DLEXT}"
