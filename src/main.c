#include <stdio.h>
#include <stdlib.h> // For strtol() and exit()
#include <string.h> // For strcpy() and strlen()

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

int main(int argc, char *argv[]) {
    // Check for 4 here because the first arg is always the executable's path
    if (argc != 4) {
        invalid_usage();
    }

    /* 
     * strtol() -> string to long, the 10
     * specifies decimal (use 16 for hexadecimal)
    */

    unsigned long long size;
    const int max_dest_length = 1042;

    if (strtol(argv[1], NULL, 10) <= 0) { // Only assign size if arg is valid
        invalid_usage();
    }
    
    size = strtol(argv[1], NULL, 10); // Set size to first argument

    char unit = *argv[2]; // Set unit to second argument
    char destination[max_dest_length];

    if (strlen(argv[3]) > max_dest_length) { // Check validity of destination
        invalid_usage();
    }

    strcpy(destination, argv[3]); // Copy value of argv[3] to destination

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

    return 0;
}
