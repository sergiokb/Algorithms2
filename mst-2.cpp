#include <iostream>
#include <vector>
#include <set>
int get(int v, std::vector<int>& p);
void unite(int u, int v, std::vector<int>& p, std::vector<int>& size);
int mst(int n, int m, std::set<std::pair<int, std::pair<int, int>>>& edges);
int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::set<std::pair<int, std::pair<int, int>>>edges;
    int fr, to, w;
    for(int i = 0; i < m; i++) {
        std::cin >> fr >> to >> w;
        --fr;
        --to;
        edges.insert({w, {fr, to}});
    }
    std::cout << mst(n, m, edges);
    return 0;
}

int mst(int n, int m, std::set<std::pair<int, std::pair<int, int>>>& edges) {
    std::vector<int>p(n, -1);
    std::vector<int>size(n, 1);
    int ans = 0;
    int w;
    for(auto e: edges) {
        int u = e.second.first;
        int v = e.second.second;
        w = e.first;
        u = get(u, p);
        v = get(v, p);
        if(u != v) {
            unite(u, v, p, size);
            ans += w;
        }
    }
    return ans;
}

int get(int v, std::vector<int>& p) {
    if(p[v] == -1) return v;
    return p[v] = get(p[v], p);
}

void unite(int u, int v, std::vector<int>& p, std::vector<int>& size) {
    if(size[u] < size[v]) std::swap(u, v);
    p[v] = u;
    size[u] += size[v];
}
