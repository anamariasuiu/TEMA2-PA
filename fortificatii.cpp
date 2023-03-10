#include <bits/stdc++.h>
using namespace std;

#define NMAX 50005

struct Edge {
    int node;
    int neigh;
    int w;

    Edge() { }
    Edge(int node, int neigh, int w)
        : node(node)
        , neigh(neigh)
        , w(w) { }
};
struct DijkstraResult {
    int node;
    int d;
    int p;

    DijkstraResult(int _node, int _d, int _p)
        : node(_node)
        , d(_d)
        , p(_p) { }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n, m, k, nr;
    vector<Edge> edges;
    vector<int> enemies;
    vector<pair<int, int>> adj[NMAX];
    vector<DijkstraResult> distances;

    void read_input() {
        ifstream fin("fortificatii.in");
        fin >> n >> m >> k;
        fin >> nr;
        for (int i = 0, x; i < nr; i++) {
            fin >> x;
            enemies.push_back(x);
        }
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        fin.close();
    }
    void get_result() {
        int source = 1;
        vector<int> d(n + 1, INT_MAX);
        vector<int> p(n + 1);
        multiset<pair<int, int>> pq;

        d[source] = 0;
        pq.insert(make_pair(d[source], source));

        while (!pq.empty()) {
            auto top = pq.begin();
            auto x = top->second;
            pq.erase(top);
            for (const auto& it : adj[x]) {
                int y = it.first;
                int w = it.second;
                // verificam daca se imbunatateste distanta
                if (d[y] > d[x] + w) {
                    // Scoatem vechea pereche din set.
                    pq.erase({d[y], y});
                    // Actualizam distanta si inseram din nou in set.
                    d[y] = d[x] + w;
                    p[y] = x;
                    pq.insert({d[y], y});
                }
            }
        }
        // adaugam in vectorul distances doar distantele de la source la enemies
        // care sunt valide si doar pentru cazurile in care putem construi
        // fortificatie
        for (int i = 0; i < nr; i++) {
            if (d[enemies[i]] != INT_MAX && find(enemies.begin(), enemies.end(),
             p[enemies[i]]) == enemies.end())
            distances.push_back(DijkstraResult(enemies[i],
             d[enemies[i]], p[enemies[i]]));
        }
    }
    int minim_times() {
        int i = 0;
        // pentru fiecare foritificatie care trebuie construita
        while (i <= k) {
            // stergem distantele minime
            distances.clear();

            // recalculam distantele minime de la source la enemies
            get_result();

            // le sortam in ordine crescatoare pentru a o afla pe cea
            // mai mica
            sort(distances.begin(), distances.end(),
                    [](const DijkstraResult&a, const DijkstraResult&b)->bool{
                        return a.d < b.d;
                    });

            // cautam vecinul enemyului
            for (unsigned int j = 0; j < adj[distances[0].node].size(); j++) {
                // parintele nodului enemy este vecinul intre care putem pune
                // fortificatie
                if (adj[distances[0].node][j].first == distances[0].p) {
                    auto y = adj[distances[0].node][j].first;
                    auto w = adj[distances[0].node][j].second;

                    // punem fortificatie crescand weightul muchiei dintre
                    // enemy si parintele sau, si viceversa
                    adj[distances[0].node][j].second++;

                    pair<int, int> p = {distances[0].node, w};
                    auto it = find(adj[y].begin(), adj[y].end(), p);
                    it->second++;
                    break;
                }
            }
            i++;
        }
        // sortam crescator distantele pentru a afla distanta minima finala
        sort(distances.begin(), distances.end(),
        [](const DijkstraResult&a, const DijkstraResult&b)->bool{
            return a.d < b.d;
        });
        return distances[0].d;
    }
    void print_output() {
        ofstream fout("fortificatii.out");
        fout << minim_times() <<endl;
        fout.close();
    }
};
int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
