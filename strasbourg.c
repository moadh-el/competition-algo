    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // LIS + Lower Bound
    typedef struct SPair {
        int left;
        int right;
    } Pair;

    int compare(const void *a, const void *b) {
        const Pair *x = a;
        const Pair *y = b;
        if (x->left != y->left) return x->left - y->left;
        return x->right - y->right;
    }

    int lower_bound(int *arr, int size, int key) {
        int l = 0, r = size;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] < key) l = m + 1;
            else r = m;
        }
        return l;
    }


    int main(void) {

        FILE *f = fopen("./input.txt", "r");
        if (!f) {
            perror("Erreur d'ouverture du fichier");
            return 1;
        }

        int n; fscanf(f, "%i", &n);
        Pair* pairs = malloc(n * sizeof(Pair));

        for (int i = 0; i < n; i++) {
            if (fscanf(f, "%i %i", &pairs[i].left, &pairs[i].right) != 2) {
                fprintf(stderr, "Erreur de lecture à la ligne %d\n", i + 1);
                fclose(f);
                return EXIT_FAILURE;
            }
        }
        fclose(f);
    
    qsort(pairs, n, sizeof(Pair), compare);
    
    int* tail = malloc(n * sizeof(int));
    int* prev = malloc(n * sizeof(int));
    int* pos = malloc(n * sizeof(int));

    int len = 0;

   for (int i = 0; i < n; i++) {
        int r = pairs[i].right;
        int idx = lower_bound(tail, len, r);
        tail[idx] = r;
        pos[idx] = i;
        prev[i] = idx > 0 ? pos[idx - 1] : -1;
        if (idx + 1 > len) len = idx + 1;
    }
    
    Pair* sol = malloc(len * sizeof(Pair));
    int idx = len - 1;
    int k = pos[len - 1];
    while (k != -1) {
        sol[idx] = pairs[k];
        idx--;
        k = prev[k];
    }

    printf("%i\n", len);
    for (int i = 0; i < len; i++) {
        printf("%i %i\n", sol[i].left, sol[i].right);
    }
    
    free(pairs); free(tail); free(prev); free(pos); free(sol);
    
    return 0;

    }
