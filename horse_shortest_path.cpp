#include <iostream>
#include <queue>
int main() {
    char c1, d1, c2, d2;
    std::cin >> c1 >> d1 >> c2 >> d2;
    int a = 8 * (c1 - 97) + d1 - 49;
    int b = 8 * (c2 - 97) + d2 - 49;
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
        if(v / 8 > 1 && v % 8 < 7 && !used[v - 16 + 1]) {
            q.push(v - 16 + 1);
            parent[q.back()] = v;
        }
        if(v / 8 > 1 && v % 8 > 0 && !used[v - 16 - 1]) {
            q.push(v - 16 - 1);
            parent[q.back()] = v;
        }
        if(v / 8 > 0 && v % 8 < 6 && !used[v - 8 + 2]) {
            q.push(v - 8 + 2);
            parent[q.back()] = v;
        }
        if(v / 8 > 0 && v % 8 > 1 && !used[v - 8 - 2]) {
            q.push(v - 8 - 2);
            parent[q.back()] = v;
        }
        if(v / 8 < 7 && v % 8 < 6 && !used[v + 8 + 2]) {
            q.push(v + 8 + 2);
            parent[q.back()] = v;
        }
        if(v / 8 < 7 && v % 8 > 1 && !used[v + 8 - 2]) {
            q.push(v + 8 - 2);
            parent[q.back()] = v;
        }
        if(v / 8 < 6 && v % 8 < 7 && !used[v + 16 + 1]) {
            q.push(v + 16 + 1);
            parent[q.back()] = v;
        }
        if(v / 8 < 6 && v % 8 > 0 && !used[v + 16 - 1]) {
            q.push(v + 16 - 1);
            parent[q.back()] = v;
        }
    }
    std::vector<int>ans;
    while(v != -1) {
        ans.push_back(v);
        v = parent[v];
    }
    for(int i = ans.size() - 1; i >= 0; i--) {
        v = ans[i];
        std::cout << char((v / 8) + 97) << v % 8 + 1 << '\n';
    }
    return 0;
}

