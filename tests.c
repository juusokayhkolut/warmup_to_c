////////////////////////////////////////////////////////////////////
// FILE WRITTEN BY JUUSO KÄYHKÖ (493675)                          //
//                                                                //
// AI TOOLS WERE USED FOR FINDING TESTING OBJECTIVES,             //
// BUT NOT FOR WRITING THE ACTUALY CODE.                          //
// FILE: tests.c                                                  //
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_emptyFile();
void test_singleLine();
void test_missingFile();
void test_invalidOutputFile();

void writeTestFile(const char *filename, const char *content);
void readFileAndCompare(const char *filename, const char *expected);
void deleteFile(const char *filename);

void test_noArguments() {
    int result = system("./reverse");
    assert(result != 0); // Should not be 0
}

void test_emptyFile() {
    writeTestFile("empty.txt", "");
    system("./reverse empty.txt output2.txt");
    readFileAndCompare("output2.txt", "");
    deleteFile("empty.txt");
    deleteFile("output2.txt");
}

void test_singleLine() {
    writeTestFile("single.txt", "onlyline\n");
    system("./reverse single.txt output3.txt");
    readFileAndCompare("output3.txt", "onlyline\n");
    deleteFile("single.txt");
    deleteFile("output3.txt");
}

void test_missingFile() {
    int result = system("./reverse doesnotexist.txt output4.txt > temp.txt 2>&1");
    assert(result != 0); // Should not be 0

    FILE *fp = fopen("temp.txt", "r");
    assert(fp != NULL); // Should not be NULL
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    assert(strncmp(buffer, "Failed to open input file.", 26) == 0);
    
    fclose(fp);
    deleteFile("temp.txt");
}

void test_invalidOutputFile() {
    writeTestFile("test5.txt", "first\n");
    int result = system("./reverse test5.txt /invalidpath/output5.txt > temp2.txt 2>&1");
    assert(result != 0); // Should not be 0
    
    FILE *fp = fopen("temp2.txt", "r");
    assert(fp != NULL); // Should not be NULL
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    assert(strncmp(buffer, "Failed to open output file.", 27) == 0);
    
    fclose(fp);
    deleteFile("test5.txt");
    deleteFile("temp2.txt");
}

//** Helper functions **//
void writeTestFile(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    assert(fp != NULL);
    fputs(content, fp);
    fclose(fp);
}

// Read file and compare content
void readFileAndCompare(const char *filename, const char *expected) {
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);
    char buffer[1000];
    fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[sizeof(buffer) - 1] = '\0';
    fclose(fp);
    assert(strcmp(buffer, expected) == 0);
}

void deleteFile(const char *filename) {
    remove(filename);
}

void run_tests() {
    fprintf(stdout, "Running test_noArguments...\n");
    test_noArguments();
    
    fprintf(stdout, "Running test_emptyFile...\n");
    test_emptyFile();
    
    fprintf(stdout, "Running test_singleLine...\n");
    test_singleLine();
    
    fprintf(stdout, "Running test_missingFile...\n");
    test_missingFile();

    fprintf(stdout, "Running test_invalidOutputFile...\n");
    test_invalidOutputFile();

    printf("All tests passed!\n");
}

int main() {
    run_tests();
    return 0;
}