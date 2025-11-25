#include "durl.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [options] <URL>\n", argv[0]);
        return 1;
    }

    DURL *handle = durl_init();
    if (!handle) {
        return 1;
    }

    int verbose = 0;
    char *request_type = NULL;
    char *post_data = NULL;

    static struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"header", required_argument, 0, 'H'},
        {"request", required_argument, 0, 'X'},
        {"data", required_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "vH:X:d:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                durl_setopt(handle, DURLOPT_VERBOSE, &verbose);
                break;
            case 'H':
                durl_setopt(handle, DURLOPT_CUSTOMHEADERS, optarg);
                break;
            case 'X':
                request_type = optarg;
                durl_setopt(handle, DURLOPT_REQUEST_TYPE, request_type);
                break;
            case 'd':
                post_data = optarg;
                durl_setopt(handle, DURLOPT_POSTFIELDS, post_data);
                break;
            default:
                fprintf(stderr, "Usage: %s [options] <URL>\n", argv[0]);
                durl_cleanup(handle);
                return 1;
        }
    }

    if (optind < argc) {
        durl_setopt(handle, DURLOPT_URL, argv[optind]);
    } else {
        fprintf(stderr, "URL is required.\n");
        durl_cleanup(handle);
        return 1;
    }

    durl_perform(handle);
    durl_cleanup(handle);

    return 0;
}