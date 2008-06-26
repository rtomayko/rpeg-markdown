require 'markdown.so'

class Markdown

  # Original Markdown formatted text.
  attr_reader :text

  # Set true to have smarty-like quote translation performed.
  attr_accessor :smart

  # Set true to have footnotes processed.
  attr_accessor :notes

  # BlueCloth compatible output filtering.
  attr_accessor :filter_styles, :filter_html

  # RedCloth compatible line folding -- not used for Markdown but
  # included for compatibility.
  attr_accessor :fold_lines

  # Create a new Markdown processor. The +text+ argument
  # should be a string containing Markdown text. Additional arguments may be
  # supplied to set various processing options:
  #
  # * <tt>:smart</tt> - Enable SmartyPants processing.
  # * <tt>:notes</tt> - Enable footnotes.
  # * <tt>:filter_styles</tt> - Do not output <tt><style></tt> tags.
  # * <tt>:filter_html</tt> - Do not output any raw HTML tags included in
  #   the source text.
  # * <tt>:fold_lines</tt> - RedCloth compatible line folding (not used).
  #
  # NOTE: The <tt>:filter_styles</tt> and <tt>:filter_html</tt> extensions
  # are not yet implemented.
  def initialize(text, *extensions)
    @smart = false
    @notes = false
    @text = text
    extensions.each { |e| send("#{e}=", true) }
  end

end
