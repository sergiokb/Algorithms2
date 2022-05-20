#include <iostream>
long long inDegree(long long m, long long d, long long mod);
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
        m = inDegree(m, a, mod);
    }
    // formula (2^P + 2*(-1)^P)/(3*2^P) where P - permutation
    m *= ((mod + 1) / 2); // divide by 2
    m %= mod;
    p = m + t; // t = (-1)^P
    p = (((mod + 1) / 3) * p) % mod; // divide by 3
    q = m;
    std::cout << p << '/' << q;
    return 0;
}

long long inDegree(long long m, long long d, long long mod){
    if(d == 1) return m % mod;
    if(d % 2 == 1) return (m * inDegree(m, d - 1, mod)) % mod;
    m = inDegree(m, d / 2, mod) % mod;
    m = (m * m) % mod;
    return m % mod;
}
