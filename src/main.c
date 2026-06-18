#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEST_LENGTH 4096

/*
 * Usage: dummy [size] [unit] [destination]
 * Example: dummy 2 g ./test
 *
 * Rules:
 *  - Size must be positive
 *  - Unit must be in b, k, m, g, or t
 *    (lower or upper works)
 */

char     unit;
char     destination[MAX_DEST_LENGTH];
uint64_t size = 0;

int invalid_usage();
void write_dummy_file(uint64_t size, char *destination);

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

    printf("\nSize: %lu bytes\nDestination: %s\n", size, destination);
    printf("Writing file...\n");

    write_dummy_file(size, destination);

    printf("\n");

    return EXIT_SUCCESS;
}

int invalid_usage() {
    printf("Usage: dummy [size] [unit] [destination]\nExample: dummy 24 M ~/Desktop\n");
    exit(EXIT_FAILURE);
}

void write_dummy_file(uint64_t size, char *destination) {
    FILE *fptr;
    if ((fptr = fopen(destination, "wb")) == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // TODO: Adjust chunk size
    const int chunk_size = 65536;
    uint64_t *buf = malloc(chunk_size);

    size_t written = 0;

    while (written < size) {
        written += fwrite(buf, 1, chunk_size, fptr);
    }

    if (written != size) {
        perror("Failed to write file");
        exit(EXIT_FAILURE);
    }

    printf("\nBytes written: %lu", written);

    // Close destination file
    fclose(fptr);
}

/* TODO:
 * - Handle errors
 * - Set default destination
 * - Handle buffer overflow crash if path is too long
 */
