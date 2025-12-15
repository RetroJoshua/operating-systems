#include <stdio.h>

#define FRAMES 3
#define PAGES 12

int fr[FRAMES];

void display() {
    int i;
    printf("\n");
    for (i = 0; i < FRAMES; i++)
        printf("%d\t", fr[i]);
}

int main() {
    int page[PAGES] = {2,3,2,1,5,2,4,5,3,2,5,2};
    int last_used[FRAMES];   // store "time" when each frame was last used
    int time = 0;
    int pf = 0;
    int i, j;

    // initialize frames as empty
    for (i = 0; i < FRAMES; i++) {
        fr[i] = -1;
        last_used[i] = -1;
    }

    for (j = 0; j < PAGES; j++) {
        int current = page[j];
        int hit = 0;
        time++;

        // 1. Check if page is already in a frame (HIT)
        for (i = 0; i < FRAMES; i++) {
            if (fr[i] == current) {
                hit = 1;
                last_used[i] = time;  // update last used time
                break;
            }
        }

        if (!hit) {
            // 2. Check for an empty frame first
            int placed = 0;
            for (i = 0; i < FRAMES; i++) {
                if (fr[i] == -1) {
                    fr[i] = current;
                    last_used[i] = time;
                    pf++;
                    placed = 1;
                    break;
                }
            }

            // 3. If no empty frame, replace LRU page
            if (!placed) {
                int lru_index = 0;
                int min_time = last_used[0];

                for (i = 1; i < FRAMES; i++) {
                    if (last_used[i] < min_time) {
                        min_time = last_used[i];
                        lru_index = i;
                    }
                }

                fr[lru_index] = current;
                last_used[lru_index] = time;
                pf++;
            }
        }

        display();
    }

    printf("\nNumber of page faults (LRU): %d\n", pf);

    return 0;
}