#include "ruby.h"

VALUE rb_markdown_buffer_init(long size);
void rb_markdown_buffer_free(void);
int rb_markdown_buffer_printf(const char * format, ...);
char rb_markdown_buffer_putchar(char c);
