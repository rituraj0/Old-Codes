#include<iostream>
#include<cstdio>
#include<cstdlib>
typedef long long int lg;
int main()
{

 lg test,n1,n2,i,j,mn,x;
 
 scanf("%lld",&test);

while(test--)
{
  scanf("%lld",&n1);
lg a[10005],b[1005];
 for(i=0;i<n1;i++)
 scanf("%lld",&a[i]);


scanf("%lld",&n2);

 for(i=0;i<n2;i++)
 scanf("%lld",&b[i]);

 mn=2000000;
 
 for(i=0;i<n1;i++)
 {
    for(j=0;j<n2;j++)
   {
      x=abs(a[i]-b[j]);
   if(x<mn)
   mn=x;
  }

 }

printf("%lld\n",mn);

}

return 0;
}
