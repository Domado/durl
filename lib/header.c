#include "header.h"
#include <stdlib.h>
#include <string.h>

void durl_add_header(DURL *h, const char *line) {
    struct durl_header *new_header = malloc(sizeof(struct durl_header));
    if (!new_header) return;
    new_header->line = strdup(line);
    new_header->next = h->headers;
    h->headers = new_header;
}

void durl_free_headers(DURL *h) {
    struct durl_header *current = h->headers;
    while (current) {
        struct durl_header *next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
    h->headers = NULL;
}
