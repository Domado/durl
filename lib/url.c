#include "url.h"
#include <stdlib.h>
#include <string.h>

void durl_parse_url(DURL *h) {
    if (!h || !h->url) return;

    free(h->scheme);
    free(h->host);
    free(h->port);
    free(h->path);
    h->scheme = NULL;
    h->host = NULL;
    h->port = NULL;
    h->path = NULL;

    char *url_copy = strdup(h->url);
    if (!url_copy) return;

    char *scheme_ptr = strstr(url_copy, "://");
    if (!scheme_ptr) {
        free(url_copy);
        return;
    }
    *scheme_ptr = '\0';
    h->scheme = strdup(url_copy);

    char *host_ptr = scheme_ptr + 3;
    char *path_ptr = strchr(host_ptr, '/');
    char *port_ptr = strchr(host_ptr, ':');

    if (path_ptr) {
        h->path = strdup(path_ptr);
        *path_ptr = '\0';
    } else {
        h->path = strdup("/");
    }

    if (port_ptr && (!path_ptr || port_ptr < path_ptr)) {
        *port_ptr = '\0';
        h->port = strdup(port_ptr + 1);
    }

    h->host = strdup(host_ptr);

    if (!h->port) {
        if (strcmp(h->scheme, "https") == 0) {
            h->port = strdup("443");
        } else {
            h->port = strdup("80");
        }
    }
    
    if (strcmp(h->scheme, "https") == 0) {
        h->use_ssl = 1;
    } else {
        h->use_ssl = 0;
    }

    free(url_copy);
}
