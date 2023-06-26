#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

int is_request_smuggling(const char* request) {
    char* request_copy = strdup(request);
    char* token = strtok(request_copy, "\n");

    while (token != NULL) {
        // Check for suspicious patterns in headers
        if (strstr(token, "Transfer-Encoding:") != NULL &&
            strstr(token, "Content-Length:") != NULL) {
            free(request_copy);
            return 1;
        }

        token = strtok(NULL, "\n");
    }

    free(request_copy);
    return 0;
}

int main() {
    char request[MAX_REQUEST_SIZE];
    
    printf("Enter the HTTP request:\n");
    fgets(request, sizeof(request), stdin);

    int is_smuggling = is_request_smuggling(request);
    if (is_smuggling) {
        printf("Request smuggling detected!\n");
    } else {
        printf("No request smuggling detected.\n");
    }

    return 0;
}
