#ifndef HEADER_H
#define HEADER_H
#include "context.h"
void durl_add_header(DURL *h, const char *line);
void durl_free_headers(DURL *h);
#endif
