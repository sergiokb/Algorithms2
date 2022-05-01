#include <iostream>
#include <vector>

std::vector<int>f(int& n, std::vector<int>& b);

int main() {
    int n;
    std::vector<int>a;
    std::cin >> n;
    int t;
    for(int i = 0; i < n; i++) {
        std::cin >> t;
        a.push_back(t);
    }
    std::vector<int>b;
    for(int i = n - 1; i >= 0; i--) {
        b.push_back(a[i]);
    }
    std::vector<int>nv = f(n, b);
    std::cout << nv.size() << std::endl;
    for(int i = 0; i < nv.size(); i++) {
        std::cout << n - nv[i] << ' ';
    }
    return 0;
}

std::vector<int>f(int& n, std::vector<int>& b) {
    std::vector<int>dp;   //with keys
    std::vector<int>dps;  //with values
    std::vector<int>rm;   //remember previous
    rm.assign(n, -1);
    int up;
    for(int i = 0; i < n; i++) {
        up = std::upper_bound(dps.begin(), dps.end(), b[i]) - dps.begin();
        if(up >= dp.size()) {
            dp.push_back(i);
            dps.push_back(b[i]);
        }
        else {
            dp[up] = i;
            dps[up] = b[i];
        }
        if(up > 0) rm[i] = dp[up - 1];
    }
    std::vector<int>nv;
    int k = dp[dp.size() - 1];
    while(k >= 0) {
        nv.push_back(k);
        k = rm[k];
    }
    return nv;
}

