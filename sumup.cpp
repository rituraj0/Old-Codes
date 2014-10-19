#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
int test;
float n;
scanf("%d",&test);

while(test--)
{
scanf("%f",&n);

printf("%0.5f\n",(((n+1)*(n+1)-n-1)/2)/((n+1)*(n+1)-n));
}

return 0;
}
