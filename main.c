#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int temps_arrivee;
    int duree_exec;
} Processus;

int main() {
    int n, quantum;

    printf("--- SIMULATEUR D'ORDONNANCEMENT ---\n");
    
    printf("Entrez le nombre de processus : ");
    scanf("%d", &n);

    printf("Entrez le quantum de temps global : ");
    scanf("%d", &quantum);

    Processus p[n];

    printf("\n--- Saisie des processus ---\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcessus P%d :\n", p[i].id);
        printf("  Temps d'arrivee : ");
        scanf("%d", &p[i].temps_arrivee);
        printf("  Duree d'execution : ");
        scanf("%d", &p[i].duree_exec);
    }

    printf("\n--- Recapitulatif des donnees saisies ---\n");
    printf("Quantum global : %d\n", quantum);
    for (int i = 0; i < n; i++) {
        printf("P%d -> Arrivee: %d | Execution: %d\n", p[i].id, p[i].temps_arrivee, p[i].duree_exec);
    }

    return 0;
}
