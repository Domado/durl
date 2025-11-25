#include "connect.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/err.h>

static int _durl_tcp_connect(DURL *h) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(h->host, h->port, &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    h->sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (h->sockfd < 0) {
        perror("socket");
        freeaddrinfo(res);
        return -1;
    }

    if (connect(h->sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("connect");
        close(h->sockfd);
        h->sockfd = -1;
        freeaddrinfo(res);
        return -1;
    }
    
    freeaddrinfo(res);
    return 0;
}

static int _durl_ssl_connect(DURL *h) {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    const SSL_METHOD *method = TLS_client_method();
    h->ssl_ctx = SSL_CTX_new(method);
    if (!h->ssl_ctx) {
        ERR_print_errors_fp(stderr);
        return -1;
    }

    h->ssl = SSL_new(h->ssl_ctx);
    if (!h->ssl) {
        ERR_print_errors_fp(stderr);
        return -1;
    }

    SSL_set_fd(h->ssl, h->sockfd);
    if (SSL_connect(h->ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return -1;
    }
    return 0;
}

int durl_connect(DURL *h) {
    if (_durl_tcp_connect(h) != 0) return -1;

    if (h->use_ssl) {
        if (_durl_ssl_connect(h) != 0) return -1;
    }
    return 0;
}

void durl_disconnect(DURL *h) {
    if (!h) return;
    
    if (h->ssl) {
        SSL_shutdown(h->ssl);
        SSL_free(h->ssl);
        h->ssl = NULL;
    }
    if (h->ssl_ctx) {
        SSL_CTX_free(h->ssl_ctx);
        h->ssl_ctx = NULL;
    }
    if (h->sockfd > 0) {
        close(h->sockfd);
        h->sockfd = -1;
    }
}
