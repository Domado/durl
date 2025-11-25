#ifndef DURL_H
#define DURL_H

typedef struct DURL_HANDLE DURL;

typedef enum {
    DURLOPT_URL,
    DURLOPT_VERBOSE,
    DURLOPT_CUSTOMHEADERS,
    DURLOPT_POSTFIELDS,
    DURLOPT_REQUEST_TYPE
} DURLoption;

DURL *durl_init();
int durl_setopt(DURL *handle, DURLoption option, void *param);
int durl_perform(DURL *handle);
void durl_cleanup(DURL *handle);

#endif