#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long int lg;
int main()
{

lg i,a[1000005],test,k,mn,sm,n;

scanf("%lld",&test);

for(k=1;k<=test;k++)
{

  scanf("%lld",&n);

 for(i=0;i<n;i++)
  scanf("%lld",&a[i]);

 mn=a[0]; 
 sm=0;
 
 for(i=0;i<n;i++)
 {
  sm=sm+a[i];

 if(sm<mn)
 mn=sm;
 }

 if(mn>0)
 printf("Scenario #%lld: 1\n",k);
 else
  printf("Scenario #%lld: %lld\n",k,abs(mn-1));


}

return 0;
}
