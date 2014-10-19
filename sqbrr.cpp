#include<iostream>
#include<cstdio>
using namespace std;
typedef long long int lg;

int f[100],n;
lg dp[100][100];

lg solve(int pos, int open) {
	
        if(open < 0) 
          return 0; // invalid
	
        if(pos == n) 
        return open == 0; //  agar [n][0] hai to 1 nahi to  0
	
 
 
	if(dp[pos][open]  != -1) return dp[pos][open] ;

 	if(f[pos])
           dp[pos][open]= solve(pos+1, open+1); // must put a [ here
	else
           dp[pos][open]=solve(pos+1, open+1) + solve(pos+1, open-1);  
        
       return  dp[pos][open]; // try [ and ] both
}

/*
//now converting this unit dp
int n;//intail number of n scanded
n=2*n;
 
 for(i=1;i<=n;i++)
  dp[n][i]=0;
  
  dp[n][0]=1;

  for(i=0;i<=n;i++)
   

 for(i=n-1;i>=0;i--) 
    for(j=1;j<=n/2+5;j++)//open ki number n/2 se jyada hogi hi nahi
       {
           if(f[i])
            dp[i][j]=dp[i+1][j+1];
            else
            dp[i][j]=dp[i+1][j+1]+dp[i+1][j-1];
        }

*/
//now 
int main() {
	
	int t,k,m,i,j;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &k);
		n*=2;
                 for(i=0;i<=n;i++) 
                   f[i]=0;
                 
                  for(i=0;i<=n;i++)
                    for(j=0;j<=n;j++)
                        dp[i][j]=-1;
		
           for(i = 0; i < k; i++) 
                    {
			scanf("%d", &m);
			f[m-1] = 1;
               		}
		printf("%lld\n", solve(0, 0));
	}
	//system("pause");
	return 0;
}



/*Sample input:
5 
1 1 
1 
1 1 
2 
2 1 
1 
3 1 
2 
4 2 
5 7 

Sample output:
1 
0 
2 
3 
2 
*/
