#if 0
reference : Jiang, Yupeng, and Yingpu Deng. "Strong pseudoprimes to the first eight prime bases." Mathematics of Computation 83.290 (2014): 2915-2924.
#endif

#include <math.h>
#include "gmp.h"

static unsigned int mr_64bit_base[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };

/*
	deterministic Miller-Rabin prime test
	n-1 = (2**k)*q ,  q is odd
 */
int deterministic_mr_64bit_prime_test(unsigned long n)
{
	mpz_t temp, n_minus_1, b, q, mod;
	unsigned long t, ti;
	unsigned int i, j;
	unsigned int k;
	int result = 1;

	if (n <= 1UL) {
		return 0;
	}
	if (n == 2UL) {
		return 1;
	}
	else if ((n % 2UL) == 0UL) {
		return 0;
	}
	else if (n <= 37UL) {
	    t = sqrt(n);
	    for(ti=3UL; ti<=t; ti+=2UL) {
		if((n%ti) == 0UL)
		    return 0;
	    }
	    return 1;
	}

	mpz_init(temp);
	mpz_init_set_ui(mod, n);
	mpz_init(n_minus_1);
	mpz_sub_ui(n_minus_1, mod, 1UL);

	k = mpz_scan1(n_minus_1, 0UL);
	mpz_init(q);
	mpz_tdiv_q_2exp(q, n_minus_1, (unsigned long) k);

	for (i = 0; i < (sizeof(mr_64bit_base)/sizeof(unsigned int)); i++) {
		mpz_init_set_ui(b, (unsigned long)mr_64bit_base[i]);
		//gmp_printf("%Zd\n", b);

		mpz_powm(temp, b, q, mod);
		if ((mpz_cmp_ui(temp, 1UL) == 0) || (mpz_cmp(temp, n_minus_1) == 0)) {
			continue;
		}

		for (j = 1; j < k; j++) {
			mpz_powm_ui(temp, temp, 2UL, mod);
			if (mpz_cmp(temp, n_minus_1) == 0) {
				break;
			}
			if (mpz_cmp_ui(temp, 1UL) == 0) {
				result = 0;
				goto mr_end;
			}
		}
		if(j == k) {
			result = 0;
			goto mr_end;
		}
	}

mr_end:
	mpz_clear(temp);
	mpz_clear(b);
	mpz_clear(mod);
	mpz_clear(n_minus_1);
	mpz_clear(q);

	return result;
}

