#include<iostream>
#include<cstdio>
typedef long long int lg;
int main()
{
lg n;
scanf("%lld",&n);


if(n%10!=0)
printf("1\n%lld\n",n%10);
else
printf("2\n");

return 0;
}

