#include <iostream>
#include <vector>

bool bit(long long mask, int pos);
long long variants(int n, int m, std::vector<long long>& noh, std::vector<long long>& iss);

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<long long>noh(m, 0); // not in hunger
    std::vector<long long>iss(m, 0); // defined
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
    std::cout << variants(n, m, noh, iss);
    return 0;
}

bool bit(long long mask, int pos) {
    return (mask >> pos) & 1;
}

long long variants(int n, int m, std::vector<long long>& noh, std::vector<long long>& iss) {
    std::vector<std::vector<int>>dp(2, std::vector<int>(1 << n));
    long long mod = 1e9 + 7;
    long long ans = 0;
    int x, y;
    bool bx, by;
    for(int i = 0; i < m; i++) {
        dp[i % 2].assign(1 << n, 0);
        for(int j = 0; j < 1 << n; j++) {
            if(((noh[i] ^ j) & iss[i]) == 0) {
                if(i == 0) {
                    ++dp[i % 2][j]; // variants for j mask in i-row when it's last 
                }
                else {
                    // the whole can be uniquely set by 0 or 1 in the first cell
                    x = 1;
                    y = 0;
                    bx = true; // if with 1 there are no collisions
                    by = true; // if with 0 there are no collisions
                    for(int l = 1; l < n; l++) {
                        if(bit(j, l) + bit(j, l - 1) + bit(y, l - 1) == 1) y += (1 << l); // must
                        if(bit(j, l) + bit(j,l - 1) + bit(y, l - 1) + bit(y, l) != 2) by = false; // collision
                        if(bit(j, l) + bit(j, l - 1) + bit(x, l - 1) == 1) x += (1 << l); // must
                        if(bit(j, l) + bit(j, l - 1) + bit(x, l - 1) + bit(x, l) != 2) bx = false; // collision
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
    return ans;
}
