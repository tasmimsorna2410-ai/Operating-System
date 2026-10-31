#include <stdio.h>

int pickVictim(int refs[], int mem[], int total, int slots, int from) {
    int far = -1, chosen = -1;
    for (int a = 0; a < slots; a++) {
        int b;
        for (b = from; b < total; b++) {
            if (mem[a] == refs[b]) {
                if (b > far) {
                    far = b;
                    chosen = a;
                }
                break;
            }
        }
        if (b == total)
            return a;
    }
    return (chosen == -1) ? 0 : chosen;
}

int main() {
    int total, slots;
    printf("Enter number of pages: ");
    scanf("%d", &total);

    int refs[total];
    printf("Enter page reference string:\n");
    for (int a = 0; a < total; a++)
        scanf("%d", &refs[a]);

    printf("Enter number of frames: ");
    scanf("%d", &slots);

    int mem[slots], miss = 0;
    for (int a = 0; a < slots; a++)
        mem[a] = -1;

    printf("\nPage\tFrames\n");
    for (int a = 0; a < total; a++) {
        int cur = refs[a], hit = 0;

        for (int b = 0; b < slots; b++)
            if (mem[b] == cur)
                hit = 1;

        if (!hit) {
            int blank = -1;
            for (int b = 0; b < slots; b++)
                if (mem[b] == -1)
                    blank = b;

            if (blank != -1)
                mem[blank] = cur;
            else
                mem[pickVictim(refs, mem, total, slots, a + 1)] = cur;

            miss++;
        }

        printf("%d\t", cur);
        for (int b = 0; b < slots; b++)
            (mem[b] == -1) ? printf("- ") : printf("%d ", mem[b]);
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", miss);
    return 0;
}
