#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int main() {
	int n, i, t, j, root, node;
	vector<vector<int> > nodes;
	list<int>::iterator iter;
	vector<bool> visited;
	queue<int> Q;

	cout << "Enter the number of nodes: ";
	cin >> n;

	nodes.resize(n+1); visited.resize(n+1);
	for (i = 1; i < n+1; i++) {
		cout << "Enter the nodes adjacent to " << i << ". Terminate with -1: ";
		cin >> t;
		while (t!=-1) {
			nodes[i].push_back(t);
			cin >> t;
		}
		visited[i] = 0;
	}

	cout << "\nEnter the node to start BFS from: ";
	cin >> root;

	cout << "\nBFS: ";
	cout << root << ' ';
	visited[root] = 1;
	Q.push(root);

	while (!Q.empty()) {
		node = Q.front();
		Q.pop();

		for (i=0; i<= nodes[node].size(); ++i) {
			if ( visited[ nodes[node][i] ] == 0) {
				visited[ nodes[node][i] ] = 1;
				cout << nodes[node][i] << ' ';
				Q.push(i);
			}
		}
	}

	cout << endl;

	return 0;
}
