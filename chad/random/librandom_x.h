#if defined(X)
#ifndef XA
# define XA 0
#endif
#ifndef XB
# define XB 0
#endif
X(xorshift , 32, XA                  )
X(lcg      , 32, XA                  )
X(lcg2     , 32, XA                  )
X(pcg      , 32, XA, RANDOM_PCG_PRIME)
X(photon   , 32, XA, XB              )
X(romuduo  , 32, XA, XB              )
X(xoroshiro, 64, XA, XB              )
X(splitmix , 64, XA                  )
X(wy       , 64, XA                  )
X(mt19937  , 32, XA                  )
#undef X
#undef XA
#undef XB
#endif
