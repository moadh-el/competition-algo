#include <stdio.h>
#define MOD 1000000007

int rhythm_patterns(int n) {
    if (n == 0 || n == 1)
        return 1;
    int dp[n+1];
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    }
    return dp[n];
}

int main() {
    int q[] = {6,0,1,2,3,4,10}; 
    for (int i = 1; i <= q[0]; i++) {
        printf("%d\n", rhythm_patterns(q[i]));
    }
    return 0;
}





///////////////////////////
#include <stdio.h>
#define MOD 1000000007

void matrix_mult(long long a[2][2], long long b[2][2]) {
    long long res[2][2];
    res[0][0] = (a[0][0]*b[0][0] + a[0][1]*b[1][0]) % MOD;
    res[0][1] = (a[0][0]*b[0][1] + a[0][1]*b[1][1]) % MOD;
    res[1][0] = (a[1][0]*b[0][0] + a[1][1]*b[1][0]) % MOD;
    res[1][1] = (a[1][0]*b[0][1] + a[1][1]*b[1][1]) % MOD;
    a[0][0] = res[0][0];
    a[0][1] = res[0][1];
    a[1][0] = res[1][0];
    a[1][1] = res[1][1];
}

void matrix_pow(long long mat[2][2], int n) {
    long long res[2][2] = {{1, 0},{0, 1}}; // Identity matrix
    while(n > 0) {
        if(n % 2 == 1) {
            matrix_mult(res, mat);
        }
        matrix_mult(mat, mat);
        n /= 2;
    }
    mat[0][0] = res[0][0];
    mat[0][1] = res[0][1];
    mat[1][0] = res[1][0];
    mat[1][1] = res[1][1];
}

int rhythm_patterns(int n) {
    if(n == 0 || n == 1) return 1;
    long long mat[2][2] = {{1,1},{1,0}};
    matrix_pow(mat, n);
    return mat[0][0];
}

int main() {
    int q[] = {6,0,1,2,3,4,10};
    for (int i = 1; i <= q[0]; i++) {
        printf("%d\n", rhythm_patterns(q[i]));
    }
    return 0;
}
