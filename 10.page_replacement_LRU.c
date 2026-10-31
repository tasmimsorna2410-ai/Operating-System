#include <stdio.h>

int getLru(int stamp[], int n) {
    int a, low = stamp[0], idx = 0;
    for (a = 1; a < n; a++) {
        if (stamp[a] < low) {
            low = stamp[a];
            idx = a;
        }
    }
    return idx;
}

int main() {
    int numPages, numFrames, mem[10], refs[30], tick = 0, stamp[10];
    int hit, placed, a, b, victim, miss = 0;

    printf("Enter number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter reference string: ");
    for (a = 0; a < numPages; a++)
        scanf("%d", &refs[a]);

    for (a = 0; a < numFrames; a++)
        mem[a] = -1;

    for (a = 0; a < numPages; a++) {
        hit = placed = 0;

        for (b = 0; b < numFrames; b++) {
            if (mem[b] == refs[a]) {
                tick++;
                stamp[b] = tick;
                hit = placed = 1;
                break;
            }
        }

        if (hit == 0) {
            for (b = 0; b < numFrames; b++) {
                if (mem[b] == -1) {
                    tick++;
                    miss++;
                    mem[b] = refs[a];
                    stamp[b] = tick;
                    placed = 1;
                    break;
                }
            }

            if (placed == 0) {
                victim = getLru(stamp, numFrames);
                tick++;
                miss++;
                mem[victim] = refs[a];
                stamp[victim] = tick;
            }

            printf("\n");
            for (b = 0; b < numFrames; b++)
                printf("%d\t", mem[b]);
        }
    }

    printf("\nTotal page faults = %d\n", miss);
    return 0;
}
