
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *sourceFile, *destinationFile;
    char sourceFileName[100], destinationFileName[100];
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    printf("Enter source file name: ");
    scanf("%s", sourceFileName);

    printf("Enter destination file name: ");
    scanf("%s", destinationFileName);

    sourceFile = fopen(sourceFileName, "rb");
    if (sourceFile == NULL) {
        printf("Error: Unable to open source file\n");
        exit(EXIT_FAILURE);
    }

    destinationFile = fopen(destinationFileName, "wb");
    if (destinationFile == NULL) {
        printf("Error: Unable to open destination file\n");
        fclose(sourceFile);
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully\n");

    return 0;
}
/* step:- create one txt file in same dictionary and type in running code file.txt and
          please assume it have some data




/*
This is a simple C program to copy the contents of one file to another using buffered I/O. Here are the key steps in the code:
1. Define a buffer size for reading chunks of data.
2. Prompt the user to enter the source and destination file names.
3. Open the source file in binary read mode ("rb").
4. Check if the source file is opened successfully, and if not, print an error message and exit.
5. Open the destination file in binary write mode ("wb").
6. Check if the destination file is opened successfully, and if not, print an error message, close the source file, and exit.
7. Read chunks of data from the source file and write them to the destination file until the entire file is copied.
8. Close both files.
9. Print a success message. */
