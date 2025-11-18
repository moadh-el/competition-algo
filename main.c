#include <stdio.h>
#include <stdlib.h>
// (Les autres includes et fonctions parse_int/readline sont masqués ici mais sont supposés exister dans votre environnement)

// --- A AJOUTER AVANT LE MAIN ---

// Fonction de comparaison pour le tri décroissant (qsort)
int compare_desc(const void *a, const void *b) {
    long long valA = *(const long long *)a;
    long long valB = *(const long long *)b;
    if (valA < valB) return 1;
    if (valA > valB) return -1;
    return 0;
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    // --- VOTRE CODE ICI (Allocation) ---
    // On alloue un tableau pour stocker toutes les caisses
    long long *crates = malloc(n * sizeof(long long));
    long long total_sum = 0;

    for (int n_itr = 0; n_itr < n; n_itr++) {
        int x = parse_int(ltrim(rtrim(readline())));

        // --- VOTRE CODE ICI (Lecture) ---
        crates[n_itr] = x; // On stocke la valeur
        total_sum += x;    // On l'ajoute au total
    }

    // --- VOTRE CODE ICI (Logique Gloutonne) ---

    // 1. Trier le tableau en ordre décroissant
    qsort(crates, n, sizeof(long long), compare_desc);

    long long current_sum = 0;
    int k = 0;

    // 2. Sélectionner les caisses jusqu'à dépasser la moitié du total
    for (int i = 0; i < n; i++) {
        current_sum += crates[i];
        k++; // On compte cette caisse
        
        // Si la somme actuelle est > au reste (total - actuel)
        if (current_sum > total_sum - current_sum) {
            break; 
        }
    }

    // 3. Afficher le résultat
    printf("%d\n", k); // Nombre de caisses
    for(int i = 0; i < k; i++) {
        printf("%lld\n", crates[i]); // Valeur de chaque caisse
    }

    // Nettoyage mémoire
    free(crates);

    return 0;
}
