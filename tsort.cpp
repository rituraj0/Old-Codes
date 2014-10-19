#include<iostream>
#include<stdio.h>
using namespace std;
int a[1000010];
void sort(int,int);
void sort(int l,int r)
{
     int p,i,j,temp;
     if(l<r)
     {
            i=l;//index
            j=r+1;//index
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
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    
    sort(0,n-1);
    
    for(i=0;i<n;i++)
    printf("%d\n",a[i]);
    
    return 0;
}

