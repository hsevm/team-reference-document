// Left: 0..n-1, Right: 0..m-1
int n, m;
vector<vector<int>> gl, gr;

bool dfs_kuhn(int u, vector<int> &pairR, vector<int> &color, int c) {
    color[u] = c;
    for (auto v : gl[u]) {
        if (pairR[v] == -1) {
            pairR[v] = u;
            return true;
        }
    }
    for (auto v : gl[u]) {
        if (color[pairR[v]] != c && dfs_kuhn(pairR[v], pairR, color, c)) {
            pairR[v] = u;
            return true;
        }
    }
    return false;
}

vector<int> kuhn_matching() {
    vector<int> pairR(m, -1);
    vector<int> color(n, 0);
    for (int u = 0; u < n; ++u) {
        dfs_kuhn(u, pairR, color, u + 1);
    }
    return pairR;
}

void dfs_min_vertex_covering(int u, vector<int> &pairR, vector<bool> &visited) {
    visited[u] = true;
    for (auto v : gl[u]) {
        if (!visited[pairR[v]]) {
            dfs_min_vertex_covering(pairR[v], pairR, visited);
        }
    }
}

pair<vector<int>, vector<int>> min_vertex_covering() {
    vector<int> pairR = kuhn_matching();
    vector<bool> is_paired_left(n, false);
    for (auto &u : pairR) {
        if (u != -1) {
            is_paired_left[u] = true;
        }
    }
    vector<bool> visited(n, false);
    for (int u = 0; u < n; ++u) {
        if (!is_paired_left[u] && !visited[u]) {
            dfs_min_vertex_covering(u, pairR, visited);
        }
    }
    vector<int> res_left, res_right;
    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            res_left.emplace_back(u);
        }
    }
    for (int v = 0; v < m; ++v) {
        if (pairR[v] != -1 && visited[pairR[v]]) {
            res_right.emplace_back(v);
        }
    }
    return {res_left, res_right};
}