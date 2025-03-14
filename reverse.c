////////////////////////////////////////////////////////////////////
// FILE WRITTEN BY JUUSO KÄYHKÖ (493675)                          //
//                                                                //
// AI TOOLS WERE USED FOR ALGORHITM STRUCTURE GENERATION,         //
// BUT NOT FOR WRITING THE ACTUALY CODE.                          //
// FILE: reverse.c                                                //
////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// READ FILE OF ANY LENGTH
char *readLine(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, file);
    if (read == -1) {
        free(line);
        return NULL;
    }

    return line;
}

int main(int argc, char *argv[]) {
    // CHECK IF AT LEAST ONE ARGUMENT WAS GIVEN
    if (argc < 2) {
        fprintf(stderr, "Provide arguments for input file and optionally output file\n");
        exit(1);
    }

    // CHECK IF TOO MANY ARGUMENTS WAS GIVEN
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // CHECK IF INPUT AND OUTPUT (NAME) IS THE SAME
    if (argc >= 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    }

    FILE *input = fopen(argv[1], "r");

    // OPEN INPUT FILE
    if (!input) {
        fprintf(stderr, "error: cannot open file '%s'.\n", argv[1]);
        exit(1);
    }

    // INITIAL CAPACITY, GROW AS NEEDED IF FILE IS VERY LARGE
    size_t capacity = 10;
    size_t count = 0;
    char **lines = malloc(capacity * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        fclose(input);
        exit(1);
    }

    // READ FROM INPUT FILE
    char *line;
    while ((line = readLine(input)) != NULL) {
        if (count >= capacity) {
            // INCREASE CAPACITY AS NEEDED
            capacity *= 2;
            char **temp = realloc(lines, capacity * sizeof(char *));
            if (!temp) {
                fprintf(stderr, "malloc failed\n");
                
                // CLOSE FILE AND FREE MEMORY
                free(line);
                for (size_t i = 0; i < count; i++) {
                    free(lines[i]);
                }
                free(lines);
                fclose(input);
                exit(1);
            }
            lines = temp;
        }
        lines[count++] = line;
    }

    // CLOSE FILE
    fclose(input);

    // OPEN OUTPUT (IF ONE WAS GIVEN)
    FILE *output = NULL;
    if (argc >= 3) {
        output = fopen(argv[2], "w");
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'.\n", argv[2]);
            exit(1);
        }
    }

    // WRITE OR PRINT LINES IN REVERSE
    for (int i = count - 1; i >= 0; i--) {
        size_t len = strlen(lines[i]);
        if (len > 0 && lines[i][len - 1] != '\n') {
            // ADD NEW LINE IF MISSING
            fprintf(output ? output : stdout, "%s\n", lines[i]);
        } else {
            fprintf(output ? output : stdout, "%s", lines[i]);
        }
    }

    // CLOSE FILE AND FREE MEMORY
    if (output) fclose(output);
    for (size_t i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
