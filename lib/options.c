#include "options.h"
#include "context.h"
#include "header.h"
#include <string.h>
#include <stdlib.h>

int durl_setopt(DURL *handle, DURLoption option, void *param) {
    if (!handle) return -1;
    switch (option) {
        case DURLOPT_URL:
            if (handle->url) free(handle->url);
            handle->url = strdup((char *)param);
            break;
        case DURLOPT_VERBOSE:
            handle->verbose = *(int *)param;
            break;
        case DURLOPT_CUSTOMHEADERS:
            durl_add_header(handle, (char *)param);
            break;
        case DURLOPT_POSTFIELDS:
            if (handle->post_fields) free(handle->post_fields);
            handle->post_fields = strdup((char *)param);
            break;
        case DURLOPT_REQUEST_TYPE:
            if (handle->request_type) free(handle->request_type);
            handle->request_type = strdup((char *)param);
            break;
        default:
            return -1;
    }
    return 0;
}
