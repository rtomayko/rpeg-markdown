$: << File.join(File.dirname(__FILE__), "lib")

require 'test/unit'
require 'markdown'

class MarkdownTest < Test::Unit::TestCase

  def test_that_extension_methods_are_present_on_markdown_class
    assert Markdown.instance_methods.include?('to_html'),
      "Markdown class should respond to #to_html"
  end

  def test_converting_simple_string_to_html
    markdown = Markdown.new('Hello World.')
    assert_respond_to markdown, :to_html
    assert_equal "\n\n<p>Hello World.</p>", markdown.to_html
  end

  def test_converting_markup_string_to_html
    markdown = Markdown.new('_Hello World_!')
    assert_respond_to markdown, :to_html
    assert_equal '<p><em>Hello World</em>!</p>', markdown.to_html
  end

end
