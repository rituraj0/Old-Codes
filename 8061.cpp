#include<iostream>
#include<stdio.h>
using namespace std;
long long int a[1000010];
void sort(int,int);

void sort(int l,int r)
{
     int p,i,j;
     long long int temp;
     if(l<r)
     {
            i=l;j=r+1;
            p=a[l];
            do{
                   do i++;
                   while(a[i]<p && i<r);
                   
                   do j--;
                   while(a[j]>p);
                   
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
    int i,n,k;
    
    int test;
    long long int dm,tp;
    
    scanf("%d",&test);
    
    while(test--)
    {
   scanf("%d%d",&n,&k);
                 
    
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    
    sort(0,n-1);  

    
   int  sl=0;
    dm=1000000009;
    
    for(i=0;i<n;i++)
    {
     if(i+k-1<n)               
      {tp=a[i+k-1]-a[i]; 
       if(tp<dm)
        { dm=tp;
        sl=i;
        }
       }            
       }
       
    printf("%lld\n",a[sl+k-1]-a[sl]);
       
    
   }//end while
   
   
   
   
    
    return 0;
}
