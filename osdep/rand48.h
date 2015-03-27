#ifndef MP_RAND48_H_
#define MP_RAND48_H_

#include "config.h"

#if HAVE_RAND48
#include <stdlib.h>
#else
double mp_drand48(void);
double mp_erand48(unsigned short int xsubi[3]);

#define drand48(...) mp_drand48(__VA_ARGS__)
#define erand48(...) mp_erand48(__VA_ARGS__)
#endif

#endif
