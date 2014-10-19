#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long int lg;

void sort(lg,lg,lg);

struct node
{
lg f[3];//st starting time ft finishing point
}a[100009];

int main()
{
  lg n,m,k,i,cn,t;

 for(scanf("%lld",&t);t--;)
{

 scanf("%lld",&n);

 for(i=0;i<n;i++)
  scanf("%lld%lld",&a[i].f[0],&a[i].f[1]);

 
 sort(0,n-1,1);

 cn=1;
 k=0;

 for(m=1;m<n;m++)
   if((a[m].f[0]>=a[k].f[1])&&(cn++)&&(k=m) );
     
    

 printf("%lld\n",cn);
}
return 0;

}













void sort(lg l,lg r,lg x)
{
     
     lg p,i,j;
     node temp;
     if(l<r)
     {
            i=l;
            j=r+1;
            
            p=a[l].f[x];//bhai yaha finishing  time pe sort kar rahe hai
            do{
                   do i++;
                   while(a[i].f[x]<p && i<r);
                   
                   do j--;
                   while(a[j].f[x]>p);
                   
                   if(i<j)
                   {temp=a[i];
                   a[i]=a[j];
                   a[j]=temp;
                   }
                   
                   }while(i<j);
                   
               temp=a[l];
               a[l]=a[j];
               a[j]=temp;
                
  
               sort(l,j-1,x);
               sort(j+1,r,x);
               }
               
               }

