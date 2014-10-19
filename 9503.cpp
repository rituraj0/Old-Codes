#include<iostream>
#include<cstdio>
typedef long long int lg;
using namespace std;



lg jana[100006]={0},s[100006]={0},a,b,n;

lg cost(lg i,lg j)
{
  jana[i]=0;//pahle wale ko mitane ke lia
 lg  cstay=(s[j]-s[i]-1)*b;
   
 lg cfly=2*a;

 if( cstay < cfly)
  return cstay ;//ruka hai yaha
 else
  {
      jana[i]=1;
     return cfly;
  }

}
   

int main()
{

  int test;

  
  lg c,d,tt,tc,sc,i,j,sh,bj,tp;

  scanf("%d",&test);
  lg k=1;
 while(k<=test)
 {
 scanf("%lld%lld%lld",&n,&a,&b);

 for(i=0;i<n;i++)
 scanf("%lld",&s[i]);
 
  tt=0;
  for(i=0;i<n-1;i++)
  {
     tp=cost(i,i+1);
      tt+=tp;
  }

  /*for(i=0;i<n-1;i++)
   if(jana[i]==1)
     tt+=2*a;
*/
      tt+=n*b;
   
       tt+=2*a;//pahle wale aane nad last wale jane ka

  printf("Case #%lld: %lld\n",k,tt);
  k++;
 }

return 0;
} 
     
 
     
   
     

    

  
