#include <stdio.h>
#include <stdlib.h> // For strtol() and exit()
#include <string.h> // For strcpy() and strlen()

#define MAX_DEST_LENGTH 1024
    /*
     * Usage: dummy [size] [unit] [destination]
     * Example: dummy 24 m ~/test
     *
     * Rules:
     *  - Size must be greater than 0
     *  - Unit must be in b, k, m, g, or t
     *    (lower or upper works)
     *  - If no destination is specified, a
     *    default file called 'dummy-file' will be
     *    created in the current directory
    */

int invalid_usage() {
    printf("Usage: dummy [size] [unit] [destination]\nExample: dummy 24 M ~/Desktop\n");
    exit(1);
}

#ifdef DEBUG
void debug_print_args(int argc, char *argv[]) {
    printf("Arguments explicitly given: %i\n", argc - 1);

    printf("\nargv[0] = %s\n\n", argv[0]);    
    
    for (int i = 1; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf("----------------------------------------\n\n");
}
#endif

int main(int argc, char *argv[]) {
    /*
     * 1. Get user args [DONE]
     * 2. Ensure only 3 args are passed, remember
     * that argv[0] is the execuatable's path [DONE]
     * 3. Check to ensure size, unit and destination are valid [DONE]
     * 4. Convert size if necessary
     *
     * Make sure to handle buffer overflow crash if path is too long
    */

#ifdef DEBUG
    debug_print_args(argc, argv);
#endif

    // Check for 4 here because the first arg is always the executable's path
    if (argc != 4) {
        invalid_usage();
    }

    /* 
     * strtol() -> string to long, the 10
     * specifies decimal (use 16 for hexadecimal)
    */

    unsigned long long size;

    if (strtol(argv[1], NULL, 10) <= 0) { // Only assign size if arg is valid
        invalid_usage();
    }
    
    size = strtol(argv[1], NULL, 10); // Set size to first argument

    char unit = *argv[2]; // Set unit to second argument
    char destination[MAX_DEST_LENGTH];

    if (strlen(argv[3]) > MAX_DEST_LENGTH) { // Check validity of destination
        invalid_usage();
    }

    strcpy(destination, argv[3]);

#ifdef DEBUG
    printf("\nSize: %llu %c\nDestination: %s\n", size, unit, destination);
#endif

    // Switch case to determine size
    switch (unit) {
        case 'b':
        case 'B':
            break;
        case 'k':
        case 'K':
            size *= 1024;
            break;
        case 'm':
        case 'M':
            size *= 1048576;
            break;
        case 'g':
        case 'G':
            size *= 1073741824;
            break;
        case 't':
        case 'T':
            size *= 1099511627776;
            break;
        default:
            invalid_usage();
    }

    printf("Actual Size: %llu byte(s)", size);

    return 0;
}
