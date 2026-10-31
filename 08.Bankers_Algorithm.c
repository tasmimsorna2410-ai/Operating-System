#include <stdio.h>

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int held[p][r], limit[p][r], required[p][r], free_res[r];
    int complete[p], order[p];

    printf("Enter Allocation Matrix:\n");
    for (int a = 0; a < p; a++)
        for (int b = 0; b < r; b++)
            scanf("%d", &held[a][b]);

    printf("Enter Maximum Matrix:\n");
    for (int a = 0; a < p; a++)
        for (int b = 0; b < r; b++)
            scanf("%d", &limit[a][b]);

    printf("Enter Available Resources:\n");
    for (int b = 0; b < r; b++)
        scanf("%d", &free_res[b]);

    for (int a = 0; a < p; a++)
        for (int b = 0; b < r; b++)
            required[a][b] = limit[a][b] - held[a][b];

    for (int a = 0; a < p; a++)
        complete[a] = 0;

    int cnt = 0;
    while (cnt < p) {
        int progress = 0;
        for (int a = 0; a < p; a++) {
            if (!complete[a]) {
                int b;
                for (b = 0; b < r; b++)
                    if (required[a][b] > free_res[b])
                        break;

                if (b == r) {
                    for (int c = 0; c < r; c++)
                        free_res[c] += held[a][c];
                    order[cnt++] = a;
                    complete[a] = 1;
                    progress = 1;
                }
            }
        }
        if (!progress) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int a = 0; a < p; a++)
        printf("P%d ", order[a]);
    printf("\n");

    return 0;
}
