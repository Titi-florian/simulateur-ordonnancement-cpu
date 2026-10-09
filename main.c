#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int temps_arrivee;
    int duree_exec;
    int temps_fin;
    int temps_rotation;
} Processus;

// Fonction pour trier les processus par ordre d'arrivée croissant (pour le FIFO)
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
    // On fait une copie locale ou on trie pour le FIFO
    Processus copie[n];
    for(int i=0; i<n; i++) copie[i] = p[i];

    trierParArrivee(copie, n);

    int temps_actuel = 0;

    printf("\n--- EXECUTION DE L'ALGORITHME FIFO ---\n");
    for (int i = 0; i < n; i++) {
        if (temps_actuel < copie[i].temps_arrivee) {
            temps_actuel = copie[i].temps_arrivee;
        }

        temps_actuel += copie[i].duree_exec;
        copie[i].temps_fin = temps_actuel;
        copie[i].temps_rotation = copie[i].temps_fin - copie[i].temps_arrivee;

        printf("Processus P%d -> Arrivee: %d | Execution: %d | Fin: %d | Rotation: %d\n",
               copie[i].id, copie[i].temps_arrivee, copie[i].duree_exec, copie[i].temps_fin, copie[i].temps_rotation);
    }
}

// Implémentation de l'algorithme SGF (Non préemptif)
void executerSGF(Processus p[], int n) {
    int temps_actuel = 0;
    int completes = 0;
    int est_termine[n];
    for (int i = 0; i < n; i++) est_termine[i] = 0;

    printf("\n--- EXECUTION DE L'ALGORITHME SGF ---\n");
    while (completes < n) {
        int idx_court = -1;
        int min_duree = 99999;

        // Trouver le processus arrivé ayant la plus petite durée d'exécution
        for (int i = 0; i < n; i++) {
            if (!est_termine[i] && p[i].temps_arrivee <= temps_actuel) {
                if (p[i].duree_exec < min_duree) {
                    min_duree = p[i].duree_exec;
                    idx_court = i;
                }
            }
        }

        // Si aucun processus n'est encore arrivé, on avance le temps d'une unité
        if (idx_court == -1) {
            temps_actuel++;
        } else {
            temps_actuel += p[idx_court].duree_exec;
            p[idx_court].temps_fin = temps_actuel;
            p[idx_court].temps_rotation = p[idx_court].temps_fin - p[idx_court].temps_arrivee;
            est_termine[idx_court] = 1;
            completes++;

            printf("Processus P%d -> Arrivee: %d | Execution: %d | Fin: %d | Rotation: %d\n",
                   p[idx_court].id, p[idx_court].temps_arrivee, p[idx_court].duree_exec, p[idx_court].temps_fin, p[idx_court].temps_rotation);
        }
    }
}

// Implémentation de l'algorithme SRP (Shortest Remaining Time First / Préemptif)
void executerSRP(Processus p[], int n) {
    int temps_restant[n];
    for (int i = 0; i < n; i++) {
        temps_restant[i] = p[i].duree_exec;
    }

    int temps_actuel = 0;
    int completes = 0;

    printf("\n--- EXECUTION DE L'ALGORITHME SRP (Preemptif) ---\n");
    while (completes < n) {
        int idx_court = -1;
        int min_restant = 99999;

        // Trouver le processus arrivé non terminé avec le plus petit temps restant
        for (int i = 0; i < n; i++) {
            if (temps_restant[i] > 0 && p[i].temps_arrivee <= temps_actuel) {
                if (temps_restant[i] < min_restant) {
                    min_restant = temps_restant[i];
                    idx_court = i;
                }
            }
        }

        // Si aucun processus n'est disponible, on avance le temps
        if (idx_court == -1) {
            temps_actuel++;
        } else {
            // On exécute d'une unité de temps
            temps_restant[idx_court]--;
            temps_actuel++;

            // Si le processus vient de se terminer
            if (temps_restant[idx_court] == 0) {
                completes++;
                p[idx_court].temps_fin = temps_actuel;
                p[idx_court].temps_rotation = p[idx_court].temps_fin - p[idx_court].temps_arrivee;

                printf("Processus P%d -> Arrivee: %d | Execution initiale: %d | Fin: %d | Rotation: %d\n",
                       p[idx_court].id, p[idx_court].temps_arrivee, p[idx_court].duree_exec, p[idx_court].temps_fin, p[idx_court].temps_rotation);
            }
        }
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

    // Exécution des algorithmes
    executerFIFO(p, n);
    executerSGF(p, n);
    executerSRP(p, n);

    return 0;
}
