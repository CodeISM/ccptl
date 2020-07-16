#include "Misc/modular.h"
template <int N = 1'000'000, int MOD = 998244353>
struct combinatorics {
    modular<MOD> fac[N + 1], inv[N + 1];
    combinatorics() : fac{}, inv{} {
        fac[0] = 1;
        for (int i = 1; i <= N; ++i)
            fac[i] = i * fac[i - 1];
        inv[N] = mexp(fac[N], MOD - 2);
        for (int i = N - 1; i >= 0; i--)
            inv[i] = (i + 1) * inv[i + 1];
    }
    modular<MOD> factorial(int n) const { return fac[n]; }
    modular<MOD> inverse_factorial(int n) const { return inv[n]; }
    modular<MOD> nCr(int n, int r) const {
        return n >= r ? fac[n] * inv[r] * inv[n - r] : 0;
    }
};
