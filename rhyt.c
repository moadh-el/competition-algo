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
