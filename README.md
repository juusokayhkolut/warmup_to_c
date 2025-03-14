# Documentation for reverse program

## Files
- reverse.c: Includes main logic for reversing operations
- tests.c: Includes tests for reverse program
- Makefile: Responsible for translating c code

### reverse.c
- `readLine`: reads a single line
- `main`
    - Checks for appropriate arguments
    - Opens input file, reads all lines into a dynamically growing array
    - Prints or writes lines in reverse order (depending on if output argument was given)
    - Frees memory and closes files

### tests.c
#### Tests
- `test_noArguments`: tests for no arguments (expected: return 1)
- `test_emptyFile`: tests for empty input file (expected: "" input file)
- `test_singleFile`: tests for single line input file (expected: output same as input)
- `test_missingFile`: tests for missing input file (expected: 1)
- `test_invalidOutputFile`: tests invalid output file (expected: 1)

#### Helper functions
- `writeTestFile`: write file with given name and content
- `readFileAndCompare`: compares file content to expected
- `deleteFile`: deletes file
- `readFileAndCompare`: compares file content to expected

### Makefile
Converted: gcc
Flags:
- Wall: Enable all common warnings
- Wextra: Enable extra warnings
- std=c11: Use C11 standard for compiling the code

#### Commands
- make all: Compiles reverse (main) and test file
- make reverse: Compiles reverse (main) file
- make tests: Compiles test file
- make test: Runs tests
- make clean: Removes files

## Running the program
To turn the program, use
```make all```
to generate all necessary files. Then, run:
```./reverse <input> <output>```
To run tests, run
```make test```