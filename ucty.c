#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Z;
    int A;
    int B;
} ucet_t;

void load(ucet_t *co, ucet_t **kam, int N) {
    int i;

    for (i = 0; i < N; i++) {
        kam[i] = co + i;
    }
}

int main() {
    int N, K;
    ucet_t *ucty;
    ucet_t **Zucty; // účty seřazené dle částky
    ucet_t **Bucty; // účty seřazené dle částky za příchozí platbu

    scanf("%d%d", &N, &K);
    ucty = malloc(N * sizeof(ucet_t));
    Zucty = malloc(N * sizeof(ucet_t*));
    Bucty = malloc(N * sizeof(ucet_t*));

    free(ucty);
    free(Zucty);
    free(Bucty);
    return 0;
}
