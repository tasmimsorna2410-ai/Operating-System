#include <stdio.h>

int main() {
    int k, num;
    printf("enter the number of process:");
    scanf("%d", &num);

    int id[20], burst[20], prio[20], finish[20], turn[20], wait[20], done[20] = {0};

    for (k = 0; k < num; k++) {
        id[k] = k + 1;
        printf("Enter burst time and priority for process %d:", k + 1);
        scanf("%d %d", &burst[k], &prio[k]);
    }

    int clock = 0, doneCount = 0;
    float avgTurn = 0, avgWait = 0;

    while (doneCount < num) {
        int pick = -1;
        int lowest = 99999;

        for (k = 0; k < num; k++) {
            if (!done[k]) {
                if (prio[k] < lowest) {
                    lowest = prio[k];
                    pick = k;
                } else if (prio[k] == lowest) {
                    if (id[k] < id[pick]) {
                        pick = k;
                    }
                }
            }
        }

        clock += burst[pick];
        finish[pick] = clock;
        turn[pick] = finish[pick];
        wait[pick] = turn[pick] - burst[pick];
        done[pick] = 1;
        doneCount++;
    }

    printf("PID\tBT\tPRIORITY\tCT\tTAT\tWT\n");
    for (k = 0; k < num; k++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", id[k], burst[k], prio[k], finish[k], turn[k], wait[k]);
        avgTurn += turn[k];
        avgWait += wait[k];
    }
    printf("Average TAT = %.2f\n", avgTurn / num);
    printf("Average WT = %.2f\n", avgWait / num);

    return 0;
}
