// Originally writted by Burundik1
// Optimizations by madhur4127

/** Interface */
inline char readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

/******************************** FAST IO STARTS *****************************/
static const int buf_size = 1 << 16;
alignas(64) static char buf[buf_size];
static int len = 0, pos = 0;
inline char getChar() {
    if (__builtin_expect(pos == len, 0)) pos = 0, len = fread(buf, 1, buf_size, stdin);
    // assert(pos != len);
    return buf[pos++];
}
inline char readChar() {
    char c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}
template <class T> inline T readInt() {
    char s = 1, c = readChar();
    T x = 0;
    if (c == '-') s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

static int write_pos = 0;
alignas(64) static char write_buf[buf_size];
inline void writeChar(char x) {
    if (__builtin_expect(write_pos == buf_size, 0)) fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}
constexpr inline uint64_t P(uint32_t p) {
    uint64_t ret = 1;
    for (; p; p--)
        ret *= 10u;
    return ret;
}
uint32_t digits10(uint64_t v) {
    if (v < P(2)) return 1 + (v >= P(1));
    if (v < P(3)) return 3;
    if (v < P(12)) {
        if (v < P(8)) {
            if (v < P(6)) {
                if (v < P(4)) return 4;
                return 5 + (v >= P(5));
            }
            return 7 + (v >= P(7));
        }
        if (v < P(10))
            return 9 + (v >= P(9));
        return 11 + (v >= P(11));
    }
    return 12 + digits10(v / P(12));
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
template <class T>
inline void writeInt(T x, char end) {
    if (__builtin_expect(write_pos + 21 >= buf_size, 0)) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    if (x < 0) writeChar('-'), x = -x;
    write_pos += u64ToAsciiTable(x);
    if (end) writeChar(end);
}
inline void writeWord(const char *s) {
    while (*s)
        writeChar(*s++);
}
struct Flusher {
    ~Flusher() {
        if (write_pos) fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;
/******************************** FAST IO ENDS *****************************/
