#include <stdio.h>

int main() {
    int total, slots;
    printf("Enter number of pages: ");
    scanf("%d", &total);

    int refs[total];
    printf("Enter the page reference string:\n");
    for (int a = 0; a < total; a++)
        scanf("%d", &refs[a]);

    printf("Enter number of frames: ");
    scanf("%d", &slots);

    int mem[slots];
    for (int a = 0; a < slots; a++)
        mem[a] = -1;

    int next = 0, miss = 0;

    printf("\nPage\tFrames\n");
    for (int a = 0; a < total; a++) {
        int cur = refs[a];
        int hit = 0;

        for (int b = 0; b < slots; b++) {
            if (mem[b] == cur) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            mem[next] = cur;
            next = (next + 1) % slots;
            miss++;
        }

        printf("%d\t", cur);
        for (int b = 0; b < slots; b++) {
            if (mem[b] == -1)
                printf("- ");
            else
                printf("%d ", mem[b]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", miss);

    return 0;
}
