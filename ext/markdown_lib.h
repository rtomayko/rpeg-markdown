#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

enum markdown_extensions {
    EXT_SMART            = 0x1,
    EXT_NOTES            = 0x2,
    EXT_FILTER_HTML      = 0x4,
    EXT_FILTER_STYLES    = 0x8
};

enum markdown_formats {
    HTML_FORMAT,
    LATEX_FORMAT,
    GROFF_MM_FORMAT
};

GString * markdown_to_g_string(char *text, int extensions, int output_format);
char * markdown_to_string(char *text, int extensions, int output_format);

/* vim: set ts=4 sw=4 : */
