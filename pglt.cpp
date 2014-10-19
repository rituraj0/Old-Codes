#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
   int e,f,i,j,n,vl[100],wt[100],wf,tp;
   
  cin>>e>>f;
  wf=f-e;

  cin>>n;

 for(i=0;i<n;i++)
  cin>>vl[i]>>wt[i];


 int dp[wf+10];

 for(i=0;i<wf+5;i++)
  dp[i]=-1;//-1 means no soultion so far

 dp[0]=0;

 for(i=0;i<=wf;i++)
 {
     for(j=0;j<n;j++)
       {
         if(wt[j]<=i)
           {
              tp=dp[ i-wt[j] ]+vl[j];
                if(dp[i]==-1)
                   dp[i]=tp;
                 else if(dp[i]>tp)
                   dp[i]=tp;      
            }    
        }
  }

  cout<<dp[wf]<<endl;
  
  return 0;
}
