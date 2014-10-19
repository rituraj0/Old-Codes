#include<iostream>
#include<cstdio>
using namespace std;

i64 solve(int pos, int open) {
	if(open < 0) return 0; // invalid
	if(pos == n) return open == 0; // must for being valid
	int &ret = dp[pos][open];
	if(ret != -1) return ret;
	if(f[pos]) return ret = solve(pos+1, open+1); // must put a [ here
	return ret = solve(pos+1, open+1) + solve(pos+1, open-1); // try [ and ] both
}

int main() {
	
	int t, k, m, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &k);
		n <<= 1;//rituraj style of  multiplying by 2
		CLR(f); SET(dp);
		for(i = 0; i < k; i++) {
			scanf("%d", &m);
			f[m-1] = 1;
		}
		printf("%lld\n", solve(0, 0));
	}
	//system("pause");
	return 0;
}
