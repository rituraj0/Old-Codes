#include<iostream>
#include <stdio.h>
#include <math.h>
typedef long long int lg;
/* Prints the n-th fraction in Cantor's enumeration. */
void print_fraction(lg n,lg k)
{
    lg d = (-1 + sqrt(1 + 8 * n)) / 2;  /* Diagonals to skip *///TERM 14 IS 2/4
    lg e = n - d * (d + 1) / 2;         /* Extra steps after the skip. */
    lg v1 = e <= 1 ? d + e : d + 2 - e;
    lg v2 = e <= 1 ?     1 : e;

    printf("TERM %lld IS %lld/%lld\n",k, d % 2 == 0 ? v1 : v2,
                        d % 2 == 0 ? v2 : v1);
}

int main()
{
    lg i,test,j;
    scanf("%lld",&test);
   for(j=1;j<=test;j++)
    {
        scanf("%lld",&i);
        print_fraction(i,j);
    }

   return 0;
}
