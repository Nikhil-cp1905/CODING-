#include <stdio.h>

void findWaitingTime(int n, int burst_time[], int wait_time[]) {
    wait_time[0] = 0;  // First process has no waiting time

    for (int i = 1; i < n; i++) {
        wait_time[i] = burst_time[i-1] + wait_time[i-1];
    }
}

void findTurnAroundTime(int n, int burst_time[], int wait_time[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = burst_time[i] + wait_time[i];
    }
}

void findAverageTime(int n, int burst_time[], int priority[]) {
    int pid[n], wait_time[n], tat[n], total_wait = 0, total_tat = 0, temp;

    // Assign process IDs
    for (int i = 0; i < n; i++) {
        pid[i] = i+1;
    }

    // Sort processes by priority (lowest number = highest priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (priority[i] > priority[j]) {
                // Swap priorities
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap burst times
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process IDs
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Find waiting time for all processes
    findWaitingTime(n, burst_time, wait_time);

    // Find turn around time for all processes
    findTurnAroundTime(n, burst_time, wait_time, tat);

    // Display process information and calculate averages
    printf("Processes  Burst time  Priority  Waiting time  Turnaround time\n");

    for (int i = 0; i < n; i++) {
        total_wait += wait_time[i];
        total_tat += tat[i];
        printf("  %d\t\t%d\t   %d\t\t%d\t\t%d\n", pid[i], burst_time[i], priority[i], wait_time[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wait / n);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], priority[n];

    // Input process burst times and priorities
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and priority for process %d: ", i+1);
        scanf("%d %d", &burst_time[i], &priority[i]);
    }

    // Calculate and display average time
    findAverageTime(n, burst_time, priority);

    return 0;
}

