#include "durl.h"
#include "context.h"
#include "url.h"
#include "connect.h"
#include "http.h"
#include "header.h"
#include <stdlib.h>
#include <string.h>

DURL *durl_init() {
    DURL *h = calloc(1, sizeof(DURL));
    if (!h) return NULL;
    h->sockfd = -1;
    h->request_type = strdup("GET");
    return h;
}

int durl_perform(DURL *handle) {
    if (!handle || !handle->url) return -1;

    durl_parse_url(handle);
    if (!handle->host) return -1;

    if (durl_connect(handle) != 0) {
        durl_disconnect(handle);
        return -1;
    }

    durl_http_perform(handle);
    durl_disconnect(handle);
    
    return 0;
}

void durl_cleanup(DURL *h) {
    if (!h) return;
    
    durl_disconnect(h);
    durl_free_headers(h);

    free(h->url);
    free(h->scheme);
    free(h->host);
    free(h->port);
    free(h->path);
    free(h->post_fields);
    free(h->request_type);
    free(h);
}