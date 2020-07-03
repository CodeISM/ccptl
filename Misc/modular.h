/*
 * Author : Madhur Chauhan
 * Use : Modular Arithmetic
 * Time Complexity : O(1) for arithmetic operations except division
 * Space Complexity: O(1)
 * Usage Notes: Template argument is the modulus which is set to default: 1e9+7. A modular int can be created by:
 *                  modular<> m = 56; // creates a modular integer initialize to 56 in MOD = 1e9+7
 *                  using mint = modular<998244353>; // MInt can be used like regular integer
 *                  vector<mint> dp(10, Mint(0)); // creater a vector with values initialized to 0
 *                  cout << m * 1'000'000'000'000 << endl; // will not overflow
 *              There is also a class "dmodular" which can be used when the modular is not known and cannot be used as template argument.
 *                  dmodular m(23, 1e9+7); // creates a dmodular integer with modulus as 1e9+7 (which is default).
 */
#include <cstdint>
#include <type_traits>

// Actual modular class. Use only if MOD is known otherwise use dmodular
template <int MOD = (int)1e9 + 7>
struct modular {
    int32_t value;
    static const int32_t mod = MOD;
    modular(int64_t v = 0, int32_t mod = MOD) : value{static_cast<int32_t>(v % mod)} {
        if (value < 0) value += mod;
    }
};

struct dmodular { // Use this if the MOD is not known at compile time
    int32_t mod, value;
    dmodular(long long v = 0, int32_t mod = 1e9 + 7) : mod{mod}, value{static_cast<int32_t>(v % mod)} {
        if (value < 0) value += mod;
    }
};
// Verbose C++ regions start, use C++20's concepts and constraints to make it less terse, yo!
template <typename> struct is_modular : public false_type {}; // this is used to check for whether T matches dmodular or Modular<>.
template <> struct is_modular<dmodular> : public true_type {};
template <int MOD> struct is_modular<modular<MOD>> : public true_type {};

template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> &operator+=(T &a, const U &b) {
    T temp(b);
    a.value += temp.value;
    if (a.value >= a.mod) a.value -= a.mod;
    return a;
}
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> operator+(T a, const U &b) { return a += b; }
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> &operator-=(T &a, const U &b) {
    T temp{b};
    a.value -= temp.value;
    if (a.value < 0) a.value += a.mod;
    return a;
}
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> &operator*=(T &a, const U &b) {
    T temp{b};
    a.value = (long long)a.value * temp.value % a.mod;
    return a;
}
// Useful functions
template <typename T> // make sure, T is Modular or modular. Otherwise overflow will occur
inline enable_if_t<is_modular<T>::value, T> mexp(T a, int64_t e) {
    T res(1, a.mod);
    for (; e; a *= a, e >>= 1)
        if (e & 1) res *= a;
    return res;
}
template <typename T>
inline T inverse(T a) {
    int64_t phi = a.mod - 1; // change this for general MOD where a^phi = 1 (mod MOD)
    return mexp(a, phi - 1);
}
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> &operator/=(T &a, const U &b) { return a *= inverse<T>(b); }
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> operator-(T a, const U &b) { return a -= b; }
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> operator*(T a, const U &b) { return a *= b; }
template <typename T, class U> inline enable_if_t<is_modular<T>::value, T> operator/(T a, const U &b) { return a /= b; }
template <typename T> inline enable_if_t<is_modular<T>::value, T> operator-(const T &a) { return 0 - a; }
template <typename T> inline enable_if_t<is_modular<T>::value, bool> operator==(const T &a, const T &b) { return a.value == b.value; }
template <typename T> inline enable_if_t<is_modular<T>::value, bool> operator!=(const T &a, const T &b) { return a.value != b.value; }
template <typename T> inline enable_if_t<is_modular<T>::value, ostream> &operator<<(ostream &os, const T &a) { return os << a.value; }
template <typename T> inline enable_if_t<is_modular<T>::value, istream> &operator>>(istream &is, T &a) {
    long long temp;
    is >> temp;
    a = T(temp);
    return is;
}