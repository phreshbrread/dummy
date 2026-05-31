#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

<<<<<<< HEAD
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
=======
#define MAX_DEST_LENGTH 1024
>>>>>>> f9d19b8 (Fixes)

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

void invalid_usage() {
    printf("%llu, %c, %s\n", size, unit, destination);
    printf("Usage: dummy [size] [unit] [destination]\nExample: dummy 24 M ~/Desktop\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    // Check for 4 here because the first arg is always the executable's path
    if (argc != 4) {
        invalid_usage();
    }

<<<<<<< HEAD
    /* 
     * strtol() -> string to long, the 10
     * specifies decimal (use 16 for hexadecimal)
    */

    unsigned long long size;
    const int max_dest_length = 1042;

    if (strtol(argv[1], NULL, 10) <= 0) { // Only assign size if arg is valid
=======
    // Only assign size if arg is valid
    if (strtol(argv[1], NULL, 10) <= 0) {
>>>>>>> f9d19b8 (Fixes)
        invalid_usage();
    }

<<<<<<< HEAD
    char unit = *argv[2]; // Set unit to second argument
    char destination[max_dest_length];

    if (strlen(argv[3]) > max_dest_length) { // Check validity of destination
        invalid_usage();
    }

    strcpy(destination, argv[3]); // Copy value of argv[3] to destination
=======
    // Set size to first argument
    size = strtol(argv[1], NULL, 10);

    // De-reference second given arg for unit
    unit = tolower(*argv[2]);

    char destination[MAX_DEST_LENGTH];
    if (strlen(argv[3]) > MAX_DEST_LENGTH) { // Check validity of destination
        invalid_usage();
    }

    strcpy(destination, argv[3]);
>>>>>>> f9d19b8 (Fixes)

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

<<<<<<< HEAD
    printf("\nSize: %llu %c\nDestination: %s\n", size, unit, destination);
    printf("Actual Size: %llu byte(s)\n", size);

    /* TODO
     * - Make faster
     * - Fix accuracy issues
     * - Handle errors
     * - Set default destination
     * - Handle buffer overflow crash if path is too long
    */    

    // This is a really shit way of doing this and only gets slower the larger the file
    FILE *fptr;                         // Create file pointer 
    fptr = fopen(destination, "wb");    // Open file at destination
    
    for (int i = 0; i <= size; ++i) {   // Fill with zeroes until size is reached
        fprintf(fptr, "%d", 0);
    }

    fclose(fptr);                       // Close destination file
=======
    // TODO: Actually write file
>>>>>>> f9d19b8 (Fixes)

    printf("Actual Size: %llu byte(s)\n", size);

    printf("Wrote [SIZE] file at [DESTINATION]\n");

    return EXIT_SUCCESS;
}
