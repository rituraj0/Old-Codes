#include<iostream>
#include<cstdio>
#include<string.h>
#include<vector>
using namespace std;

#define min(a,b) (((a)<(b))?(a):(b))
#define rep(i,n) for(i=0;i<(n);i++)
#define MAXN 100000

vector<int> adj[MAXN+2];
int n;
int dp[MAXN+2][2];
/*Problem Link : https://www.spoj.pl/problems/PT07X/

This is a classic dynamic programming problem. We'll need to find minimal vertex cover of an unweighted, undirected tree.



We'll try to find the optimal solution for the subtree rooted at each node considering either its parent is covered (and as such the edge between it and its parent) or its parent is not covered. In the first case, we have the freedom to either cover the current node or not. But in the second case, we must cover the current node. Optimal solution is the one that uses least nodes.

-*/
int go(int cur, int parent, bool isParentCovered) 
{
 if(dp[cur][isParentCovered] != -1)//memoization
 return dp[cur][isParentCovered];

 int &ret = dp[cur][isParentCovered];

 ret = 0;

 int i, r;

 if(isParentCovered) 
 {
     rep(i, adj[cur].size()) 
       if(adj[cur][i] != parent) 
        {
         ret += go(adj[cur][i], cur, false);
        }

     r = 1;

    rep(i, adj[cur].size())
       if(adj[cur][i] != parent) 
         {
           r += go(adj[cur][i], cur, true) ;
          }
 
    ret = min(ret, r);
 }
else 
 {
  ret = 1;
  rep(i, adj[cur].size())
    if(adj[cur][i] != parent)
      {
      ret += go(adj[cur][i], cur, true) ;
      }
 }

 return ret;
}



int main() {
 int i,u,v;
 int r1,r2;
 while(scanf(" %d",&n) == 1)
 {
  
   for(i=1;i<=n;i++) 
    adj[i].clear();
       
       for(i=1;i<n;i++)
     {
     scanf(" %d %d",&u,&v);
      adj[u].push_back(v);
       adj[v].push_back(u);
     }
 
  memset(dp,-1,sizeof(dp));
 
   r1 = 1;
 
  rep(i,adj[1].size())
    r1 += go(adj[1][i], 1, true);
  
  r2 = 0;
  
  rep(i, adj[1].size()) 
    r2 += go(adj[1][i], 1, false);
 
  printf("%d\n",min(r1,r2));

 }
 return 0;
}
