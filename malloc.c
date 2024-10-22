#include <stdio.h>

void allocate(int blockSize[], int m, int processSize[], int n, char type) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (idx == -1 || 
                   (type == 'B' && blockSize[j] < blockSize[idx]) || 
                   (type == 'W' && blockSize[j] > blockSize[idx])) 
                    idx = j;
            }
        }
        if (idx != -1) {
            allocation[i] = idx;
            blockSize[idx] -= processSize[i];
        }
    }

    printf("\n%s Fit Allocation:\n", (type == 'F') ? "First" : (type == 'B') ? "Best" : "Worst");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600}, processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]), n = sizeof(processSize) / sizeof(processSize[0]);
    int b1[m], b2[m], b3[m];

    for (int i = 0; i < m; i++) b1[i] = b2[i] = b3[i] = blockSize[i];

    allocate(b1, m, processSize, n, 'F'); // First Fit
    allocate(b2, m, processSize, n, 'B'); // Best Fit
    allocate(b3, m, processSize, n, 'W'); // Worst Fit

    return 0;
}

