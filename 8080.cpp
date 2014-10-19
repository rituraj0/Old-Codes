#include<iostream>
#include<cstdio>
int main()
{
    int test;
    int a,d,n,sm;
    scanf("%d",&test);
    while(test--)
    {
      scanf("%d%d%d",&n,&a,&d);
      sm=(n*(2*a+(n-1)*d))/2;
      printf("%d\n",sm);
      }
      
      return 0;
      }           
