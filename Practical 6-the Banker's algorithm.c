
/* the Banker's algorithm: */

#include <stdio.h>

int main() {
    // Number of processes and resources
    int n = 5; // Number of processes (P0, P1, P2, P3, P4)
    int m = 3; // Number of resource types (e.g., resources R0, R1, R2)

    // Allocation matrix: the amount of each resource currently allocated to each process
    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Maximum matrix: the maximum demand of each resource by each process
    int max[5][3] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    // Available array: the number of available instances of each resource type
    int avail[3] = {3, 3, 2};

    // Finish array to keep track of which processes have completed
    int finish[n], safe_sequence[n];
    // Index for the safe sequence array
    int sequence_index = 0;

    // Initialize the finish array (0 means process not yet finished)
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Need matrix calculation code
    // Calculate the Need matrix from the maximum and allocation matrices
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Variable to keep track of whether a process can be safely executed
    int is_safe = 1;

    // Main loop to find a safe sequence of processes
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            // Check each process to see if it can be safely executed
            if (!finish[i]) { // Only consider unfinished processes
                int can_execute = 1;
                // Check if the process's needs can be satisfied by available resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        can_execute = 0;
                        break;
                    }
                }
                // If the process can be safely executed
                if (can_execute) {
                    // Add the process to the safe sequence
                    safe_sequence[sequence_index++] = i;
                    // Release the resources back to the available array
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    // Mark the process as finished
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if the system is in a safe state
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            is_safe = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    // If the system is in a safe state, print the safe sequence
    if (is_safe) {
        printf("The system is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n - 1; i++) {
            printf("P%d -> ", safe_sequence[i]);
        }
        printf("P%d\n", safe_sequence[n - 1]);
    }

    return 0;
}


/*

- **alloc**: Represents the allocation matrix. It contains the current allocation of resources to each process.
- **max**: Represents the maximum matrix. It contains the maximum demand of each resource by each process.
- **avail**: Represents the available resources array. It contains the available resources in the system.
- **finish**: An array used to keep track of which processes have completed execution.
- **safe_sequence**: An array used to keep track of the safe sequence of processes.
- **sequence_index**: An index to keep track of the safe sequence.
- **need**: Represents the need matrix, which is calculated by subtracting the allocation from the maximum for each process.
- **is_safe**: A flag used to check whether the system is in a safe state.

The program calculates the `need` matrix and checks whether the system is in a safe state.
If the system is safe, it prints the safe sequence of processes.
Otherwise, it prints a message indicating that the system is not safe.
*/
