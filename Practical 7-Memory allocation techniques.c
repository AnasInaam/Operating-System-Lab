/*
 * Practical 7 - Memory Allocation Techniques
 * 
 * This program demonstrates two fundamental memory allocation algorithms:
 * 1. First Fit Algorithm - Allocates memory to the first available block that is large enough
 * 2. Best Fit Algorithm - Allocates memory to the smallest available block that can fit the process
 * 
 * These algorithms are used in operating systems for dynamic memory allocation
 * to optimize memory usage and minimize fragmentation.
 */

#include <stdio.h>
#include <string.h> // For memcpy function

// Constants defining the number of memory blocks and processes
#define RESOURCES 5  // Number of memory blocks available
#define PROCESSES 4  // Number of processes requesting memory

// Global arrays storing process sizes and memory block sizes
int process[PROCESSES] = {210, 350, 100, 520};    // Size of each process in KB
int resource[RESOURCES] = {250, 600, 150, 500, 400}; // Size of each memory block in KB
int allocation[PROCESSES]; // Tracks which block each process is allocated to (-1 = not allocated)

/*
 * Function: initialize
 * Purpose: Initialize the allocation array to indicate no processes are allocated initially
 * Sets all allocation values to -1 (meaning unallocated)
 */
void initialize() {
    for (int i = 0; i < PROCESSES; i++) {
        allocation[i] = -1; // -1 indicates process is not allocated to any block
    }
}

/*
 * Function: firstFit
 * Purpose: Implements the First Fit memory allocation algorithm
 * Algorithm: For each process, find the first memory block that is large enough
 * 
 * Parameters:
 *   blockSize[] - Array of available memory block sizes
 *   m - Number of memory blocks
 *   processSize[] - Array of process memory requirements  
 *   n - Number of processes
 * 
 * First Fit Algorithm:
 * - Scan memory blocks from beginning
 * - Allocate the first block that is >= process size
 * - Simple and fast, but may lead to fragmentation
 */
void firstFit(int blockSize[], int m, int processSize[], int n) {
    initialize(); // Reset allocation array
    
    // Try to allocate each process to the first suitable block
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Check if current block is large enough for the process
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j; // Allocate process i to block j
                blockSize[j] -= processSize[i]; // Reduce available space in the block
                break; // Move to next process (first fit found)
            }
        }
    }
    
    // Display First Fit allocation results
    printf("\nFirst Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    
    // Show which processes are allocated to each block
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;

        // Check if any process is allocated to this block
        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);
                allocated = 1;
            }
        }

        if (!allocated) {
            printf("empty"); // No process allocated to this block
        }
        printf("\n");
    }

    // Display processes that couldn't be allocated
    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {
            printf("process %d\n", i + 1);
        }
    }
}

/*
 * Function: bestFit
 * Purpose: Implements the Best Fit memory allocation algorithm
 * Algorithm: For each process, find the smallest memory block that can fit it
 * 
 * Parameters:
 *   blockSize[] - Array of available memory block sizes
 *   m - Number of memory blocks
 *   processSize[] - Array of process memory requirements
 *   n - Number of processes
 * 
 * Best Fit Algorithm:
 * - Scan all memory blocks for each process
 * - Find the block with minimum waste (smallest block that fits)
 * - Minimizes internal fragmentation but may increase external fragmentation
 * - More complex than First Fit but better memory utilization
 */
void bestFit(int blockSize[], int m, int processSize[], int n) {
    initialize(); // Reset allocation array
    
    // Try to allocate each process to the best fitting block
    for (int i = 0; i < n; i++) {
        int bestBlockIndex = -1;     // Index of the best fitting block
        int minDifference = -1;      // Minimum waste (difference between block and process size)
        
        // Search through all blocks to find the best fit
        for (int j = 0; j < m; j++) {
            int difference = blockSize[j] - processSize[i]; // Calculate waste
            
            // Check if block can fit the process and is better than current best
            if (difference >= 0 && (minDifference == -1 || difference < minDifference)) {
                bestBlockIndex = j;
                minDifference = difference;
            }
        }
        
        // Allocate to the best fitting block if found
        if (bestBlockIndex != -1) {
            allocation[i] = bestBlockIndex;
            blockSize[bestBlockIndex] -= processSize[i]; // Reduce available space
        }
    }
    
    // Display Best Fit allocation results
    printf("\nBest Fit Allocation:\n");
    printf("\nBlock No.\tProcess No.\n");
    
    // Show which processes are allocated to each block
    for (int j = 0; j < RESOURCES; j++) {
        printf("%d\t\t", j + 1);
        int allocated = 0;

        // Check if any process is allocated to this block
        for (int i = 0; i < PROCESSES; i++) {
            if (allocation[i] == j) {
                printf("%d ", i + 1);
                allocated = 1;
            }
        }

        if (!allocated) {
            printf("empty"); // No process allocated to this block
        }
        printf("\n");
    }

    // Display processes that couldn't be allocated
    printf("\nNot Allocated Process\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] == -1) {
            printf("process %d\n", i + 1);
        }
    }
}

/*
 * Function: main
 * Purpose: Main program that provides a menu interface for testing memory allocation algorithms
 * Allows users to compare First Fit and Best Fit algorithms with the same set of processes
 */
int main() {
    int m = RESOURCES; // Number of memory blocks
    int n = PROCESSES; // Number of processes
    int choice;        // User's menu choice

    // Create copies of the original arrays to preserve original data
    // This allows multiple algorithm runs without affecting the original data
    int processCopy[PROCESSES];
    int resourceCopy[RESOURCES];

    // Copy process and resource arrays to preserve original values
    memcpy(processCopy, process, PROCESSES * sizeof(int));
    memcpy(resourceCopy, resource, RESOURCES * sizeof(int));

    // Main program loop - display menu and process user choices
    do {
        printf("\nChoose an allocation method:\n");
        printf("1. First Fit\n");   // Quick allocation, may waste space
        printf("2. Best Fit\n");    // Better space utilization, slower allocation
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Run First Fit algorithm using copied arrays (preserves original data)
                firstFit(resourceCopy, m, processCopy, n);
                break;
            case 2:
                // Run Best Fit algorithm using original arrays
                // Note: This will modify the original resource array
                bestFit(resource, m, process, n);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 3); // Continue until user chooses to exit

    return 0;
}
