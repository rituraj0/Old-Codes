#include <iostream>
#include <vector>

#include <list>

using namespace std;

int main() {
	vector<list<int> > adjlist;
	vector<vector<int> > adjmatrix;
	list<int>::iterator iter;
	int n, i, j, t;
		
	cout << "Enter the number of nodes: ";
	cin >> n;
	
	adjlist.resize(n+1);
	adjmatrix.resize(n+1);

	for (i = 1; i < n+1; i++) {
	
		adjmatrix[i].resize(n+1);
		for (j = 1; j < n+1; j++) adjmatrix[i][j] = 0;
		
		cout << "Enter the adjlist adjacent to " << i << ". Terminate with -1: ";
		cin >> t;
		while (t != -1) {
			adjlist[i].push_back(t);
			adjmatrix[i][t] = 1;
			cin >> t;
		}
		
	}

	cout << "\nAdjacency List:\n";
	for (i = 1; i < n+1; i++) {
		cout << i << ": ";
		for (iter = adjlist[i].begin(); iter != adjlist[i].end(); ++iter) {
			cout << " -> " << *iter;
		}
		cout << endl;
	}

	cout << "\nAdjacency Matrix:\n";
	
	cout << ' ';
	for (i = 1; i < n+1; i++) {
		cout << ' ' << i;
	}
	cout << endl;
	for (i = 1; i < n+1; i++) {
		cout << i << ' ';
		for (j = 1; j < n+1; j++) {
			cout << adjmatrix[i][j] << ' ' ;
		}
		cout << endl;
	}
	
	return 0;
}
