#include <stdio.h>

void printTable(int n, int m, int alloc[n][m], int max[n][m], int need[n][m], int avail[m]) {
    printf("\nProcess\t\tAllocated\t\tMaximum\t\t\tNeed\t\t\tAvailable\n");
    printf("\t\tRes0 Res1 Res2\t\tRes0 Res1 Res2\t\tRes0 Res1 Res2\t\tRes0 Res1 Res2\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t", i);
        // Print allocated resources
        for (int j = 0; j < m; j++) {
            printf("%d   ", alloc[i][j]);
        }
        printf("\t\t");
        // Print maximum resources
        for (int j = 0; j < m; j++) {
            printf("%d   ", max[i][j]);
        }
        printf("\t\t");
        // Print need resources
        for (int j = 0; j < m; j++) {
            printf("%d   ", need[i][j]);
        }
        // Print available resources for the first process (initial values)
        if (i == 0) {
            printf("\t\t");
            for (int j = 0; j < m; j++) {
                printf("%d   ", avail[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resources

    // Allocation matrix
    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Maximum resources matrix
    int max[5][3] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    // Available resources
    int avail[3] = {3, 3, 2}; 

    // Finishing flag array
    int f[n], ans[n], ind = 0;

    // Initialize all processes as unfinished
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    // Need matrix
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Print the initial table
    printTable(n, m, alloc, max, need, avail);

    int y = 0;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("\nThe system is not in a safe state.\n");
            break;
        }
    }

    if (flag == 1) {
        printf("\nFollowing is the SAFE Sequence:\n");
        for (int i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}

