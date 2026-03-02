/* A C-program for MT19937, with initialization improved 2002/1/26.
 * Coded by Takuji Nishimura and Makoto Matsumoto.
 *
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. The names of its contributors may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mt19937.h"

/* Period parameters */
#define MT19937_N 624
#define MT19937_M 397
#define MT19937_MATRIX_A 0x9908B0DFU
#define MT19937_UPPER_MASK 0x80000000U
#define MT19937_LOWER_MASK 0x7FFFFFFFU

/* Tempering parameters */
#define MT19937_U 11
#define MT19937_D 0xFFFFFFFFU
#define MT19937_S 7
#define MT19937_B 0x9D2C5680U
#define MT19937_T 15
#define MT19937_C 0xEFC60000U
#define MT19937_L 18

/* Initialization multiplier */
#define MT19937_F 1812433253U

static inline
void twist(random_mt19937_t * randomp) {
    for (int i = 0; i < MT19937_N; i++) {
        uint32_t y = (randomp->mt[i] & MT19937_UPPER_MASK) |
                     (randomp->mt[(i + 1) % MT19937_N] & MT19937_LOWER_MASK);
        randomp->mt[i] = randomp->mt[(i + MT19937_M) % MT19937_N] ^ (y >> 1);
        if (y & 1) {
            randomp->mt[i] ^= MT19937_MATRIX_A;
        }
    }
    randomp->index = 0;
}

random_mt19937_t random_mt19937_init(uint32_t initial) {
    random_mt19937_t mt19937;
    mt19937.mt[0] = initial;
    for (int i = 1; i < MT19937_N; i++) {
        mt19937.mt[i] = MT19937_F * (mt19937.mt[i-1] ^ (mt19937.mt[i-1] >> 30)) + i;
    }
    mt19937.index = MT19937_N;
    return mt19937;
}

uint32_t random_mt1993732(random_mt19937_t * randomp) {
    if (randomp->index >= MT19937_N) {
        if (randomp->index > MT19937_N) {
            *randomp = random_mt19937_init(5489U);
        }
        twist(randomp);
    }

    uint32_t y = randomp->mt[randomp->index++];

    y ^= (y >> MT19937_U);
    y ^= (y << MT19937_S) & MT19937_B;
    y ^= (y << MT19937_T) & MT19937_C;
    y ^= (y >> MT19937_L);

    return y;
}
