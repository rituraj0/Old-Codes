#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long int lg;

lg gc(lg n,lg m)
{ if(m<=n && n%m == 0)
   return m;
  if(n < m)
   return gc(m,n);
  else
  return gc(m,n%m);
 }


int main()
{

int test;

lg sm,n,i,x,y;
scanf("%d",&test);

while(test--)
{
  scanf("%lld",&n);
 
  sm=0;
 
 for(i=1;i<=n;i++) 
 {x=gc(i,n);
 //cout<<i<<"   "<<x<<endl;
  
  y=(i*n)/x;
 
  sm+=y;
 }

 printf("%lld\n",sm);

}

return 0;
}


