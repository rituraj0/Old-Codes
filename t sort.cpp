#include<iostream>
#include<stdio.h>
int a[250000];
void sort(int,int);
void sort(int l,int r)
{int pi,i,j;
int temp;

if(l<r)
{
       i=l;j=r+1;
       
       pi=a[l];
       
       do{
             do i++;while(a[i]<pi && i<=r);
             do  j--;while(a[j]>pi && j>=l);
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
              
