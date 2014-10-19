#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long int lg;

int main()
{

 lg a[5],i,n,j,t;

 while( scanf("%lld",&a[0])!=EOF )
 {
   for(i=1;i<4;i++)
   scanf("%lld",&a[i]);

   for(i=0;i<4;i++)
     for(j=i+1;j<4;j++)
     {
          if(a[i]<a[j])
             {
                t=a[i];
                  a[i]=a[j];
                   a[j]=t;
              }

     }

 
    for(i=0;i<4;i++)
     cout<<a[i]<<"  ";
   cout<<endl;
 }

return 0;
}
 
