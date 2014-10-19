#include <iostream>
using namespace std;

int main() 
{
	int n, W, i, j, k;
	cout << "Enter the number of items: ";
	cin >> n;
	
	int v[n+1], w[n+1];
	cout << "Enter the value for each item:\n";
	for (i=1; i<n+1; i++)
		cin >> v[i];
	cout << "Enter the weight of each item:\n";
	for (i=1; i<n+1; i++)
		cin >> w[i];

	cout << "Enter the maximum weight of the knapsack: ";
	cin >> W;

	int value[n+1][W+1], keep[n+1][W+1];

	for (j=0; j<W+1; j++)
	value[0][j] = 0;
	
	for (i=1; i<n+1; i++)
	{
		for (j=0; j<W+1; j++)
		{
			if (w[i] <= j)
			{
				if ( v[i]+value[i-1][j-w[i]] > value[i-1][j])
				{
					value[i][j] = v[i]+value[i-1][j-w[i]];
					keep[i][j] = 1;
				}
				else
				{
					value[i][j] = value[i-1][j];
					keep[i][j] = 0;
				}
			}
			else
			{
				value[i][j] = value[i-1][j];
				keep[i][j] = 0;
			}
		}
	}

	cout << "\nMaximum value: " << value[n][W] << endl;
	cout << "\nItems taken: ";
	k = W;
	for (i=n; i>0; i--)
	{
		if (keep[i][k] == 1)
		{
			cout << i << ' ';	
			k = k - w[i];
		}
	}
	cout << endl;

	return 0;
}
