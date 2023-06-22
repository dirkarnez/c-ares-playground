#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ares.h>

void callback(void *arg, int status, int timeouts, struct hostent *hostent) {
    if (status != ARES_SUCCESS) {
        printf("Failed to lookup %s: %s\n", (char *)arg, ares_strerror(status));
        return;
    }

    struct in_addr addr;
    memcpy(&addr, hostent->h_addr_list[0], sizeof(struct in_addr));
    printf("%s has address %s\n", (char *)arg, inet_ntoa(addr));
}

int main() {
    ares_channel channel;
    int status;
    const char *domain = "google.com";

    status = ares_library_init(ARES_LIB_INIT_ALL);
    if (status != ARES_SUCCESS) {
        printf("Failed to initialize c-ares library: %s\n", ares_strerror(status));
        return 1;
    }

    status = ares_init(&channel);
    if (status != ARES_SUCCESS) {
        printf("Failed to initialize c-ares channel: %s\n", ares_strerror(status));
        return 1;
    }

    ares_gethostbyname(channel, domain, AF_INET, callback, (void *)domain);

    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
}
