#include <stdio.h>

#define N 3  // Number of frames

void pagereplace(int pages[], int n, int method) {
    int frame[N] = {-1, -1, -1};
    int time[N] = {0, 0, 0};
    int freq[N] = {0, 0, 0};
    int fault = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0, idx = 0;

        // Check if page is already in frame
        for (int j = 0; j < N; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                if (method == 1) time[j] = i;  // Update time for LRU
                if (method == 2) freq[j]++;    // Update frequency for LFU
                break;
            }
        }

        // If page is not in frame, a fault occurs
        if (found == 0) {
            fault++;
            
            if (method == 0) {  // FIFO replacement logic
                idx = 0;
                for (int j = 1; j < N; j++) {
                    if (time[j] < time[idx]) {
                        idx = j;  // Find the oldest page in terms of arrival time
                    }
                }
            } else if (method == 1) {  // LRU replacement logic
                idx = 0;
                for (int j = 1; j < N; j++) {
                    if (time[j] < time[idx]) {
                        idx = j;  // Find least recently used page
                    }
                }
            } else if (method == 2) {  // LFU replacement logic
                idx = 0;
                for (int j = 1; j < N; j++) {
                    if (freq[j] < freq[idx]) {
                        idx = j;  // Find least frequently used page
                    } else if (freq[j] == freq[idx] && time[j] < time[idx]) {
                        idx = j;  // Resolve ties by arrival time
                    }
                }
            }

            // Replace the page
            frame[idx] = pages[i];
            time[idx] = i;
            freq[idx] = 1;
        }

        // Display frame content
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < N; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Page faults (method %d): %d\n\n", method, fault);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3, 1, 3, 1, 0, 1, 3};
    int n = sizeof(pages) / sizeof(pages[0]);

    printf("FIFO Algorithm\n");
    pagereplace(pages, n, 0);

    printf("LRU Algorithm\n");
    pagereplace(pages, n, 1);

    printf("LFU Algorithm\n");
    pagereplace(pages, n, 2);

    return 0;
}
