#include <stdio.h>

int main() {
    int arrival[15], burst[15], finish[15], wait[15], turn[15], resp[15], begin[15];
    int k, num;

    printf("Enter the number of process:");
    scanf("%d", &num);

    printf("Enter burst time of all the processes:");
    for (k = 0; k < num; k++)
        scanf("%d", &burst[k]);

    begin[0] = 0;
    finish[0] = begin[0] + burst[0];

    for (k = 1; k < num; k++) {
        begin[k] = finish[k - 1];
        finish[k] = begin[k] + burst[k];
    }

    float sumWait = 0, sumTurn = 0, sumResp = 0;
    for (k = 0; k < num; k++) {
        turn[k] = finish[k];
        wait[k] = turn[k] - burst[k];
        resp[k] = begin[k];

        sumWait += wait[k];
        sumTurn += turn[k];
        sumResp += resp[k];
    }

    printf("PNo.\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (k = 0; k < num; k++)
        printf("p[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n", k + 1, burst[k], begin[k], finish[k], turn[k], wait[k], resp[k]);

    printf("Avg waiting time = %.2f\n", sumWait / num);
    printf("Avg turn around time = %.2f\n", sumTurn / num);
    printf("Avg response time = %.2f\n", sumResp / num);

    return 0;
}
