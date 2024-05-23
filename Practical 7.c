#include <stdio.h>
#include <string.h> // For memcpy

#define RESOURCES 5
#define PROCESSES 4

int process[PROCESSES] = {210, 350, 100, 520};
int resource[RESOURCES] = {250, 600, 150, 500, 400};
int allocation[PROCESSES];

void initialize() {
    for (int i = 0; i < PROCESSES; i++) {
        allocation[i] = -1;
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    initialize();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;

        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);
                allocated = 1;
            }
        }

        if (!allocated) {
            printf("empty");
        }
        printf("\n");
    }

    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {
            printf("process %d\n", i + 1);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    initialize();
    for (int i = 0; i < n; i++) {
        int bestBlockIndex = -1;
        int minDifference = -1;
        for (int j = 0; j < m; j++) {
            int difference = blockSize[j] - processSize[i];
            if (difference >= 0 && (minDifference == -1 || difference < minDifference)) {
                bestBlockIndex = j;
                minDifference = difference;
            }
        }
        if (bestBlockIndex != -1) {
            allocation[i] = bestBlockIndex;
            blockSize[bestBlockIndex] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;

        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);
                allocated = 1;
            }
        }

        if (!allocated) {
            printf("empty");
        }
        printf("\n");
    }

    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {
            printf("process %d\n", i + 1);
        }
    }
}

int main() {
    int m = RESOURCES;
    int n = PROCESSES;
    int choice;

    int processCopy[PROCESSES];
    int resourceCopy[RESOURCES];

    // Copy process and resource arrays
    memcpy(processCopy, process, PROCESSES * sizeof(int));
    memcpy(resourceCopy, resource, RESOURCES * sizeof(int));

    do {
        printf("\nChoose an allocation method:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit(resourceCopy, m, processCopy, n);
                break;
            case 2:
                bestFit(resource, m, process, n);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
