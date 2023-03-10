#include <bits/stdc++.h>
#include<stdio.h>
using namespace std;

#define NMAX 50005

void dfs(int node, vector<int>& used, vector<int>& topsort,
 vector <int> adj[NMAX]) {
    // marcheze nodul ca fiind vizitat
    used[node] = 1;

    // parcurg vecinii
    for (auto& neigh : adj[node]) {
        if (!used[neigh]) {
            dfs(neigh, used, topsort, adj);
        }
    }

    // dupa ce am vizitat recursiv toti vecinii, adaugam
    // nodul la sortare
    topsort.push_back(node);
}
vector<int> solve_dfs(vector <int> adj[NMAX], int n) {
    // vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
    vector<int> topsort;

    // used[node] = 1 daca node a fost deja vizitat, 0 altfel
    vector<int> used(n + 1, 0);

    // pentru fiecare nod
    for (int node = 1; node <= n; ++node) {
        // daca nodul este nevizitat, pornim o parcurgere
        if (!used[node]) {
            dfs(node, used, topsort, adj);
        }
    }

    // rezultatul a fost obtinut in ordine inversa
    reverse(topsort.begin(), topsort.end());

    return topsort;
}
int main() {
    int n, m, a;
    ifstream fin("curse.in");
    fin >> n>> m>> a;
    int mat[a][n];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < n; j++) {
            fin >> mat[i][j];
        }
    }
    vector <pair<int, int>> v;
    vector <pair<int, int>> new_v;
    vector <int> adj[NMAX];
    for (int i = 0; i < a - 1; i++) {
        // adaug muchie intre nodurile adiacente
        adj[mat[i][0]].push_back(mat[i + 1][0]);

        // pentru masinilie adiacente egale de coloana 1, adaugam muchie
        // intre masinilie corespunzatoare acestor linii de pe coloana 2
        if (mat[i][0] == mat[i + 1][0]) {
            adj[mat[i][1]].push_back(mat[i + 1][1]);

            // salvam indecsii liniilor corespunzatoare masinilor egale
            v.push_back({i, i + 1});
        }
    }
    for (int j = 0; j < n - 2; j++) {
        // pentru fiecare pereche de masini adiacente egale
        for (auto &p : v) {
            // comparam daca pe coloana urmatoare se pastreaza egalitate
            if (mat[p.first][j + 1] == mat[p.second][j + 1]) {
                // adaugam muchie intre nodurile pe coloana imediat urmatoare
                adj[mat[p.first][j + 2]].push_back(mat[p.second][j + 2]);

                // salvam perechea care pastreaza egalitatea
                new_v.push_back(p);
            }
        }
        // atribuim noul vector de perechi
        v.clear();
        v = new_v;
        new_v.clear();
    }
    // sortare topologica pentru a afla ordinea masinilor
    vector <int> topsort = solve_dfs(adj, m);
    ofstream fout("curse.out");
    for (auto &it : topsort) {
        fout<< it <<" ";
    }
}
