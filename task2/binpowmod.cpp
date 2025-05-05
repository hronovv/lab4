#include "binpowmod.h"
unsigned long long binpowmod(unsigned long long x, unsigned long long y,
                             long long N) {


    if (N < 0) {
        N *= -1;
    }
    if (y == 0) {
        return 1;
    }
    unsigned long int z = binpowmod(x % N, y / 2, N) % N;
    if (y % 2 == 0) {
        return (z * z) % N;
    } else {
        return ((x % N) * ((z * z) % N)) % N;
    }
}
