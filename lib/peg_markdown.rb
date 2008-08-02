require 'peg_markdown.so'

# Front-end to jgm's peg-markdown implementation of Markdown, the humane
# text markup language.
#
# A simple processor:
#   >>> puts Markdown.new("Hello, World.").to_html
#   <p>Hello, World.</p>
#
# With other stuff:
#   >>> puts Markdown.new("_Hello -- World!_", :smart, :filter_html).to_html
#   <p><em>Hello World!</em></p>
#
class PEGMarkdown

  # Original Markdown formatted text.
  attr_reader :text

  # Set true to have smarty-like quote translation performed.
  attr_accessor :smart

  # Set true to have footnotes processed.
  attr_accessor :notes

  # Do not output <style> tags included in the source text.
  attr_accessor :filter_styles

  # Do not output any raw HTML included in the source text.
  attr_accessor :filter_html

  # Included for compatibility with RedCloth's interface.
  attr_accessor :fold_lines

  # Create a new Markdown processor. The +text+ argument is a string
  # containing Markdown text. Variable other arguments may be supplied to
  # set various processing options:
  #
  # * <tt>:smart</tt> - Enable SmartyPants processing.
  # * <tt>:notes</tt> - Enable footnotes.
  # * <tt>:filter_styles</tt> - Do not output <style> tags included in the
  #   source text.
  # * <tt>:filter_html</tt> - Do not output raw HTML included in the
  #   source text.
  # * <tt>:fold_lines</tt> - RedCloth compatible line folding (not used).
  #
  def initialize(text, *extensions)
    @text = text
    @smart = false
    @notes = false
    @filter_styles = false
    @filter_html = false
    extensions.each { |e| send("#{e}=", true) }
  end

  alias to_s text

end

Markdown = PEGMarkdown unless defined? Markdown
