#include <stdio.h>
#include <stdlib.h>

/* Problème : Hermione's Fake Wand Permit
   Lecture depuis : input.txt
*/

int main() {
    int D, S;
    FILE *fp;

    // 1. Ouverture du fichier en mode lecture ("r" = read)
    fp = fopen("input.txt", "r");

    // Vérification si le fichier existe
    if (fp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier input.txt\n");
        return 1;
    }

    // 2. Lecture de D et S depuis le fichier
    if (fscanf(fp, "%d %d", &D, &S) != 2) {
        printf("Erreur : Format du fichier incorrect\n");
        fclose(fp);
        return 1;
    }

    // Fermeture du fichier car nous avons fini de lire
    fclose(fp);

    // 3. Vérification des contraintes
    // S doit être au moins 1 (le premier chiffre ne peut pas être 0)
    // S ne peut pas dépasser 9 * D (car le chiffre max est 9)
    if (S == 0 || S > 9 * D) {
        printf("-1\n");
        return 0;
    }

    // 4. Allocation dynamique pour le résultat
    // Taille D + 1 pour inclure le caractère de fin de chaîne '\0'
    char *result = (char*)malloc((D + 1) * sizeof(char));
    if (result == NULL) {
        printf("Erreur d'allocation memoire\n");
        return 1;
    }

    // 5. Algorithme Glouton Inversé (De la droite vers la gauche)
    // On remplit les dernières positions avec le maximum possible (9)
    // pour laisser les petits chiffres au début.
    for (int i = D - 1; i > 0; i--) {
        // On peut mettre 9, SAUF si cela laisse la somme restante à 0.
        // On doit garder au moins 1 pour le tout premier chiffre (index 0).
        int pick = 9;
        if (S - 1 < 9) {
            pick = S - 1;
        }

        result[i] = pick + '0'; // Conversion int -> char
        S -= pick;
    }

    // 6. Le reste de la somme va dans le premier chiffre
    result[0] = S + '0';

    // Terminer la chaîne
    result[D] = '\0';

    // 7. Affichage du résultat (dans la console)
    printf("%s\n", result);

    // Si vous voulez écrire le résultat dans un fichier output.txt, décommentez ceci :
    /*
    FILE *fout = fopen("output.txt", "w");
    fprintf(fout, "%s\n", result);
    fclose(fout);
    */

    // Libération de la mémoire
    free(result);

    return 0;
}
