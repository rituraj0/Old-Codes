#include<iostream>
#include<cstdio>
typedef long long int lg;

lg m;
void multiply(lg F[2][2], lg M[2][2]);
 
void power(lg F[2][2], lg n);
 
/* function that returns nth Fibonacci number */
lg fib(lg n)
{
  lg F[2][2] = {{1,1},{1,0}};
  if(n == 0)
    return 0;
  power(F, n-1);
  return (F[0][0])%m;
}
 
/* Optimized version of power() in method 4 */
void power(lg F[2][2], lg  n)
{
  if( n == 0 || n == 1)
      return;
  lg M[2][2] = {{1,1},{1,0}};
 
  power(F, n/2);
  multiply(F, F);
 
  if( n%2 != 0 )
     multiply(F, M);
}
 
void multiply(lg F[2][2], lg M[2][2])
{
  lg x =  (F[0][0]*M[0][0])%m + (F[0][1]*M[1][0])%m;
  lg y =  (F[0][0]*M[0][1])%m + (F[0][1]*M[1][1])%m;
  lg z =  (F[1][0]*M[0][0])%m + (F[1][1]*M[1][0])%m;
  lg w =  (F[1][0]*M[0][1])%m + (F[1][1]*M[1][1])%m;
 
  F[0][0] = x%m;
  F[0][1] = y%m;
  F[1][0] = z%m;
  F[1][1] = w%m;
}
 
/* Driver program to test above function */
int main()
{
  lg n = 9,test,x,an;
scanf("%lld",&test);

while(test--)
{
  scanf("%lld%lld",&n,&m);

    x=(fib(n+2)*2)%m-(n+2)%m;

   if(x<0)
   x=x+m;   
 an=x%m;
   

  printf("%lld\n",an);
 } 
  return 0;
}
