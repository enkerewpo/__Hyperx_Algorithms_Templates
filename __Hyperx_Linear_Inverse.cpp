void get_inv() {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (n - n / i) * inv[n % i] % n;
}