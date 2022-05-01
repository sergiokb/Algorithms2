#include <iostream>
#include <vector>
bool bit(long long mask, int pos);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    long long ans = 0;
    long long mod = 1e9 + 7;
    std::cin >> n >> m;
    std::vector<long long>noh(m, 0);
    std::vector<long long>iss(m, 0);
    char c;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cin >> c;
            if(c == '+') {
                noh[j] += (1 << i);
                iss[j] += (1 << i);
            }
            if(c == '-') {
                iss[j] += (1 << i);
            }
        }
    }
    std::vector<std::vector<bool>>cute(1 << n, std::vector<bool>(1 << n, false));
    std::vector<std::vector<int>>dp(2, std::vector<int>(1 << n));
    int x, y;
    bool bx, by;
    for(int i = 0; i < m; i++) {
        dp[i % 2].assign(1 << n, 0);
        for(int j = 0; j < 1 << n; j++) {
            if(((noh[i] ^ j) & iss[i]) == 0) {
                if(i == 0) {
                    ++dp[i % 2][j];
                }
                else {
                    x = 1;
                    y = 0;
                    bx = true;
                    by = true;
                    for(int l = 1; l < n; l++) {
                        if(bit(j, l) + bit(j, l - 1) + bit(y, l - 1) == 1) y += (1 << l);
                        if(bit(j, l) + bit(j,l - 1) + bit(y, l - 1) + bit(y, l) != 2) by = false;
                        if(bit(j, l) + bit(j, l - 1) + bit(x, l - 1) == 1) x += (1 << l);
                        if(bit(j, l) + bit(j, l - 1) + bit(x, l - 1) + bit(x, l) != 2) bx = false;
                    }
                    if(i > 0 && bx && ((noh[i - 1] ^ x) & iss[i - 1]) == 0) {
                        dp[i % 2][j] += dp[(i - 1) % 2][x];
                        dp[i % 2][j] %= mod;
                    }
                    if(i > 0 && by && ((noh[i - 1] ^ y) & iss[i - 1]) == 0) {
                        dp[i % 2][j] += dp[(i - 1) % 2][y];
                        dp[i % 2][j] %= mod;
                    }
                }
            }
            if(i == m - 1) {
                ans += dp[i % 2][j];
                ans %= mod;
            }
        }
    }
    std::cout << ans;
    return 0;
}
bool bit(long long mask, int pos) {
    return (mask >> pos) & 1;
}

