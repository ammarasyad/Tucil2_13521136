//
// Created by ammar on 2/26/23.
//

#ifndef TUCIL2_13521136_RAND_H
#define TUCIL2_13521136_RAND_H

/**
 * Generates a random number using the RDRAND instruction
 * @param bound
 * @return Random number
 */
double getRand(long double bound = 1e+18 /* Literally just a random number so it's not huge */) {
    unsigned long long result;
    __builtin_ia32_rdrand64_step(&result);
    return (double) (result / bound);
}

#endif
