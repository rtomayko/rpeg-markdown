Ruby PEG Markdown
=================

An extension library around [John MacFarlane's fast implementation][1]
of Markdown in C.

[1]: http://github.com/jgm/peg-markdown/

Synopsis
--------

    >> require 'markdown'
    >> puts Markdown.new('Hello, world.').to_html
    <p>Hello, world.</p>

    >> puts Markdown.new('_Hello World!_', :smart, :filter_html).to_html
    <p><em>Hello World!</em></p>

    >> puts Markdown.new('_Hello World!_').to_latex
    \emph{Hello World!}

    >> puts Markdown.new('_Hello World!_').to_groff_mm
    .P
    \fIHello world!\fR

    >> PEGMarkdown.new('Hello! World!')

Installation / Hacking
----------------------

This library requires a recent version of glib2. All modern GNU userland
systems should be fine.

Install from GEM:

    $ sudo gem install rpeg-markdown

Hacking:

    $ git clone git://github.com/rtomayko/rpeg-markdown.git
    $ cd rpeg-markdown
    $ rake test

Patches happily accepted via fork or email.

Changes
-------

  * [Version 1.0](http://github.com/rtomayko/rpeg-markdown/tree/v1.0)

COPYING
-------

The peg-markdown sources are licensed under the GPL and the Ruby PEG Markdown
extension sources adopts this license. See the file LICENSE included with this
distribution for more information.
