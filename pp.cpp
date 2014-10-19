#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <deque>

using namespace std;

#define FOR(I,A,B)   for(int I= (A); I<(B); ++I)
#define REP(I,N)     FOR(I,0,N)
#define ALL(A)       (A).begin(), (A).end()
#define DEBUG 0

typedef long long int LL;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int main ()
{
	vector<int> fib( 36, 0 );
	fib[1] = 1;
	fib[2] = 2;
	FOR( i, 3, 36 )
		fib[i] = fib[i-1]+fib[i-2];//, cout << fib[i] << endl;;
	int N;
	vector<int>::iterator pos, prev;
	while( scanf( "%d\n", &N ) )
	{
		if( N == 0 ) break;
		vector<int> ans( N, 0 );
		int X;
		REP( i, N )
		{
			scanf( "%d", &X );
			if( X >= 7465176 ) 
			{
				ans[i] = 9227465;
				continue;
			}
			pos = lower_bound( fib.begin(), fib.end(), X );
			if( *pos == X )
				ans[i] = X;
			else
			{
				prev = pos-1;
				if( abs(*pos-X) > abs(*prev-X) )
					ans[i] = *prev;
				else
					ans[i] = *pos;
			}
		}
		sort( ans.begin(), ans.end() );
		printf( "%d", ans[0] );
		FOR( i, 1, N )
			printf( " %d", ans[i] );
		printf( "\n" );
	}
}
