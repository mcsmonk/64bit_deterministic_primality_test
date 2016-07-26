#include <stdio.h>
#include "deterministic_mr_64bit_prime_test.h"

int main(int argc, char *argv[])
{
    unsigned long n, fbb;
    int state = 0;
    int p1, p2;
    //unsigned long norm = ;

    printf("sizeof(unsigned long) = %d \n", sizeof(unsigned long));

    fbb = 3000000000UL;
    //n   = 48164915UL;
    n   = 2915682821UL;
    printf("%lu\n", n);
    printf("%s\n", deterministic_mr_64bit_prime_test(n)? "prime" : "composite");
    return 0;
}

