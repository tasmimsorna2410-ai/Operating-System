#include <stdio.h>

int main() {
    int num, slice;
    printf("Enter number of processes: ");
    scanf("%d", &num);

    int id[num], burst[num], left[num], finish[num], turn[num], wait[num], k;

    printf("Enter burst times for all processes:");
    for (k = 0; k < num; k++) {
        id[k] = k + 1;
        scanf("%d", &burst[k]);
        left[k] = burst[k];
    }

    printf("Enter time quantum: ");
    scanf("%d", &slice);

    int clock = 0, doneCount = 0;
    float sumWait = 0, sumTurn = 0;

    while (doneCount < num) {
        for (int k = 0; k < num; k++) {
            if (left[k] > 0) {
                if (left[k] > slice) {
                    left[k] -= slice;
                    clock += slice;
                } else {
                    clock += left[k];
                    left[k] = 0;
                    finish[k] = clock;
                    turn[k] = finish[k];
                    wait[k] = turn[k] - burst[k];
                    sumWait += wait[k];
                    sumTurn += turn[k];
                    doneCount++;
                }
            }
        }
    }

    printf("\nPID\tBT\tCT\tTAT\tWT\n");
    for (int k = 0; k < num; k++)
        printf("P%d\t%d\t%d\t%d\t%d\n",
               id[k], burst[k], finish[k], turn[k], wait[k]);

    printf("\nAverage TAT = %.2f\n", sumTurn / num);
    printf("Average WT = %.2f\n", sumWait / num);

    return 0;
}
