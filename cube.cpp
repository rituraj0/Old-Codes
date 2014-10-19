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

bool isPrime( int N )//pahle waha tak ka prime chhant lo
{
	for( int i=3; i*i<=N; i+=2 )
		if( N % i == 0 )
			return false;
	return true;
}

int main ()
{
	vector<int> primes;
	primes.push_back( 2 );
	for( int i=3; i<101; i+=2 )
		if( isPrime( i ) )
			primes.push_back( i );//sab prime to ise thus karke 
	vector<bool> notCubeFree( 1000001, false );
	int size = primes.size();
	REP( i, size )
	{
		int triple = primes[i]*primes[i]*primes[i];
		for( int j=1; ; ++j )
		{
			int X = j*triple;
			if( X <= 1000000 )
				notCubeFree[X] = true; 
			else
				break;
		}
	}
	/*
	vector<int> cubeFree;
	FOR( i, 1, 1000001 )
		if( !notCubeFree[i] )
			cubeFree.push_back( i );
	*/
	vector<int> deduct( 1000001, 0 );
	FOR( i, 1, 1000001 )
	{
		deduct[i] = deduct[i-1];
		if( notCubeFree[i] )
			++deduct[i];
	}

	// begin reading input
	int T;
	scanf( "%d\n", &T );
	REP( i, T )
	{
		int N;
		scanf( "%d\n", &N );
		printf( "Case %d: ", i+1 );
		if( notCubeFree[N] )
			printf( "Not Cube Free\n" );
		else
		{
			/*
			vector<int>::iterator it = lower_bound( cubeFree.begin(), cubeFree.end(), N );
			cout << int(it-cubeFree.begin())+1 << endl;
			*/
			printf( "%d\n", N-deduct[N] +6);
		}
		printf( "\n" );
	}

}


