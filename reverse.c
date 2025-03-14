////////////////////////////////////////////////////////////////////
// FILE WRITTEN BY JUUSO KÄYHKÖ (493675)                          //
//                                                                //
// AI TOOLS WERE USED FOR ALGORHITM GENERATION,                   //
// BUT NOT FOR WRITING THE ACTUALY CODE.                          //
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
    // REMOVE LINE IF IT EXISTS
    line[strcspn(line, "\n")] = 0;
    return line;
}

int main(int argc, char *argv[]) {
    // CHECK IF AT LEAST ONE ARGUMENT WAS GIVEN
    if (argc < 2) {
        printf("Please provide arguments for input file and optionally output file\n");
        exit(1);
    }

    // CHECK IF INPUT AND OUTPUT (NAME) IS THE SAME
    if (argc >= 3 && strcmp(argv[1], argv[2]) == 0) {
        printf("Input and output file must differ\n");
        exit(1);
    }

    FILE *input = fopen(argv[1], "r");

    // INITIAL CAPACITY, GROW AS NEEDED IF FILE IS VERY LARGE
    size_t capacity = 10;
    size_t count = 0;
    char **lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        printf("malloc failed\n");
        fclose(input);
        exit(1);
    }

    // OPEN INPUT FILE
    if (!input) {
        printf("error: cannot open file '%s'.\n", argv[1]);
        exit(1);
    }

    // READ FROM INPUT FILE
    char *line;
    while ((line = readLine(input)) != NULL) {
        if (count >= capacity) {
            capacity *= 2; // double the capacity
            char **temp = realloc(lines, capacity * sizeof(char *));
            if (!temp) {
                printf("malloc failed\n");
                free(line);
                for (size_t i = 0; i < count; i++) free(lines[i]);
                free(lines);
                fclose(input);
                exit(1);
            }
            lines = temp;
        }
        lines[count++] = line;
    }
    fclose(input);

    // OPEN OUTPUT (IF ONE WAS GIVEN)
    FILE *output = NULL;
    if (argc >= 3) {
        output = fopen(argv[2], "w");
        if (!output) {
            printf("error: cannot open file '%s'.\n", argv[2]);
            fclose(input);
            exit(1);
        }
    }

    // WRITE OR PRINT LINES IN REVERSE
    for (int i = count - 1; i >= 0; i--) {
        if (output) {
            fprintf(output, "%s\n", lines[i]);
        } else {
            printf("%s\n", lines[i]);
        }
    }

    // CLOSE FILE AND FREE MEMORY
    if (output) fclose(output);
    free(lines);

    return 0;
}
