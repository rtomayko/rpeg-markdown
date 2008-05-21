#include "ruby.h"
#include "markdown_peg.h"
#include "markdown_buffer.h"

static VALUE rb_cMarkdown;

static ID id_text;
static ID id_smart;
static ID id_notes;

#define TABSTOP 4
#define INCREMENT 4096  /* size of chunks in which to allocate memory */

static VALUE
markdown_to_html(VALUE self)
{
  element parsed_input;
  VALUE output_buffer;

  char *inputbuf, *curchar;
  int charstotab, buflength, maxlength;

  /* grab char pointer to markdown input text */
  VALUE text = rb_funcall(self, id_text, 0);
  Check_Type(text, T_STRING);
  char * ptext = StringValuePtr(text);

  buflength = 0;
  maxlength = RSTRING(text)->len >= INCREMENT ?
    RSTRING(text)->len :
    INCREMENT;
  inputbuf = malloc(maxlength);
  curchar = inputbuf;

  charstotab = TABSTOP;
  while ((*curchar = *ptext++) != '\0') {
    switch (*curchar) {
      case '\t':
        while (charstotab > 0)
          *curchar = ' ', curchar++, buflength++, charstotab--; 
        break;
      case '\n':
        curchar++, buflength++, charstotab = TABSTOP;
        break;
      default:
        curchar++, buflength++, charstotab--; 
    }
    if (charstotab == 0)
      charstotab = TABSTOP;
    if (buflength > maxlength - TABSTOP - 3) {
      maxlength += INCREMENT;
      inputbuf = realloc(inputbuf, maxlength);
      curchar = inputbuf + buflength;
      if (inputbuf == NULL) {
        /* TODO: no memory */
      }
    }
  }
  *curchar++ = '\n';
  *curchar++ = '\n';
  *curchar   = '\0';
  buflength+= 2;

  /* flip extension bits */
  int extensions = 0;
  if ( rb_funcall(self, id_smart, 0) == Qtrue )
    extensions = extensions | EXT_SMART ;
  if ( rb_funcall(self, id_notes, 0) == Qtrue )
    extensions = extensions | EXT_NOTES ;

  /* parse markdown input into sematic element tree */
  parsed_input = markdown(inputbuf, extensions);

  /* allocate output buffer and generate output */
  output_buffer = rb_markdown_buffer_init(buflength * 2);
  print_element(parsed_input, HTML_FORMAT);
  rb_markdown_buffer_free();
  return output_buffer;
}

void Init_markdown()
{
  /* Initialize frequently used Symbols */
  id_text = rb_intern("text");
  id_smart = rb_intern("smart");
  id_notes = rb_intern("notes");

  rb_cMarkdown = rb_define_class("Markdown", rb_cObject);
  rb_define_method(rb_cMarkdown, "to_html", markdown_to_html, 0);
}
