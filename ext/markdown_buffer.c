#include <stdio.h>
#include <stdarg.h>
#include "ruby.h"
#include "markdown_buffer.h"

static VALUE markdown_buffer;
static int registered = 0;

VALUE rb_markdown_buffer_init(long size) {
  if ( registered != 1 ) {
    rb_gc_register_address(&markdown_buffer);
    registered = 1;
  }
  markdown_buffer = rb_str_buf_new(size);
  return markdown_buffer;
}

void rb_markdown_buffer_free(void) {
  markdown_buffer = Qnil;
}

int rb_markdown_buffer_printf(const char * format, ...)
{
  va_list args;
  int length;
  char * buf = NULL;

  va_start(args, format);
  length = vasprintf(&buf, format, args);
  va_end(args);

  if ( buf != NULL )  {
    rb_str_buf_cat(markdown_buffer, buf, length);
    free(buf);
  } else {
    /* TODO: handle out of memory condition */
  }

  return length;
}

char rb_markdown_buffer_putchar(char c)
{
  rb_str_buf_cat(markdown_buffer, &c, 1);
  return c;
}
