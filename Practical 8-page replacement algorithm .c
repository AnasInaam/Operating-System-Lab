#include <stdio.h>

#define MAX_FRAMES 3 // Maximum number of frames
#define MAX_PAGES 100 // Maximum number of pages in the reference string
// FIFO page replacement algorithm
void fifo(int pages[], int n, int frames) {
    int frame[frames], frameIndex = 0, faults = 0;
    int i, j;

    // Initialize frame array with -1 indicating empty frames
    for (i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nFIFO Page Replacement:\n");

    // Iterate through the page reference string
    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        // If page not found in frames, replace page in FIFO manner
        if (!found) {
            faults++;
            frame[frameIndex] = page;
            frameIndex = (frameIndex + 1) % frames;
        }
    }

    // Print total page faults
    printf("Total Page Faults: %d\n", faults);
}

// LRU page replacement algorithm
void lru(int pages[], int n, int frames) {
    int frame[frames], lru[frames], faults = 0;
    int i, j, k, min;

    // Initialize frame and LRU arrays
    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        lru[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    // Iterate through the page reference string
    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                lru[j] = i + 1; // Update LRU value
                break;
            }
        }

        // If page not found in frames, replace least recently used page
        if (!found) {
            faults++;
            min = 0;
            for (j = 1; j < frames; j++) {
                if (lru[j] < lru[min]) {
                    min = j;
                }
            }
            frame[min] = page;
            lru[min] = i + 1;
        }
    }

    // Print total page faults
    printf("Total Page Faults: %d\n", faults);
}


int main() {
    // Page reference string
    int pages[MAX_PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    // Number of pages in the reference string
    int n = 20;

    // Number of frames
    int frames = MAX_FRAMES;

    int choice;

    // Menu loop
    do {
        printf("\nMenu:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, frames);
                break;
            case 2:
                lru(pages, n, frames);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

