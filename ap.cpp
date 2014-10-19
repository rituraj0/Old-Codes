#include<iostream>
#include<cstdio>
int main()
{
    int test;
    long long int a,d,n,x,y,z;
    scanf("%d",&test);
    while(test--)
    {
     scanf("%lld %lld%lld",&x,&y,&z);
     
     n=(2*z)/(x+y);
     
     d=(y-x)/(n-5);
     
     a=x-2*d;
     
     printf("%lld\n",n);
     for(x=0;x<n;x++)
      printf("%d ",a+x*d); 
      
      printf("\n");
      
      }
      
      return 0;
      }                        
