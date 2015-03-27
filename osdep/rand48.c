/*
 * SVID random number generators for systems that don't have them (Windows)
 *
 * Copied from musl libc <http://www.musl-libc.org/>
 * Copyright © 2005-2014 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <inttypes.h>
#include "osdep/rand48.h"

static unsigned short seed48[7] = { 0, 0, 0, 0xe66d, 0xdeec, 0x5, 0xb };

static uint64_t rand48_step(unsigned short *xi, unsigned short *lc)
{
    uint64_t a, x;
    x = xi[0] | (xi[1]+0U)<<16 | (xi[2]+0ULL)<<32;
    a = lc[0] | (lc[1]+0U)<<16 | (lc[2]+0ULL)<<32;
    x = a*x + lc[3];
    xi[0] = x;
    xi[1] = x>>16;
    xi[2] = x>>32;
    return x & 0xffffffffffffull;
}

double mp_erand48(unsigned short s[3])
{
    union {
        uint64_t u;
        double f;
    } x = { 0x3ff0000000000000ULL | rand48_step(s, seed48+3)<<4 };
    return x.f - 1.0;
}

double mp_drand48(void)
{
    return mp_erand48(seed48);
}
