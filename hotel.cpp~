#include<iostream>
#include<cstdio>
long long int sm,mx,n,a[300005];
int main()
{
long long int i,test,m;



scanf("%lld%lld",&n,&m);

for(i=0;i<n;i++)
scanf("%lld",&a[i]);


sm=a[0];
mx=-1;
long long int st=0;
for(i=1;i<=n;i++)
{
 
 while( sm > m && st<(i-1) )
 {sm=sm-a[st];
  st++;
 }

 if(sm<=m && sm>mx)
  mx=sm;
 

 if(i<n)
 sm=sm+a[i];

}
 
printf("%lld\n",mx);

return 0;
}


