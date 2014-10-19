#include<stdio.h>
int a[250005],in[10005];
void sort(int,int);
int main()
{
    int n,k,i,j,c=0;
    scanf("%d%d",&n,&k);
   
   for(i=0;i<n;i++)
   scanf("%d",&in[i]);
   
   c=0;
   
for(i=0;i<n;i++)
for(j=i+1;j<n;j++)
{a[c]=((in[i])^(in[j]));
c=c+1;
}

sort(0,c-1);

for(i=0;i<k;i++)
printf("%d ",a[i]);

scanf("%d",&n);
return 0;
}


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
               while(a[j]>pi);
             
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

