#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>>dp(n + 1);
    for(int i = 0; i <= n; i++) dp[i].assign(n + 1, 0);
    // i - сумма
    // j - наибольшее число
    int k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(i == j) dp[i][j] = 1;
            else {
                k = j / 2;
                while(k > 0) {
                    dp[i][j] += dp[i - j][k];
                    k--;
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i <= n; i++) ans += dp[n][i];
    std::cout << ans << std::endl;
    return 0;
}

