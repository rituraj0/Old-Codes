#include<iostream>
#include<cstdio>
typedef long long int lg;


int main()
{

lg n,cf[2000],cn=0,i,j,q,sm,sq,s;

scanf("%lld",&n);

while(n!=-1)
{
 cn++;



 for(i=0;i<=n;i++)
  scanf("%lld",&cf[i]);

  scanf("%lld",&q);
printf("Case %lld:\n",cn);
 for(i=0;i<q;i++)
{

 scanf("%lld",&s);
 
 sm=cf[n];
 sq=1;
 
 for(j=n-1;j>=0;j--)
 {sq=sq*s;
  sm=sm+cf[j]*sq;
 }
 printf("%lld\n",sm);

 }//end for
scanf("%lld",&n);
 
}//end while

return 0;
}

 


