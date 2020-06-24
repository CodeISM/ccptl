/*
 * Author: Madhur Chauhan, Ankur Dua, CCPTL
 * Uses: Prime generation using Sieve of Eratosthenes. Optimized for time and space.
 * Time Complexity: O(n log log n)
 * Space Complexity: O(N/128 + #primes)
 * Status: Tested
 */
template <int LIM>
vector<int> prime_seive() {
    vector<int> ret{2}; // add {2} and don't think about even numbers anymore
    if (LIM == 1) return ret;
    ret.reserve(LIM / log(LIM));                     // #primes, pi(x) ~=  x / ln(x)
    auto bsp = make_unique<bitset<(LIM + 3) / 2>>(); // tackoverflow
    int64_t i = 3, end = (LIM + 1) / 2;
    for (i = 3; i * i <= LIM; i += 2) {
        if ((*bsp)[(i + 1) / 2]) continue;
        ret.push_back(i);
        for (int64_t j = (i * i + 1) / 2; j <= end; j += i)
            (*bsp)[j] = 1;
    }
    for (i = (i + 1) / 2; i <= end; ++i)
        if (!(*bsp)[i]) ret.push_back(i);
    ret.shrink_to_fit();
    return ret;
}