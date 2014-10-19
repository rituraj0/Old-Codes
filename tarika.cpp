#include<iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
 {
	int n, m, r, c, a[100][100],dp[100][100], i, j;
	
	scanf("%d%d%d%d", &n, &m, &r, &c);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			{scanf("%d", &a[i][j]);
                          dp[i][j]=a[i][j]; // :)
                         }

	for(i = r + 1; i <= n; i++)
              dp[i][c] = dp[i-1][c] - a[i][c];

	for(j = c + 1; j <= m; j++) 
              dp[r][j] = dp[r][j-1] - a[r][j];
 
	for(i = r + 1; i <= n; i++)
		for(j = c + 1; j <= m; j++)
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) - a[i][j];

	if(dp[n][m] >= 0) 
           printf("Y %d\n", dp[n][m]);
	else printf("N\n");
	
return 0;
}
