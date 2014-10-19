#include<iostream>
#include<stdio.h>
int a[100000003];
void sort(int,int);
void sort(int l,int r)
{int pi,i,j;
int temp;

if(l<r)
{
       i=l;j=r+1;
       
       pi=a[l];
       
       do{
             do i++;
            while(a[i]<pi && i<r);
            
           do  j--;
           while(a[j]>pi && j>l);
           
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
int test,n,k,i,sum;
scanf("%d",&test);
while(test--)
{
scanf("%d%d",&n,&k);
for(i=0;i<n;i++)
scanf("%d",&a[i]);

sort(0,n-1);
sum=0;
for(i=n-1;i>=n-k;i--)
sum+=a[i];

printf("%d\n",sum);

}

return 0;
}


