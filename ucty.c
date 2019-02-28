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

int cmpZ (const void *ucetA, const void *ucetB) {
    ucet_t *a = (ucet_t*)&ucetA;
    ucet_t *b = (ucet_t*)&ucetB;
    return b->Z - a->Z;
}

int cmpB (const void *ucetA, const void *ucetB) {
    ucet_t *a = (ucet_t*)&ucetA;
    ucet_t *b = (ucet_t*)&ucetB;
    return a->Z - b->Z;
}

int solve(ucet_t **Zucty, ucet_t ** Bucty, int N, int K) {
    int i, num, index;
    while (K >= 0) {
        for (i = 0, num = Zucty[0]->Z; i < N && Zucty[i]->Z == num; i++) {
            for (index = 0; index < N && Bucty[index]->Z >= Zucty[i]->Z; index++);
            index--;
            if ((Zucty[i]->A + Bucty[index]->B) <= K && Zucty[i]->Z > Bucty[index]->Z) {
                Zucty[i]->Z--;
                Bucty[index]->Z++;
                K -= (Zucty[i]->A + Bucty[index]->B);
            }
            else {
                qsort(Zucty, N, sizeof(ucet_t*), cmpZ);
                return Zucty[0]->Z;
            }
        }
    }
    return Zucty[0]->Z;
}

int main() {
    int N, K;
    int back;
    int i;
    ucet_t *ucty;
    ucet_t **Zucty; // účty seřazené dle částky, od nejvyšší
    ucet_t **Bucty; // účty seřazené dle částky za příchozí platbu od nejnižšší

    scanf("%d%d", &N, &K);
    ucty = malloc(N * sizeof(ucet_t));
    Zucty = malloc(N * sizeof(ucet_t*));
    Bucty = malloc(N * sizeof(ucet_t*));

    for (i = 0; i < N; i++) {
        scanf("%d", &ucty[i].Z);
    }
    for (i = 0; i < N; i++) {
        scanf("%d", &ucty[i].A);
    }
    for (i = 0; i < N; i++) {
        scanf("%d", &ucty[i].B);
    }

    load(ucty, Zucty, N);
    load(ucty, Bucty, N);
    qsort(Zucty, N, sizeof(ucet_t*), cmpZ);
    qsort(Bucty, N, sizeof(ucet_t*), cmpB);

    back = solve(Zucty, Bucty, N, K);
    printf("%d\n", back);

    free(ucty);
    free(Zucty);
    free(Bucty);
    return 0;
}
