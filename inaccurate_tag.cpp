#include <iostream>
#include <vector>
#include <map>
int inf = 1e8;
class Heap{
private:
    std::vector<int>a;
    std::vector<int>num;
    std::vector<int>pointer;
    int n = 0;
public:
    void insert(int x,int i){
        if(a.size() <= n + 1) a.resize(2 * n + 2);
        ++n;
        a[n] = x;
        pointer.resize(i + 1);
        if(num.size() <= n) num.resize(2 * n + 1);
        pointer[i] = n;
        num[n] = i;
        siftUp(n);
    }
    int getMinNum(){
        return num[1];
    }
    int getSize() const{
        return n;
    }
    void extractMin(){
        exchange(1, n);
        n--;
        siftDown(1);
    }
    void decreaseKey(int y, int delta){
        a[pointer[y]] -= delta;
        siftUp(pointer[y]);
    }
    void siftUp(int u){
        while(u != 1){
            if(a[u] <= a[u/2]){
                exchange(u, u/2);
                u /= 2;
            }
            else break;
        }
    }
    void siftDown(int u){
        while(2 * u <= n){
            int w = 2 * u;
            if(2 * u + 1 <= n && a[2 * u + 1] < a[2 * u]) w = 2 * u + 1;
            if(a[w] < a[u]){
                exchange(w, u);
                u = w;
            }
            else break;
        }
    }
    void exchange(int p,int q){
        int k = num[p];
        int m = num[q];
        std::swap(num[p], num[q]);
        std::swap(pointer[k], pointer[m]);
        std::swap(a[p], a[q]);
    }
};

int solution(uint64_t s, uint64_t t,
             std::vector<char>& dir, std::vector<int>& parent, std::map<uint64_t, int>& m);
int manhattan_distance(uint64_t v);
std::vector<std::pair<uint64_t, char>> cross(uint64_t v, char dp);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t a;
    uint64_t s = 0;
    uint64_t t = 0;
    for(uint64_t i = 0; i <= 15; ++i) {
        std::cin >> a;
        s += (a << 4 * (15 - i));
        t += (((i + 1) % 16) << 4 * (15 - i));
    }
    std::vector<char>dir;
    std::vector<int>parent;
    std::map<uint64_t, int>m;
    int ans = solution(s, t, dir, parent, m);
    std::cout << ans << '\n';
    if(ans >= 0) {
        std::string path;
        int curr = m[t];
        while(curr > 0) {
            path.insert(0, 1, dir[curr]);
            curr = parent[curr];
        }
        std::cout << path;
    }
    return 0;
}

int solution(uint64_t s, uint64_t t,
             std::vector<char>& dir, std::vector<int>& parent, std::map<uint64_t, int>& m) {
    int ans = -1;
    std::vector<int>g;
    std::vector<uint64_t>accord;
    std::vector<bool>used;
    Heap h;
    g.push_back(0);
    accord.push_back(s);
    m[s] = 0;
    dir.push_back('*');
    parent.push_back(-1);
    used.push_back(false);
    h.insert(2 * manhattan_distance(s), 0);
    while(h.getSize() > 0) {
        int n = h.getMinNum();
        uint64_t v = accord[n];
        if(v == t) {
            ans = g[n];
            break;
        }
        h.extractMin();
        used[n] = true;
        for(std::pair<uint64_t, char> var: cross(v, dir[n])) {
            uint64_t u = var.first;
            char d = var.second;
            if(m.find(u) == m.end()) {
                m[u] = accord.size();
                h.insert(inf + 2 * manhattan_distance(u), accord.size());
                g.push_back(inf);
                accord.push_back(u);
                dir.push_back(d);
                parent.push_back(n);
                used.push_back(false);
            }
            int p = m[u];
            if(used[p]) continue;
            if(g[p] > g[n] + 1) {
                int delta = g[p] - (g[n] + 1);
                h.decreaseKey(p, delta);
                g[p] -= delta;
                dir[p] = d;
                parent[p] = n;
            }
        }
    }
    return ans;
}

int manhattan_distance(uint64_t v) {
    int md = 0;
    for(int i = 0; i <= 15; ++i) {
        int a = (v >> 4 * (15 - i)) % 16;
        if(a > 0) {
            --a;
            md += std::abs((a % 4) - (i % 4));
            md += std::abs((a / 4) - (i / 4));
        }
    }
    return md;
}

std::vector<std::pair<uint64_t, char>> cross(uint64_t v, char dp) {
    std::vector<std::pair<uint64_t, char>>var;
    uint64_t u;
    uint64_t z = 0;
    uint64_t y;
    while(true) {
        if((v >> (4 * (15 - z))) % 16 == 0) break;
        ++z;
    }
    if(dp != 'L' && z % 4 > 0) {
        y = (v >> 4 * (15 - (z - 1))) % 16;
        u = v;
        u -= (y << 4 * (15 - (z - 1)));
        u += (y << 4 * (15 - z));
        var.emplace_back(u, 'R');
    }
    if(dp != 'R' && z % 4 < 3) {
        y = (v >> 4 * (15 - (z + 1))) % 16;
        u = v;
        u -= (y << 4 * (15 - (z + 1)));
        u += (y << 4 * (15 - z));
        var.emplace_back(u, 'L');
    }
    if(dp != 'U' && z / 4 > 0) {
        y = (v >> 4 * (15 - (z - 4))) % 16;
        u = v;
        u -= (y << 4 * (15 - (z - 4)));
        u += (y << 4 * (15 - z));
        var.emplace_back(u, 'D');
    }
    if(dp != 'D' && z / 4 < 3) {
        y = (v >> 4 * (15 - (z + 4))) % 16;
        u = v;
        u -= (y << 4 * (15 - (z + 4)));
        u += (y << 4 * (15 - z));
        var.emplace_back(u, 'U');
    }
    return var;
}
