#include<iostream>
#include<stdio.h>
using namespace std;
long long int a[10010];
void sort(long long int,long long int);
void sort(long long int l,long long int r)
{
    long long int p,i,j,temp;
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
    long long int i,n,cn=0,sm=0,k,s;
    
    int test,c=0;
    scanf("%d",&test);
    
    while(c<test)
    {
    c++; 
    scanf("%lld%lld",&s,&n);
    
    for(i=0;i<n;i++)
    scanf("%lld",&a[i]);
    
    sort(0,n-1);
    
    cn=0;
    sm=0;
    
    for(i=n-1;i>=0;i--)
    {
       if(sm<s)
       {sm+=a[i];
       cn++;
       }
       else
       break;
       }
       
     if(sm>=s)
     printf("Scenario #%d:\n%d\n",c,cn); 
     else
      printf("Scenario #%d:\nimpossible\n",c); 
      
      
      }
       
       //system("pause");

       
       return 0;
       }                
   
    
