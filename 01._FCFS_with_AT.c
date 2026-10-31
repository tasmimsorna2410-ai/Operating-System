#include <stdio.h>

int main() {
    int arrival[15], burst[15], finish[15], wait[15], turn[15], resp[15], begin[15];
    int k, num;

    printf("Enter the number of process:");
    scanf("%d", &num);

    printf("Enter arrival time of all the processes:");
    for (k = 0; k < num; k++)
        scanf("%d", &arrival[k]);

    printf("Enter burst time of all the processes:");
    for (k = 0; k < num; k++)
        scanf("%d", &burst[k]);

    begin[0] = arrival[0];
    finish[0] = begin[0] + burst[0];

    for (k = 1; k < num; k++) {
        if (arrival[k] > finish[k - 1])
            begin[k] = arrival[k];
        else
            begin[k] = finish[k - 1];
        finish[k] = begin[k] + burst[k];
    }

    float sumWait = 0, sumTurn = 0;
    for (k = 0; k < num; k++) {
        turn[k] = finish[k] - arrival[k];
        wait[k] = turn[k] - burst[k];

        sumWait += wait[k];
        sumTurn += turn[k];
    }

    printf("PNo.\tAT\tBT\tCT\tTAT\tWT\n");
    for (k = 0; k < num; k++)
        printf("p%d\t%d\t%d\t%d\t%d\t%d\n", k + 1, arrival[k], burst[k], finish[k], turn[k], wait[k]);

    printf("Avg waiting time = %.2f\n", sumWait / num);
    printf("Avg turn around time = %.2f\n", sumTurn / num);

    return 0;
}
