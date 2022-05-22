#include <iostream>
#include <queue>
void shortest_path(int a, int b, std::vector<int>& ans);
int main() {
    char c1, d1, c2, d2;
    std::cin >> c1 >> d1 >> c2 >> d2;
    int a = 8 * (c1 - 97) + d1 - 49;
    int b = 8 * (c2 - 97) + d2 - 49;
    std::vector<int>ans;
    shortest_path(a, b, ans);
    int v;
    for(int i = int(ans.size()) - 1; i >= 0; i--) {
        v = ans[i];
        std::cout << char((v / 8) + 97) << v % 8 + 1 << '\n';
    }
    return 0;
}

void shortest_path(int a, int b, std::vector<int>& ans) {
    std::queue<int>q;
    std::vector<bool>used(64, false);
    std::vector<int>parent(64, -1);
    int v;
    q.push(a);
    while(true) {
        v = q.front();
        q.pop();
        if(used[v]) continue;
        used[v] = true;
        if(v == b) break;
        for(int i = -2; i <= 2; ++i) {
            for(int j = -2; j <= 2; ++j) {
                if((i + j) % 2 == 0 || i * j == 0) continue;
                if((i < 0 ? v / 8 > -i - 1 : v / 8 < 8 - i) && (j > 0 ? v % 8 < 8 - j : v % 8 > -j - 1)
                    && !used[v + 8 * i + j]) {
                    q.push(v + 8 * i + j);
                    parent[q.back()] = v;
                }
            }
        }
    }
    while(v != -1) {
        ans.push_back(v);
        v = parent[v];
    }
}
