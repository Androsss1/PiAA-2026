#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <utility>
#include <algorithm>
#include <iomanip>

using namespace std;

const double INF = 1e15;

void gen_matrix(int n, const string &filename) {
    mt19937 gen(42);
    uniform_real_distribution<> distr(1.0, 100.0);
    ofstream out(filename);
    vector<vector<double>> m(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                m[i][j] = 0.0;
            } else {
                m[i][j] = round(distr(gen) * 100) / 100.0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << m[i][j];
            if (j < n - 1) out << " ";
        }
        out << "\n";
    }
}

double prim_mst(const vector<vector<double>>& graph, const vector<int>& nodes) {
    if (nodes.empty()) return 0.0;

    int n = graph.size();
    vector<bool> in_mst(n, false);
    vector<double> min_dist(n, INF);
    double total = 0.0;

    min_dist[nodes[0]] = 0.0;

    for (size_t i = 0; i < nodes.size(); ++i) {
        int u = -1;
        double best = INF;
        for (int v : nodes) {
            if (!in_mst[v] && min_dist[v] < best) {
                best = min_dist[v];
                u = v;
            }
        }
        if (u == -1 || best >= INF) return INF;

        in_mst[u] = true;
        total += best;

        for (int v : nodes) {
            if (!in_mst[v] && graph[u][v] > 1e-9 && graph[u][v] < min_dist[v]) {
                min_dist[v] = graph[u][v];
            }
        }
    }
    return total;
}

pair<vector<int>, double> alsh2(int n, const vector<vector<double>>& graph) {
    cout << fixed << setprecision(2);

    vector<bool> visited(n, false);
    vector<int> path;
    path.reserve(n + 1);

    int cur = 0;
    visited[cur] = true;
    path.push_back(cur);
    double total_cost = 0.0;

    vector<int> buf;
    buf.reserve(n);

    for (int step = 0; step < n - 1; ++step) {
        cout << "[Step " << (step + 1) << "] Current: " << cur << "\n";
        int best_next = -1;
        double best_est = INF;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[cur][v] > 1e-9) {
                buf.clear();
                for (int j = 0; j < n; ++j) {
                    if (!visited[j] && j != v) buf.push_back(j);
                }

                double mst_cost = prim_mst(graph, buf);
                if (mst_cost >= INF) continue;

                double est = graph[cur][v] + mst_cost;
                cout << "  Candidate " << v << ": edge=" << graph[cur][v]
                     << ", MST=" << mst_cost << ", est=" << est << "\n";

                if (est < best_est) {
                    best_est = est;
                    best_next = v;
                }
            }
        }

        if (best_next == -1) {
            cout << "  No valid continuation.\n";
            return {{}, -1.0};
        }

        cout << "  -> Selected: " << best_next << " (est=" << best_est << ")\n\n";
        total_cost += graph[cur][best_next];
        visited[best_next] = true;
        path.push_back(best_next);
        cur = best_next;
    }

    if (graph[cur][0] <= 1e-9) {
        cout << "No return edge to start node.\n";
        return {{}, -1.0};
    }

    double return_cost = graph[cur][0];
    total_cost += return_cost;
    path.push_back(0);
    cout << "[Final] Return to 0: edge=" << return_cost << "\n\n";

    return {path, total_cost};
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    if (n < 2) return 1;

    gen_matrix(n, "matrix.txt");

    vector<vector<double>> matr(n, vector<double>(n));
    ifstream infile("matrix.txt");
    if (!infile) {
        cerr << "Failed to open matrix.txt\n";
        return 1;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            infile >> matr[i][j];
    infile.close();

    auto [path, cost] = alsh2(n, matr);
    if (cost < 0) {
        cout << "No valid path found.\n";
        return 1;
    }

    cout << "Result:\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i == path.size() - 1 ? "\n" : " -> ");
    }
    cout << "Cost: " << cost << "\n";

    return 0;
}
