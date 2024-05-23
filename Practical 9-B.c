#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define DISK_SIZE 1000

typedef struct {
    char name[20];
    int start;
    int length;
} ContiguousFile;

typedef struct {
    char name[20];
    int start;
    int length;
} LinkedFile;

typedef struct {
    char name[20];
    int *blocks;
    int length;
} IndexedFile;

ContiguousFile contiguousFiles[MAX_FILES];
LinkedFile linkedFiles[MAX_FILES];
IndexedFile indexedFiles[MAX_FILES];
int disk[DISK_SIZE];

int contiguousCount = 0;
int linkedCount = 0;
int indexedCount = 0;

void initializeDisk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = -1;  // -1 indicates the block is free
    }
}

void createContiguousFile() {
    char name[20];
    int length;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file length: ");
    scanf("%d", &length);

    int start = -1;
    for (int i = 0; i <= DISK_SIZE - length; i++) {
        int free = 1;
        for (int j = 0; j < length; j++) {
            if (disk[i + j] != -1) {
                free = 0;
                break;
            }
        }
        if (free) {
            start = i;
            break;
        }
    }

    if (start != -1) {
        for (int i = start; i < start + length; i++) {
            disk[i] = contiguousCount;
        }
        strcpy(contiguousFiles[contiguousCount].name, name);
        contiguousFiles[contiguousCount].start = start;
        contiguousFiles[contiguousCount].length = length;
        contiguousCount++;
        printf("File created successfully.\n");
    } else {
        printf("Not enough contiguous space available.\n");
    }
}

void createLinkedFile() {
    char name[20];
    int length;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file length: ");
    scanf("%d", &length);

    int *blocks = malloc(length * sizeof(int));
    if (blocks == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < DISK_SIZE && count < length; i++) {
        if (disk[i] == -1) {
            blocks[count] = i;
            count++;
        }
    }

    if (count == length) {
        for (int i = 0; i < length; i++) {
            disk[blocks[i]] = linkedCount;
        }
        strcpy(linkedFiles[linkedCount].name, name);
        linkedFiles[linkedCount].start = blocks[0];
        linkedFiles[linkedCount].length = length;
        linkedCount++;
        printf("File created successfully.\n");
    } else {
        printf("Not enough free space available.\n");
        free(blocks);
    }
}

void createIndexedFile() {
    char name[20];
    int length;

    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file length: ");
    scanf("%d", &length);

    int *blocks = malloc(length * sizeof(int));
    if (blocks == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int indexBlock = -1;
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == -1) {
            indexBlock = i;
            break;
        }
    }

    if (indexBlock == -1) {
        printf("No free block for index block.\n");
        free(blocks);
        return;
    }

    int count = 0;
    for (int i = 0; i < DISK_SIZE && count < length; i++) {
        if (disk[i] == -1) {
            blocks[count] = i;
            count++;
        }
    }

    if (count == length) {
        disk[indexBlock] = indexedCount;
        for (int i = 0; i < length; i++) {
            disk[blocks[i]] = indexedCount;
        }
        strcpy(indexedFiles[indexedCount].name, name);
        indexedFiles[indexedCount].blocks = blocks;
        indexedFiles[indexedCount].length = length;
        indexedCount++;
        printf("File created successfully.\n");
    } else {
        printf("Not enough free space available.\n");
        free(blocks);
    }
}

void displayFiles() {
    printf("\nContiguous Allocation:\n");
    for (int i = 0; i < contiguousCount; i++) {
        printf("File: %s, Start: %d, Length: %d\n", contiguousFiles[i].name, contiguousFiles[i].start, contiguousFiles[i].length);
    }

    printf("\nLinked Allocation:\n");
    for (int i = 0; i < linkedCount; i++) {
        printf("File: %s, Start: %d, Length: %d\n", linkedFiles[i].name, linkedFiles[i].start, linkedFiles[i].length);
    }

    printf("\nIndexed Allocation:\n");
    for (int i = 0; i < indexedCount; i++) {
        printf("File: %s, Blocks: ", indexedFiles[i].name);
        for (int j = 0; j < indexedFiles[i].length; j++) {
            printf("%d ", indexedFiles[i].blocks[j]);
        }
        printf("\n");
    }
}

int main() {
    int choice;
    initializeDisk();

    while (1) {
        printf("\nFile Allocation Techniques\n");
        printf("1. Create Contiguous File\n");
        printf("2. Create Linked File\n");
        printf("3. Create Indexed File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createContiguousFile();
                break;
            case 2:
                createLinkedFile();
                break;
            case 3:
                createIndexedFile();
                break;
            case 4:
                displayFiles();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
