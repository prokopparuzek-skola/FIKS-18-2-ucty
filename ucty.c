#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Z;
    int A;
    int B;
} ucet_t; // zde jsou uloženy údaje o účtech

void load(ucet_t *co, ucet_t **kam, int N) {
    int i;

    for (i = 0; i < N; i++) {
        kam[i] = co + i;
    }
}

void swap(ucet_t **a , ucet_t **b) {
    ucet_t *s;

    s = *a;
    *a = *b;
    *b = s;
}

void sortZ(ucet_t **ucty, int from, int to) { // seřazení účtůpodle obnosu
    int pivot = ucty[from]->Z;
    int i, gros = from;

    swap(&ucty[from], &ucty[to-1]);
    for (i = from; i < to -1; i++) {
        if (ucty[i]->Z > pivot) {
            swap(&ucty[i], &ucty[gros]);
            gros++;
        }
    }
    swap(&ucty[to-1], &ucty[gros]);
    if (gros != from)
        sortZ(ucty, from, gros);
    if (gros != to -1)
        sortZ(ucty, gros + 1, to);
}

void sortB(ucet_t **ucty, int from, int to) { //seřazení účtů dle ceny za příchozí platbu
    int pivot = ucty[from]->B;
    int i, less = from;

    swap(&ucty[from], &ucty[to-1]);
    for (i = from; i < to - 1; i++) {
        if (ucty[i]->B < pivot) {
            swap(&ucty[i], &ucty[less]);
            less++;
        }
    }
    swap(&ucty[to-1], &ucty[less]);
    if (less != from)
        sortZ(ucty, from, less);
    if (less != to -1)
        sortZ(ucty, less + 1, to);
}

int solve(ucet_t **Zucty, ucet_t ** Bucty, int N, int K) {
    int i, num, index;
    while (K >= 0) {
        for (i = 0, num = Zucty[0]->Z; i < N && Zucty[i]->Z == num; i++) { // prochází účty o stejném obnosu
            sortZ(Zucty, 0, N);
            for (index = 0; index < N && Bucty[index]->Z >= Zucty[i]->Z; index++); // zjistí účet s co nejnižší cenou za příchozí platbu, na který se peníze vejdou
            if ((Zucty[i]->A + Bucty[index]->B) <= K && Zucty[i]->Z > Bucty[index]->Z + 1) {
                Zucty[i]->Z--;
                Bucty[index]->Z++;
                K -= (Zucty[i]->A + Bucty[index]->B);
            }
            else { // vrátí nejvyšší obnos
                sortZ(Zucty, 0, N);
                return Zucty[0]->Z;
            }
        }
    }
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
    sortZ(Zucty, 0, N);
    sortB(Bucty, 0, N);

    back = solve(Zucty, Bucty, N, K);
    printf("%d\n", back);

    free(ucty);
    free(Zucty);
    free(Bucty);
    return 0;
}
