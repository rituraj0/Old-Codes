#include<iostream>
#include<cstdio>
typedef long long int lg;
int main()
{

lg test,k,i,j,n,r,mila;

scanf("%lld",&test);

for(k=1;k<=test;k++)
{

 scanf("%lld%lld",&n,&r);

  lg db[r+1][2];

 for(i=0;i<r;i++)
 scanf("%lld%lld",&db[i][0],&db[i][1]);

 mila=0;
 
 for(i=0;i<r && mila==0;i++)
 {
   for(j=i+1;j<r && mila==0;j++)
   {
       if(db[i][0]==db[j][0] && db[i][1]==db[j][1])
        mila=1;
        

   }

 }

 if(mila==0)
  printf("Scenario #%lld: possible\n",k);
  else 
  printf("Scenario #%lld: impossible\n",k);
}



/*

Scenario #1: possible

Scenario #2: impossibl
*/
return 0;
}
     
     


