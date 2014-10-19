#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cctype>
using namespace std;
typedef long long int lg;

lg n;

struct node
{
lg s,f;
}a[100005];

void sort(lg l,lg r)
{
     lg p,i,j;
     node temp;
     if(l<r)
     {
            i=l;
            j=r+1;
            
            p=a[l].f;//bhai yaha finishing  time pe sort kar rahe hai
            do{
                   do i++;
                   while(a[i].f<p && i<r);
                   
                   do j--;
                   while(a[j].f>p);
                   
                   if(i<j)
                   {temp=a[i];
                   a[i]=a[j];
                   a[j]=temp;
                   }
                   
                   }while(i<j);
                   
               temp=a[l];
               a[l]=a[j];
               a[j]=temp;
               sort(l,j-1);
               sort(j+1,r);
               }
               
               }






int main()
{

 lg test,i,j,cn;

scanf("%lld",&n);

while(n!=-1)
{
 
  for(i=0;i<n;i++)  
   scanf("%lld",&a[i].s);
  for(i=0;i<n;i++)  
   scanf("%lld",&a[i].f);

  sort(0,n-1);
 

 for(i=0;i<n;i++)
  cout<<a[i].s<<"   "<<a[i].f<<endl;

 node  sl;
 
  sl=a[0];//selected so far
  cn=1;

 for(i=1;i<n;i++)
 {

   if(a[i].s>sl.f)
   cn++;
  
   sl=a[i];
 }
 
 printf("%lld\n",cn);
scanf("%lld",&n);

}
return 0;
}

