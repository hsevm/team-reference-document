// [l, r] -- count f[k][l..r]
// [L, R] -- i = L..R
void solve(int l, int r, int L, int R, int k) {
    if (l > r) return;  // empty segment
    int m = (l + r) / 2, opt = L;
    // find answer for f[k][m]
    for (int i = L; i <= min(R, m); i++) {
        int val = f[k - 1][i] + cost(i, m);
        if (val < f[k][m])
            f[k][m] = val, opt = i;
    }
    solve(l, m - 1, L, opt, k);
    solve(m + 1, r, opt, R, k);
}
for (int k = 1; k <= K; k++)
    solve(1, n, 0, n - 1, k);
