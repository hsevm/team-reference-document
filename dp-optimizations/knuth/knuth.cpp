// opt[k-1][n] <= opt[k][n] <= opt[k][n+1]
for (int k = 1; k <= K; k++)
    for (int n = N; n >= 1; n--) {
        f[k][n] = +INF;
        for (int i = opt[k - 1][n]; i <= opt[k][n + 1]; i++) {
            int val = f[k - 1][i] + cost(i, n);
            if (val < f[k][n]) f[k][n] = val, opt[k][n] = i;
        }
    }