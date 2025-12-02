#include <stdio.h>
#include <string.h>

#define MAXN 105
#define MAXK 105

int dp[MAXN][MAXN][MAXK];
int grid[MAXN][MAXN];

int main(void) {
 int n, m, k;
 FILE *f = fopen("input.txt", "r");
 // Lecture de n, m, k
 if (fscanf(f, "%d %d %d", &n, &m, &k) != 3) {
 fclose(f);
 return 1;
 }

 // Lecture de la grille n x m
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 fscanf(f, "%d", &grid[i][j]);
 }
 }
 fclose(f);

 memset(dp, 0, sizeof(dp));

 // Case de départ
 if (grid[0][0] <= k)
 dp[0][0][grid[0][0]] = 1;

 // DP : on propage vers le bas et vers la droite
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 for (int c = 0; c <= k; c++) {
 if (dp[i][j][c] == 0) continue;

 // Aller en bas
 if (i + 1 < n && c + grid[i+1][j] <= k)
 dp[i+1][j][c + grid[i+1][j]] += dp[i][j][c];

 // Aller à droite
 if (j + 1 < m && c + grid[i][j+1] <= k)
 dp[i][j+1][c + grid[i][j+1]] += dp[i][j][c];
 }
 }
 }

 // Résultat : chemins qui arrivent en bas‑droite avec exactement k Poké Balls
 printf("%d\n", dp[n-1][m-1][k]);
 return 0;
}