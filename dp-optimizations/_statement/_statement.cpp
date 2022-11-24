// x[] — sorted array of N points
// Question: min cost to cover them with K segments (cost(seg)=len^2(seg))
int cost(int i, int j) {
    return (x[j] - x[i]) * (x[j] - x[i]);
}
// f[k][n] --- k segments, n first points
for (int k = 1; k <= K; k++)
    for (int n = 1; n <= N; n++)
        for (int i = 0; i < n; i++)
            f[k][n] = min(f[k][n], f[k - 1][i] + cost(i, n));
