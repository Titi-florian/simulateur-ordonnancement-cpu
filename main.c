#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int temps_arrivee;
    int duree_exec;
    int temps_fin;
    int temps_rotation;
} Processus;

// Fonction pour trier les processus par ordre d'arrivée croissant
void trierParArrivee(Processus p[], int n) {
    Processus temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].temps_arrivee > p[j + 1].temps_arrivee) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Implémentation de l'algorithme FIFO
void executerFIFO(Processus p[], int n) {
    trierParArrivee(p, n);

    int temps_actuel = 0;

    printf("\n--- EXECUTION DE L'ALGORITHME FIFO ---\n");
    for (int i = 0; i < n; i++) {
        // Si le CPU est inactif jusqu'à l'arrivée du processus
        if (temps_actuel < p[i].temps_arrivee) {
            temps_actuel = p[i].temps_arrivee;
        }

        temps_actuel += p[i].duree_exec;
        p[i].temps_fin = temps_actuel;
        p[i].temps_rotation = p[i].temps_fin - p[i].temps_arrivee;

        printf("Processus P%d -> Temps d'arrivee: %d | Execution: %d | Temps de fin: %d | Temps de rotation: %d\n",
               p[i].id, p[i].temps_arrivee, p[i].duree_exec, p[i].temps_fin, p[i].temps_rotation);
    }
}

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

    // Appel de l'algorithme FIFO
    executerFIFO(p, n);

    return 0;
}
