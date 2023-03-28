// За програмски јазик да се употреби C.
//
// Да се напише програма во која од стандарден влез се внесува бројот N (бројот на трансакции), а потоа N трансакциски сметки и
// како резултат ги печати идентификацискиот број и вкупната сума (со провизија) на сите трансакции платени со кредитна картичка.
// Во случај да нема трансакција платена со кредитна картичка да се испечати "No credit card transaction".

// Во структурата Трансакција (Transaction) треба да се чуваат следните информации:
// -Идентификациски број (int)
// -Платена сума (int)
// -Провизија (int)

#include <stdio.h>

typedef struct Transaction {
    int id;
    int sum;
    int provision;
    int card;
} Transaction;

int main() {
    Transaction transactions[100];
    int n, count = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &transactions[i].id, &transactions[i].sum, &transactions[i].provision, &transactions[i].card);

        if (transactions[i].card) {
            count++;
            printf("%d %d\n", transactions[i].id, transactions[i].sum + transactions[i].provision);
        }
    }

    if (!count) printf("No credit card transaction");
}