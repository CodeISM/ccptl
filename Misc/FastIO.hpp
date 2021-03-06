// Originally writted by Burundik1; Optimizations by madhur4127
// NOTE: Last input character MUST end by a new line, otherwise it is UB
// Examples:
//       int n = read();
//       string s = read<string>; // supported types in template -- char, ints (signed/unsigned, 32/64), string
//       write(n, ' '); // prints 'n' and then a space
//       write(s, '\n'); // supported types in template -- char, ints (signed/unsigned, 32/64), string

/** Read */
static const int buf_size = 1 << 16;
static char buf[buf_size];
static int len = 0, pos = 0;
inline char getChar() {
    if (__builtin_expect(pos == len, 0)) pos = 0, len = fread(buf, 1, buf_size, stdin);
    return buf[pos++];
}
template <typename T = int> inline T read() {
    char s = 1, c = read<char>();
    T x = 0;
    if (c == '-') s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}
template <>
inline char read<char>() {
    char c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}
template <>
inline string read<string>() {
    string s;
    for (char c = getChar(); c > ' '; c = getChar())
        s += c;
    return s;
}
/** Write */
static int write_pos = 0;
static char write_buf[buf_size];
uint32_t digits10(uint64_t v) {
    int len = 1;
    while (v >= 10000)
        v /= 10000, len += 4;
    return len + (v < 100 ? v >= 10 : 2 + (v >= 1000));
}
unsigned u64ToAsciiTable(uint64_t value) {
    static const char digits[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
    uint32_t const length = digits10(value);
    uint32_t next = length - 1;
    char *dst = &write_buf[write_pos];
    for (; value >= 100; next -= 2, value /= 100) {
        auto const i = (value % 100) * 2;
        dst[next] = digits[i + 1], dst[next - 1] = digits[i];
    }
    // Handle last 1-2 digits
    if (value < 10) {
        dst[next] = '0' + value;
    } else {
        auto i = uint32_t(value) * 2;
        dst[next] = digits[i + 1], dst[next - 1] = digits[i];
    }
    return length;
}
template <typename T = int> inline void write(T x, char end = 0) {
    if (__builtin_expect(write_pos + 21 >= buf_size, 0)) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    if (x < 0) write<char>('-'), x = -x;
    write_pos += u64ToAsciiTable(x);
    if (end) write<char>(end);
}
template <> inline void write<char>(const char x, char) {
    if (__builtin_expect(write_pos == buf_size, 0)) fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}
template <> inline void write<string>(const string s, char end) {
    for (const char c : s)
        write<char>(c);
    if (end) write<char>(end);
}
struct Flusher {
    ~Flusher() {
        if (write_pos) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;
