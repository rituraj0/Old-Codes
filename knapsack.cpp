#include <iostream>
#include <vector>
#include<conio.h>

using namespace std;

int main() {
	int n, W, i, j, k;
	vector<int> p, w;
	vector<vector<int> > value;
	vector<vector<bool> > keep;

	cout << "Enter the number of items: ";
	cin >> n;
	
	p.resize(n+1); w.resize(n+1);
	cout << "Enter the price of each item: \n";
	for (i = 1; i < n+1; i++) {
		cin >> p[i];
	}
	cout << "Enter the weight of each item: \n";
	for (i = 1; i < n+1; i++) {
		cin >> w[i];
	}
	cout << "Enter the maximum weight of the knapsack: ";
	cin >> W;

	value.resize(n+1); keep.resize(n+1);
	for (i = 0; i < n+1; i++) {
		value[i].resize(W+1);
		keep[i].resize(W+1);
	}	

	i = 0;
	for (j = 0; j < W+1; j++) {
		value[i][j] = 0;
		keep[i][j] = 0;
	}

	for (i = 1; i < n+1; i++) {
		for (j = 0; j < W+1; j++) {
			if (w[i] <= j) {
				if ( (p[i]+value[i-1][j-w[i]]) >= (value[i-1][j]) ) {
					value[i][j] = p[i]+value[i-1][j-w[i]];
					keep[i][j] = 1;
				}
				else {
					value[i][j] = value[i-1][j];
					keep[i][j] = 0;
				}
			}
			else {
				value[i][j] = value[i-1][j];
				keep[i][j] = 0;
			}
		}
	}

	cout << "Maximum price = " << value[n][W] << endl;

	cout << "Items that can be taken: ";
	k = W;
	for (i = n; i > 0; i--) {
		if (keep[i][k] == 1) {
			cout << i << ' ';
			k = k - w[i];
		}
	}
	cout << endl;
getch();
	return 0;	
}
