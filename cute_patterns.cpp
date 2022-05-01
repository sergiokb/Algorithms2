#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    long long ans = 0;
    std::cin >> n >> m;
    if(n > m) std::swap(n, m);
    std::vector<std::vector<bool>>cute(1 << n, std::vector<bool>(1 << n, false));
    std::vector<std::vector<int>>dp(2, std::vector<int>(1 << n));
    int same;
    bool ct;
    for(int i = 0; i < 1 << n; i++) {
        for(int j = 0; j < 1 << n; j++) {
            ct = true;
            same = 2;
            for(int k = 0; k < n; k++) {
                if(same == ((i >> k) & 1) && same == ((j >> k) & 1)) ct = false;
                if(((i >> k) & 1) == ((j >> k) & 1)) same = ((i >> k) & 1);
                else same = 2;
            }
            cute[i][j] = ct;
        }
    }
    dp[0].assign(1 << n, 1);
    for(int i = 0; i < m; i++) {
        if(i > 0) dp[i % 2].assign(1 << n, 0);
        for(int j = 0; j < 1 << n; j++) {
            for(int k = 0; k < 1 << n; k++) {
                if(i > 0 && cute[j][k]) dp[i % 2][j] += dp[(i - 1) % 2][k];
            }
            if(i == m - 1) ans += dp[i % 2][j];
        }
    }
    std::cout << ans;
    return 0;
}

