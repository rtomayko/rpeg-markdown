require 'rake/clean'
require 'rake/packagetask'
require 'rake/gempackagetask'

task :default => :test

DLEXT = Config::CONFIG['DLEXT']
VERS = '1.1.1'

spec =
  Gem::Specification.new do |s|
    s.name              = "rpeg-markdown"
    s.version           = VERS
    s.summary           = "Fast Markdown implementation"
    s.files             = FileList[
                            'README.markdown','LICENSE','Rakefile',
                            '{lib,ext,test}/**.rb','ext/*.{c,h}',
                            'test/MarkdownTest*/**/*',
                            'bin/rpeg-markdown'
                          ]
    s.bindir            = 'bin'
    s.executables       << 'rpeg-markdown'
    s.require_path      = 'lib'
    s.has_rdoc          = true
    s.extra_rdoc_files  = ['LICENSE']
    s.test_files        = FileList['test/markdown_test.rb']
    s.extensions        = ['ext/extconf.rb']

    s.author            = 'Ryan Tomayko'
    s.email             = 'r@tomayko.com'
    s.homepage          = 'http://github.com/rtomayko/rpeg-markdown'
    s.rubyforge_project = 'wink'
  end

  Rake::GemPackageTask.new(spec) do |p|
    p.gem_spec = spec
    p.need_tar_gz = true
    p.need_tar = false
    p.need_zip = false
  end

namespace :submodule do
  desc 'Init the peg-markdown submodule'
  task :init do |t|
    unless File.exist? 'peg-markdown/markdown.c'
      rm_rf 'peg-markdown'
      sh 'git submodule init peg-markdown'
      sh 'git submodule update peg-markdown'
    end
  end

  desc 'Update the peg-markdown submodule'
  task :update => :init do
    sh 'git submodule update peg-markdown' unless File.symlink?('peg-markdown')
  end

  file 'peg-markdown/markdown.c' do
    Rake::Task['submodule:init'].invoke
  end
  task :exist => 'peg-markdown/markdown.c'
end

desc 'Gather required peg-markdown sources into extension directory'
task :gather => 'submodule:exist' do |t|
  sh 'cd peg-markdown && make markdown_parser.c'
  files =
    FileList[
      'peg-markdown/markdown_{peg.h,parser.c,output.c,lib.c,lib.h}',
      'peg-markdown/{utility,parsing}_functions.c'
    ]
  cp files, 'ext/',
    :preserve => true,
    :verbose => true
end

file 'ext/Makefile' => FileList['ext/{extconf.rb,*.c,*.h,*.rb}'] do
  chdir('ext') { ruby 'extconf.rb' }
end
CLEAN.include 'ext/Makefile'

file "ext/peg_markdown.#{DLEXT}" => FileList['ext/Makefile', 'ext/*.{c,h,rb}'] do |f|
  sh 'cd ext && make'
end
CLEAN.include 'ext/*.{o,bundle,so}'

file "lib/peg_markdown.#{DLEXT}" => "ext/peg_markdown.#{DLEXT}" do |f|
  cp f.prerequisites, "lib/", :preserve => true
end
CLEAN.include "lib/*.{so,bundle}"

desc 'Build the peg_markdown extension'
task :build => "lib/peg_markdown.#{DLEXT}"

desc 'Run unit and conformance tests'
task :test => [ 'test:unit', 'test:conformance' ]

desc 'Run unit tests'
task 'test:unit' => [:build] do |t|
  ruby 'test/markdown_test.rb'
end

desc "Run conformance tests (MARKDOWN_TEST_VER=#{ENV['MARKDOWN_TEST_VER'] ||= '1.0.3'})"
task 'test:conformance' => [:build] do |t|
  script = "#{pwd}/bin/rpeg-markdown"
  test_version = ENV['MARKDOWN_TEST_VER']
  chdir("test/MarkdownTest_#{test_version}") do
    sh "./MarkdownTest.pl --script='#{script}' --tidy"
  end
end

desc 'Run version 1.0 conformance suite'
task 'test:conformance:1.0' => [:build] do
  ENV['MARKDOWN_TEST_VER'] = '1.0'
  Rake::Task['test:conformance'].invoke
end

desc 'Run 1.0.3 conformance suite'
task 'test:conformance:1.0.3' => [:build] do |t|
  ENV['MARKDOWN_TEST_VER'] = '1.0.3'
  Rake::Task['test:conformance'].invoke
end

desc 'Run unit and conformance tests'
task :test => %w[test:unit test:conformance]

desc 'Run benchmarks'
task :benchmark => :build do |t|
  $:.unshift 'lib'
  load 'test/benchmark.rb'
end

desc "See how much memory we're losing"
task 'test:mem' => %w[submodule:exist build] do |t|
  $: << File.join(File.dirname(__FILE__), "lib")
  require 'markdown'
  FileList['test/mem.txt', 'peg-markdown/MarkdownTest_1.0.3/Tests/*.text'].each do |file|
    printf "%s: \n", file
    markdown = Markdown.new(File.read(file))
    iterations = (ENV['N'] || 100).to_i
    total, growth = [], []
    iterations.times do |i|
      start = Time.now
      GC.start
      markdown.to_html
      duration = Time.now - start
      GC.start
      total << `ps -o rss= -p #{Process.pid}`.to_i
      next if i == 0
      growth << (total.last - (total[-2] || 0))
      # puts "%03d: %06.02f ms / %dK used / %dK growth" % [ i, duration, total.last, growth.last ]
    end
    average = growth.inject(0) { |sum,x| sum + x } / growth.length
    printf "  %dK avg growth (per run) / %dK used (after %d runs)\n", average, total.last, iterations
  end
end

# ==========================================================
# Rubyforge
# ==========================================================

PKGNAME = "pkg/rpeg-markdown-#{VERS}"

desc 'Publish new release to rubyforge'
task :release => [ "#{PKGNAME}.gem", "#{PKGNAME}.tar.gz" ] do |t|
  sh <<-end
    rubyforge add_release wink rpeg-markdown #{VERS} #{PKGNAME}.gem &&
    rubyforge add_file    wink rpeg-markdown #{VERS} #{PKGNAME}.tar.gz
  end
end
