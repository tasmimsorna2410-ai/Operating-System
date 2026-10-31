#include <stdio.h>

int main() {
    int burst[20], finish[20], wait[20], turn[20], resp[20], begin[20];
    int k, num, used[20] = {0};
    int doneCount = 0, clock = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &num);

    printf("Enter burst time of all the processes:");
    for (k = 0; k < num; k++) {
        scanf("%d", &burst[k]);
    }

    while (doneCount < num) {
        int pick = -1;
        for (k = 0; k < num; k++) {
            if (!used[k]) {
                if (pick == -1 || burst[k] < burst[pick])
                    pick = k;
            }
        }

        begin[pick] = clock;
        finish[pick] = begin[pick] + burst[pick];
        turn[pick] = finish[pick];
        wait[pick] = turn[pick] - burst[pick];
        resp[pick] = begin[pick];

        used[pick] = 1;
        doneCount++;
        clock = finish[pick];
    }

    float sumWait = 0, sumTurn = 0;
    printf("PNo.\tBT\tCT\tTAT\tWT\n");
    for (k = 0; k < num; k++) {
        printf("p%d\t%d\t%d\t%d\t%d\n", k + 1, burst[k], finish[k], turn[k], wait[k]);
        sumWait += wait[k];
        sumTurn += turn[k];
    }

    printf("Avg waiting time = %.2f\n", sumWait / num);
    printf("Avg turn around time = %.2f\n", sumTurn / num);

    return 0;
}
