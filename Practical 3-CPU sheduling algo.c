#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSES 5

typedef struct {
    int process_id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculateWaitingTimeFCFS(Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void fcfs(Process processes[], int n) {
    calculateWaitingTimeFCFS(processes, n);
    calculateTurnaroundTime(processes, n);

    printf("FCFS Scheduling:\n");
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void sjf(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    calculateWaitingTimeFCFS(processes, n); // Reuse FCFS waiting time calculation for sorted processes
    calculateTurnaroundTime(processes, n);

    printf("SJF Scheduling:\n");
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process processes[NUM_PROCESSES] = {
        {1, 10, 0, 0},
        {2, 5, 0, 0},
        {3, 8, 0, 0},
        {4, 6, 0, 0},
        {5, 2, 0, 0}
    };

    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. FCFS Scheduling\n");
        printf("2. SJF Scheduling\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Make a copy of the processes array to avoid sorting the original array in SJF
        Process processes_copy[NUM_PROCESSES];
        for (int i = 0; i < NUM_PROCESSES; i++) {
            processes_copy[i] = processes[i];
        }

        switch (choice) {
            case 1:
                fcfs(processes_copy, NUM_PROCESSES);
                break;
            case 2:
                sjf(processes_copy, NUM_PROCESSES);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
