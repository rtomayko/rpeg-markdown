#include "ruby.h"
#include "markdown_lib.h"

static VALUE rb_cMarkdown;

static ID id_text;
static ID id_smart;
static ID id_notes;

#define TABSTOP 4
#define INCREMENT 4096  /* size of chunks in which to allocate memory */

static VALUE
rb_markdown_to_html(VALUE self)
{
    /* grab char pointer to markdown input text */
    VALUE text = rb_funcall(self, id_text, 0);
    Check_Type(text, T_STRING);
    char * ptext = StringValuePtr(text);

    /* flip extension bits */
    int extensions = 0;
    if ( rb_funcall(self, id_smart, 0) == Qtrue )
        extensions = extensions | EXT_SMART ;
    if ( rb_funcall(self, id_notes, 0) == Qtrue )
        extensions = extensions | EXT_NOTES ;

    char *html = markdown_to_string(ptext, extensions, HTML_FORMAT);
    VALUE result = rb_str_new2(html);
    free(html);

    return result;
}

void Init_markdown()
{
    /* Initialize frequently used Symbols */
    id_text = rb_intern("text");
    id_smart = rb_intern("smart");
    id_notes = rb_intern("notes");

    rb_cMarkdown = rb_define_class("Markdown", rb_cObject);
    rb_define_method(rb_cMarkdown, "to_html", rb_markdown_to_html, 0);
}

// vim: ts=4 sw=4
