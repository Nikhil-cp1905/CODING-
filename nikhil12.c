#include <stdio.h>

#define MAX 20

void fifo(int pages[], int n, int capacity) {
    int frames[MAX], front = 0, rear = 0, page_faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            frames[rear] = pages[i];
            rear = (rear + 1) % capacity;
            page_faults++;
        }
        
        printf("\nFrames after inserting %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) printf("_ ");
            else printf("%d ", frames[j]);
        }
    }
    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
}

void lru(int pages[], int n, int capacity) {
    int frames[MAX], time[MAX], page_faults = 0, counter = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag = 0, least = counter;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                time[j] = counter;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            int pos = 0;
            for (int j = 0; j < capacity; j++) {
                if (time[j] < least) {
                    least = time[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            time[pos] = counter;
            page_faults++;
        }
        counter++;
        
        printf("\nFrames after inserting %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) printf("_ ");
            else printf("%d ", frames[j]);
        }
    }
    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

void lfu(int pages[], int n, int capacity) {
    int frames[MAX], count[MAX], page_faults = 0;
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int flag = 0, least = count[0], pos = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                count[j]++;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            for (int j = 0; j < capacity; j++) {
                if (count[j] < least || frames[j] == -1) {
                    least = count[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            count[pos] = 1;
            page_faults++;
        }

        printf("\nFrames after inserting %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) printf("_ ");
            else printf("%d ", frames[j]);
        }
    }
    printf("\nTotal Page Faults (LFU): %d\n", page_faults);
}

int main() {
    int pages[MAX], n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    printf("\n--- FIFO Page Replacement ---\n");
    fifo(pages, n, capacity);

    printf("\n--- LRU Page Replacement ---\n");
    lru(pages, n, capacity);

    printf("\n--- LFU Page Replacement ---\n");
    lfu(pages, n, capacity);

    return 0;
}
