#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEST_LENGTH 256

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

unsigned long long size = 0;
char unit;
char destination[MAX_DEST_LENGTH];

int invalid_usage() {
    printf("Usage: dummy [size] [unit] [destination]\nExample: dummy 24 M ~/Desktop\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    // Check for 4 here because the first arg is always the executable's path
    if (argc != 4) {
        invalid_usage();
    }

    if (strtol(argv[1], NULL, 10) <= 0) { // Only assign size if arg is valid
        invalid_usage();
    }

    size = strtol(argv[1], NULL, 10); // Set size to first argument

    unit = (unsigned char)tolower(*argv[2]); // Set unit to second argument

    if (strlen(argv[3]) > MAX_DEST_LENGTH) { // Check validity of destination
        invalid_usage();
    }

    strcpy(destination, argv[3]); // Copy value of argv[3] to destination

    // Switch case to determine size
    switch (unit) {
        case 'b':
            break;
        case 'k':
            size *= 1024;
            break;
        case 'm':
            size *= 1048576;
            break;
        case 'g':
            size *= 1073741824;
            break;
        case 't':
            size *= 1099511627776;
            break;
        default:
            invalid_usage();
    }

    printf("\nSize: %llu %c\nDestination: %s\n", size, unit, destination);
    printf("Actual Size: %llu byte(s)\n", size);

    /* TODO:
     * - Make faster
     * - Fix accuracy issues
     * - Handle errors
     * - Set default destination
     * - Handle buffer overflow crash if path is too long
     */

    FILE *fptr;
    if ((fptr = fopen(destination, "wb")) == NULL) {
        fprintf(stderr, "Failed to write file\n");
        exit(EXIT_FAILURE);
    }

    printf("Writing file...\n");

    // Fill with zeroes until size is reached
    // This is a really shit way of doing this and only gets slower the larger the file
    for (unsigned long long i = 0; i <= size; ++i) {
        fputc(0, fptr);
    }

    // Close destination file
    fclose(fptr);

    return 0;
}
