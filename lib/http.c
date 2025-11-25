#include "http.h"
#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#define DURL_BUFFER_SIZE 8192

static char* _build_request(DURL *h) {
    char *request = NULL;
    size_t req_len = 0;
    char buffer[DURL_BUFFER_SIZE];

    const char *method = "GET";
    if (h->request_type) {
        method = h->request_type;
    } else if (h->post_fields) {
        method = "POST";
    }

    snprintf(buffer, sizeof(buffer), "%s %s HTTP/1.1\r\n", method, h->path);
    req_len = strlen(buffer);
    request = malloc(req_len + 1);
    strcpy(request, buffer);

    snprintf(buffer, sizeof(buffer), "Host: %s\r\n", h->host);
    request = realloc(request, req_len + strlen(buffer) + 1);
    strcat(request, buffer);
    req_len += strlen(buffer);

    durl_add_header(h, "User-Agent: durl/2.0");
    durl_add_header(h, "Accept: */*");
    
    if (strcmp(method, "POST") == 0 && h->post_fields) {
        snprintf(buffer, sizeof(buffer), "Content-Length: %zu\r\n", strlen(h->post_fields));
        durl_add_header(h, buffer);
        durl_add_header(h, "Content-Type: application/x-www-form-urlencoded");
    }

    struct durl_header *current = h->headers;
    while (current) {
        snprintf(buffer, sizeof(buffer), "%s\r\n", current->line);
        request = realloc(request, req_len + strlen(buffer) + 1);
        strcat(request, buffer);
        req_len += strlen(buffer);
        current = current->next;
    }

    request = realloc(request, req_len + 3);
    strcat(request, "\r\n");
    req_len += 2;

    if (strcmp(method, "POST") == 0 && h->post_fields) {
        request = realloc(request, req_len + strlen(h->post_fields) + 1);
        strcat(request, h->post_fields);
        req_len += strlen(h->post_fields);
    }
    
    if (h->verbose) {
        printf("> %s", request);
    }

    return request;
}

int durl_http_perform(DURL *h) {
    char *request = _build_request(h);
    if (!request) return -1;

    ssize_t bytes_sent;
    if (h->use_ssl) {
        bytes_sent = SSL_write(h->ssl, request, strlen(request));
    } else {
        bytes_sent = send(h->sockfd, request, strlen(request), 0);
    }
    free(request);

    if (bytes_sent < 0) {
        perror("send/SSL_write");
        return -1;
    }

    char buffer[DURL_BUFFER_SIZE];
    ssize_t bytes_received;
    int headers_done = 0;
    while (1) {
        if (h->use_ssl) {
            bytes_received = SSL_read(h->ssl, buffer, sizeof(buffer) - 1);
        } else {
            bytes_received = recv(h->sockfd, buffer, sizeof(buffer) - 1, 0);
        }

        if (bytes_received <= 0) {
            break;
        }
        
        buffer[bytes_received] = '\0';

        if (h->verbose && !headers_done) {
            char *header_end = strstr(buffer, "\r\n\r\n");
            if (header_end) {
                *header_end = '\0';
                printf("< %s\r\n\r\n", buffer);
                *header_end = '\r';
                printf("%s", header_end + 4);
                headers_done = 1;
            } else {
                printf("< %s", buffer);
            }
        } else {
            printf("%s", buffer);
        }
    }
    
    return 0;
}
