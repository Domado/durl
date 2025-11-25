#ifndef CONTEXT_H
#define CONTEXT_H

#include <openssl/ssl.h>

struct durl_header {
    char *line;
    struct durl_header *next;
};

typedef struct DURL_HANDLE DURL;

struct DURL_HANDLE {
    char *url;
    char *scheme;
    char *host;
    char *port;
    char *path;
    char *post_fields;
    char *request_type;

    int use_ssl;
    int sockfd;
    int verbose;

    struct durl_header *headers;

    SSL_CTX *ssl_ctx;
    SSL *ssl;
};

#endif
