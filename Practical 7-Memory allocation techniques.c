/*
 * Practical 7 - Memory Allocation Techniques
 * 
 * This program demonstrates two memory allocation algorithms:
 * 1. First Fit Algorithm - Allocates the first block large enough to accommodate the process
 * 2. Best Fit Algorithm - Allocates the smallest block that can accommodate the process
 * 
 * The program uses predefined process sizes and memory blocks to simulate
 * memory allocation in an operating system.
 */

#include <stdio.h>
#include <string.h> // For memcpy

// Constants defining the number of memory blocks and processes
#define RESOURCES 5    // Number of available memory blocks
#define PROCESSES 4    // Number of processes to allocate

// Global arrays to store process and resource information
int process[PROCESSES] = {210, 350, 100, 520};        // Process sizes in KB
int resource[RESOURCES] = {250, 600, 150, 500, 400};  // Memory block sizes in KB
int allocation[PROCESSES];                              // Allocation tracking array (-1 = not allocated)

/*
 * Initialize allocation array
 * Sets all allocation entries to -1, indicating no process is allocated to any block
 */
void initialize() {
    for (int i = 0; i < PROCESSES; i++) {
        allocation[i] = -1;  // -1 indicates process i is not allocated to any block
    }
}

/*
 * First Fit Algorithm Implementation
 * 
 * This algorithm allocates the first available block that is large enough
 * to accommodate the process. It searches memory blocks sequentially from
 * the beginning until it finds a suitable block.
 * 
 * Parameters:
 * - blockSize[]: Array of memory block sizes (modified during allocation)
 * - m: Number of memory blocks
 * - processSize[]: Array of process sizes
 * - n: Number of processes
 */
void firstFit(int blockSize[], int m, int processSize[], int n) {
    initialize();  // Reset allocation array
    
    // Iterate through each process
    for (int i = 0; i < n; i++) {
        // Search for the first block that can accommodate the current process
        for (int j = 0; j < m; j++) {
            // Check if current block is large enough for the process
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;                    // Allocate block j to process i
                blockSize[j] -= processSize[i];       // Reduce available block size
                break;                                // Move to next process
            }
        }
    }
    
    // Display allocation results
    printf("\nFirst Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    
    // Display which processes are allocated to each block
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;  // Flag to track if block has any allocation

        // Check which processes are allocated to block j
        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);  // Print process number (1-indexed)
                allocated = 1;
            }
        }

        // If no process is allocated to this block
        if (!allocated) {
            printf("empty");
        }
        printf("\n");
    }

    // Display processes that could not be allocated
    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {  // Process not allocated
            printf("process %d\n", i + 1);
        }
    }
}

/*
 * Best Fit Algorithm Implementation
 * 
 * This algorithm allocates the smallest available block that is large enough
 * to accommodate the process. It searches all memory blocks to find the one
 * that minimizes wasted space after allocation.
 * 
 * Parameters:
 * - blockSize[]: Array of memory block sizes (modified during allocation)
 * - m: Number of memory blocks
 * - processSize[]: Array of process sizes
 * - n: Number of processes
 */
void bestFit(int blockSize[], int m, int processSize[], int n) {
    initialize();  // Reset allocation array
    
    // Iterate through each process
    for (int i = 0; i < n; i++) {
        int bestBlockIndex = -1;    // Index of the best fitting block
        int minDifference = -1;     // Minimum size difference found so far
        
        // Search all blocks to find the best fit
        for (int j = 0; j < m; j++) {
            int difference = blockSize[j] - processSize[i];  // Calculate remaining space
            
            // Check if block can accommodate process and is better than current best
            if (difference >= 0 && (minDifference == -1 || difference < minDifference)) {
                bestBlockIndex = j;         // Update best block index
                minDifference = difference; // Update minimum difference
            }
        }
        
        // If a suitable block was found, allocate it
        if (bestBlockIndex != -1) {
            allocation[i] = bestBlockIndex;                        // Allocate block to process
            blockSize[bestBlockIndex] -= processSize[i];          // Reduce available block size
        }
    }
    
    // Display allocation results
    printf("\nBest Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    
    // Display which processes are allocated to each block
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;  // Flag to track if block has any allocation

        // Check which processes are allocated to block j
        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);  // Print process number (1-indexed)
                allocated = 1;
            }
        }

        // If no process is allocated to this block
        if (!allocated) {
            printf("empty");
        }
        printf("\n");
    }

    // Display processes that could not be allocated
    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {  // Process not allocated
            printf("process %d\n", i + 1);
        }
    }
}

/*
 * Main function - Program entry point
 * 
 * Provides a menu-driven interface for testing different memory allocation algorithms.
 * The program creates copies of the original arrays to preserve the original data
 * for multiple test runs.
 */
int main() {
    int m = RESOURCES;  // Number of memory blocks
    int n = PROCESSES;  // Number of processes
    int choice;         // User's menu choice

    // Create working copies of process and resource arrays
    // This preserves original data for multiple algorithm runs
    int processCopy[PROCESSES];
    int resourceCopy[RESOURCES];

    // Copy process and resource arrays to preserve original data
    memcpy(processCopy, process, PROCESSES * sizeof(int));
    memcpy(resourceCopy, resource, RESOURCES * sizeof(int));

    // Main program loop - display menu and execute user choice
    do {
        // Display menu options
        printf("\nChoose an allocation method:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                // Execute First Fit algorithm using copies
                firstFit(resourceCopy, m, processCopy, n);
                break;
            case 2:
                // Execute Best Fit algorithm using original arrays
                // Note: This modifies the original resource array
                bestFit(resource, m, process, n);
                break;
            case 3:
                // Exit program
                printf("Exiting the program.\n");
                break;
            default:
                // Handle invalid menu choice
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 3);  // Continue until user chooses to exit

    return 0;  // Successful program termination
}
