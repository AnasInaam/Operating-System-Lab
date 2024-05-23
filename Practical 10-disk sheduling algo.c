#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

// Function to calculate total head movement using FCFS algorithm
int fcfs(int head, int requests[], int n) {
    int total_movement = 0;
    int current_pos = head;
    int i;
    for (i = 0; i < n; i++) {
        total_movement += abs(current_pos - requests[i]);
        current_pos = requests[i];
    }
    return total_movement;
}

// Function to calculate total head movement using SSTF algorithm
int sstf(int head, int requests[], int n) {
    int total_movement = 0;
    int current_pos = head;
    int remaining[n]; // To keep track of remaining requests
    int i, j;
    for (i = 0; i < n; i++) {
        remaining[i] = 1; // Mark all requests as remaining initially
    }
    for (i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int next_request;
        for (j = 0; j < n; j++) {
            if (remaining[j] && abs(current_pos - requests[j]) < min_distance) {
                min_distance = abs(current_pos - requests[j]);
                next_request = j;
            }
        }
        total_movement += min_distance;
        current_pos = requests[next_request];
        remaining[next_request] = 0; // Mark the chosen request as processed
    }
    return total_movement;
}

// Function to calculate total head movement using SCAN algorithm
int scan(int head, int requests[], int n) {
    int total_movement = 0;
    int current_pos = head;
    int i, j;
    // Sort requests and divide into lower and upper sequences
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    // Find index of head position in sorted requests
    int idx;
    for (idx = 0; idx < n; idx++) {
        if (requests[idx] >= head)
            break;
    }
    // Move head towards lower end and then towards upper end
    for (i = idx-1; i >= 0; i--) {
        total_movement += abs(current_pos - requests[i]);
        current_pos = requests[i];
    }
    total_movement += current_pos; // Move to track 0
    current_pos = 0;
    for (i = idx; i < n; i++) {
        total_movement += abs(current_pos - requests[i]);
        current_pos = requests[i];
    }
    return total_movement;
}

int main() {
    printf("Disk Scheduling Algorithms\n");
    int head = 50; // Initial disk head position
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67}; // Predefined sequence of disk requests
    int n = sizeof(requests) / sizeof(requests[0]); // Number of requests

    printf("Initial disk head position: %d\n", head);
    printf("Sequence of disk requests: ");
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int choice;
    while (1) {
        printf("\nMain Menu\n");
        printf("1. FCFS (First-Come, First-Served)\n");
        printf("2. SSTF (Shortest Seek Time First)\n");
        printf("3. SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Total head movement using FCFS: %d\n", fcfs(head, requests, n));
                break;
            case 2:
                printf("Total head movement using SSTF: %d\n", sstf(head, requests, n));
                break;
            case 3:
                printf("Total head movement using SCAN: %d\n", scan(head, requests, n));
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
