#include<iostream>
#include<cstdio>
#include<climits>
using namespace std;
int main()
{
int test;
scanf("%d",&test);
while(test--)
{

 int dp[1001][1001]={0};
  int n,k,w,i;
 int wt[1000],pr[1000];
 cin>>n>>k;//k is wieght

int  minwt=INT_MAX,j,x,mn;

 for(i=1;i<=n;i++)
  {cin>>pr[i];//wt. of pr[i] is  i itself
     wt[i]=i;    
  }
 
for(i=1;i<=n;i++)
 if(pr[i]!=-1)
 {minwt=i;break;}

for(i=0;i<=n;i++)
dp[0][i]=0;//dp 0 wt. so price 0

for(i=0;i<=k;i++)
dp[i][0]=0;//number of item selected is 0 


 for(i=1;i<minwt;i++)
   for(j=1;j<=n;j++)
     dp[i][j]=0;


for(w=1;w<=k;w++)
{ 
 for(i=1;i<=n;i++)
    {
       mn=INT_MAX;
       
         for(j=1;j<=n;j++)
            if(pr[j]!=-1 && wt[j]<=w)
              {
                if(dp[w-wt[j]][i-1]>0 || w==wt[j])
                 { x=dp[w-wt[j]][i-1]+pr[j];
                   if(x<=mn)
                     mn=x;
                 }
              }
       //dp[w][i]=x;

       if(mn==INT_MAX)
        dp[w][i]=0;
       else
         dp[w][i]=mn;
   }
}
x=INT_MAX;

for(i=1;i<=n;i++)
 if(dp[k][i]!=0 && dp[k][i]<x)
  x=dp[k][i];

if(x==INT_MAX)
x=0;

if(x!=0)
cout<<x<<endl;
else
printf("-1\n");

}

return 0;
}
