#include<iostream>
#include<cstdio>
int n,k;
long long int m=1000000003,a[1002][1002]={0};

int main()
{
long long int x=0;
scanf("%d%d",&n,&k);

a[1][0]=a[1][1]=1;
int i,j;



if(2*k>n)
{printf("0\n");
return 0;
}
else if(k==1)
{
printf("%d\n",n);
return 0;
}


for(i=2;i<=n-k+1;i++)
{
a[i][0]=a[i][i]=1;

  for(j=1;j<=k;j++)
  a[i][j]=(a[i-1][j-1]+a[i-1][j] )%m;

}//end for

x=( a[n-k+1][k]-a[n-k-1][k-2] )%m;
if(x<0)
x+=1000000003;
printf("%lld\n",x);

return 0;
}


