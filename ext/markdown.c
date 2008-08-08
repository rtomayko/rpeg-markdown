#include "ruby.h"
#include "markdown_lib.h"

static VALUE rb_cMarkdown;

static VALUE
rb_markdown_to_html(int argc, VALUE *argv, VALUE self)
{
    /* grab char pointer to markdown input text */
    VALUE text = rb_funcall(self, rb_intern("text"), 0);
    Check_Type(text, T_STRING);
    char * ptext = StringValuePtr(text);

    /* flip extension bits */
    int extensions = 0;
    if ( rb_funcall(self, rb_intern("smart"), 0) == Qtrue )
        extensions = extensions | EXT_SMART ;
    if ( rb_funcall(self, rb_intern("notes"), 0) == Qtrue )
        extensions = extensions | EXT_NOTES ;
    if ( rb_funcall(self, rb_intern("filter_html"), 0) == Qtrue )
        extensions = extensions | EXT_FILTER_HTML ;
    if ( rb_funcall(self, rb_intern("filter_styles"), 0) == Qtrue )
        extensions = extensions | EXT_FILTER_STYLES ;

    char *html = markdown_to_string(ptext, extensions, HTML_FORMAT);
    VALUE result = rb_str_new2(html);
    free(html);

    return result;
}

static VALUE
rb_markdown_to_latex(int argc, VALUE *argv, VALUE self)
{
    /* grab char pointer to markdown input text */
    VALUE text = rb_funcall(self, rb_intern("text"), 0);
    Check_Type(text, T_STRING);
    char * ptext = StringValuePtr(text);

    /* flip extension bits - note that defaults are different than
     * for HTML */
    int extensions = EXT_SMART | EXT_NOTES | EXT_FILTER_HTML | EXT_FILTER_STYLES;
    if ( rb_funcall(self, rb_intern("smart"), 0) == Qfalse )
        extensions = extensions & ~ EXT_SMART ;
    if ( rb_funcall(self, rb_intern("notes"), 0) == Qfalse )
        extensions = extensions & ~ EXT_NOTES ;

    char *latex = markdown_to_string(ptext, extensions, LATEX_FORMAT);
    VALUE result = rb_str_new2(latex);
    free(latex);

    return result;
}

static VALUE
rb_markdown_to_groff_mm(int argc, VALUE *argv, VALUE self)
{
    /* grab char pointer to markdown input text */
    VALUE text = rb_funcall(self, rb_intern("text"), 0);
    Check_Type(text, T_STRING);
    char * ptext = StringValuePtr(text);

    /* flip extension bits - note that defaults are different than
     * for HTML */
    int extensions = EXT_SMART | EXT_NOTES | EXT_FILTER_HTML | EXT_FILTER_STYLES;
    if ( rb_funcall(self, rb_intern("smart"), 0) == Qfalse )
        extensions = extensions & ~ EXT_SMART ;
    if ( rb_funcall(self, rb_intern("notes"), 0) == Qfalse )
        extensions = extensions & ~ EXT_NOTES ;

    char *groff = markdown_to_string(ptext, extensions, GROFF_MM_FORMAT);
    VALUE result = rb_str_new2(groff);
    free(groff);

    return result;
}

void Init_peg_markdown()
{
    rb_cMarkdown = rb_define_class("PEGMarkdown", rb_cObject);
    rb_define_method(rb_cMarkdown, "to_html", rb_markdown_to_html, -1);
    rb_define_method(rb_cMarkdown, "to_latex", rb_markdown_to_latex, -1);
    rb_define_method(rb_cMarkdown, "to_groff_mm", rb_markdown_to_groff_mm, -1);
}

// vim: ts=4 sw=4
