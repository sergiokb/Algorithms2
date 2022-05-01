#include <iostream>
long long g(long long m, long long d, long long mod);
int main() {
    std::ios_base::sync_with_stdio(false);
    long long k, a;
    long long mod = 1e9 + 7;
    long long p, q;
    std::cin >> k;
    long long m = 2;
    int t = -1;
    for(int i = 0; i < k; i++) {
        std::cin >> a;
        if(a % 2 == 0) t = 1;
        m = g(m, a, mod);
    }
    m *= ((mod + 1) / 2);
    m %= mod;
    p = m + t;
    p = (((mod + 1) / 3) * p) % mod;
    q = m;
    std::cout << p << '/' << q;
    return 0;
}

long long g(long long m, long long d, long long mod){
    if(d == 1) return m % mod;
    if(d % 2 == 1) return (m * g(m, d - 1, mod)) % mod;
    m = g(m, d / 2, mod) % mod;
    m = (m * m) % mod;
    return m % mod;
}

