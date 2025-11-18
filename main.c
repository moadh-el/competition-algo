#include <stdio.h>
#include <stdlib.h>

// Fonction de comparaison pour qsort (Tri Décroissant)
// Retourne une valeur positive si b > a, négative si a > b
int compareDesc(const void *a, const void *b) {
    long long valA = *(const long long *)a;
    long long valB = *(const long long *)b;

    if (valA < valB) return 1;
    if (valA > valB) return -1;
    return 0;
}

int main() {
    // Redirection de l'entrée standard pour lire le fichier input.txt
    // Cela permet d'utiliser scanf comme si on tapait au clavier
    if (freopen("input.txt", "r", stdin) == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir input.txt\n");
        return 1;
    }

    int N;
    // Lecture de N (première ligne)
    if (scanf("%d", &N) != 1) return 0;

    // Allocation dynamique de mémoire pour le tableau (N <= 10^6)
    // Utilisation de long long car les valeurs vont jusqu'à 10^9
    long long *crates = (long long *)malloc(N * sizeof(long long));
    if (crates == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return 1;
    }

    long long totalSum = 0;

    // Lecture des caisses
    for (int i = 0; i < N; i++) {
        scanf("%lld", &crates[i]); // %lld est le format pour long long
        totalSum += crates[i];
    }

    // Tri du tableau en ordre décroissant (les plus grands en premier)
    // Complexité : O(N log N)
    qsort(crates, N, sizeof(long long), compareDesc);

    long long currentSum = 0;
    int count = 0;

    // Algorithme Glouton
    // On détermine combien de caisses (k) il faut prendre
    for (int i = 0; i < N; i++) {
        currentSum += crates[i];
        count++; // On prend cette caisse

        // Condition : somme choisie > somme restante
        // (Somme restante = totalSum - currentSum)
        if (currentSum > (totalSum - currentSum)) {
            break; // On a trouvé le minimum nécessaire
        }
    }

    // Affichage du résultat
    printf("%d\n", count); // Ligne 1 : le nombre k
    
    for (int i = 0; i < count; i++) {
        printf("%lld\n", crates[i]); // Les k valeurs
    }

    // Libération de la mémoire
    free(crates);

    return 0;
}