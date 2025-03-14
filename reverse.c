#include <stdio.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LEN 100

int main(int argc, char *argv[]) {
    // Check if at least one argument was given
    if (argc < 2) {
        printf("Please provide arguments for input file and optionally output file\n");
        return 1;
    }

    char lines[MAX_LINES][MAX_LEN];
    int count = 0;

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Failed to open input file.\n");
        return 1;
    }

    // If output file argument was given, open the file to write
    FILE *output = NULL;
    if (argc >= 3) {
        output = fopen(argv[2], "w");
        if (!output) {
            printf("Failed to open output file.\n");
            fclose(input);
            return 1;
        }
    }

    // Read from the input file and add it to lines
    while (fgets(lines[count], MAX_LEN, input) && count < MAX_LINES) {
        lines[count][strcspn(lines[count], "\n")] = 0;
        count++;
    }
    fclose(input);

    // Depending on if output file was given, write or print reversed list
    for (int i = count - 1; i >= 0; i--) {
        if (output) {
            fprintf(output, "%s\n", lines[i]);
        } else {
            printf("%s\n", lines[i]);
        }
    }

    // Close output file if needed
    if (output) fclose(output);

    return 0;
}
