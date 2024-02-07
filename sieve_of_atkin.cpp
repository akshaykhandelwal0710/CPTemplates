const int N = 5e8;
bitset<N> is_prime;
// use is_prime[n>>1] to check for n
void sieve_of_atkin(int lim) {
    is_prime.reset();
    lim = (lim + 1) >> 1;
    for (int y = 1, m; (m = (y * y + 36) >> 1) < lim; y += 2) if (y % 3 != 0) {
        for (int k = 0; m < lim; m += (k += 36) + 18) is_prime.flip(m);
    }
    for (int x = 1, m; (m = (4 * x * x + 1) >> 1) < lim; ++x) if (x % 3 != 0) {
        for (int k = 0; m < lim; m += (k += 4)) is_prime.flip(m);
    }
    for (int y = 2, m; (m = (y * y + 3) >> 1) < lim; y += 2) if (y % 3 != 0) {
        for (int k = 0; m < lim; m += (k += 12)) is_prime.flip(m);
    }
    for (int y = 1, m; (m = ((2 * y + 6) * y + 3) >> 1) < lim; ++y) if (y % 3 != 0) {
        for (int k = 6 * y; m < lim; m += (k += 12)) is_prime.flip(m);
    }
    for (int p = 5, p2; (p2 = p * p) >> 1 < lim; p += 2) if (is_prime[p >> 1]) {
        for (int m = p2 >> 1; m < lim; m += p2) is_prime.reset(m);
    }
    if (1 < lim) is_prime.set(1);
}