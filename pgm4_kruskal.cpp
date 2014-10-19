#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct edge {
	int a, b, wt;
};

int findset (int a);
void unite (int seta, int setb);

vector<vector<int> > forest;

int main() {
	int n, i, j, t, w, a1, b1, wt1, mine, seta, setb;
	vector<list<int> > nodes, weight;
	list<int>::iterator iter;
	vector<edge*> edgelist, mst;
	edge *edge1;
	bool present;

	cout << "Enter the number of edges: ";
	cin >> n;

	forest.resize(n+1);
	for (i = 1; i < n+1; i++) {
		forest[i].push_back(i);
	}

	nodes.resize(n+1); weight.resize(n+1);
	for (i = 1; i < n+1; i++) {
		cout << "Enter the nodes adjacent to " << i << " along with the edge weight. Terminate with -1:\n";
		cin >> t >> w;
		while (t != -1) {
			nodes[i].push_back(t);
			weight[i].push_back(w);

			present = 0;
			if (i < t) {
				a1 = i; b1 = t; wt1 = w;
			}
			else {
				a1 = t; b1 = i; wt1 = w;
			}
			for (j = 0; j < edgelist.size(); j++) {
				if (edgelist[j]->a == a1 && edgelist[j]->b == b1) {
					present = 1;
					break;
				}
			}
			if (present == 0) {
				edge1 = new edge;
				edge1->a = a1;
				edge1->b = b1;
				edge1->wt = wt1;

				edgelist.push_back(edge1);
			}

			cin >> t >> w;
		}
	}

	for (i = 0; i < edgelist.size() - 1; i++) {
		mine = i;
		for (j = i+1; j < edgelist.size(); j++) {
			if (edgelist[j]->wt < edgelist[mine]->wt) {
				mine = j;
			}
		}
		if (mine != i) {
			edge1 = edgelist[i];
			edgelist[i] = edgelist[mine];
			edgelist[mine] = edge1;
		}
	}

	for (i = 0; i < edgelist.size(); i++) {
		a1 = edgelist[i]->a;
		b1 = edgelist[i]->b;
		wt1 = edgelist[i]->wt;

		seta = findset(a1); setb = findset(b1);
		if (seta != setb)
		{
			mst.push_back(edgelist[i]);
			if (mst.size() == n-1)
				break;
			unite (seta, setb);
		}
	}

	cout << "\nMST:\n";
	for (i = 0; i < mst.size(); i++)
	{
		cout << mst[i]->a << ' ' << mst[i]->b << ' ' << mst[i]->wt << endl;
	}

	return 0;
}

int findset (int a) {
	int i, j;
	for (i = 0; i < forest.size(); i++) {
		for (j = 0; j < forest[i].size(); j++)
			if (forest[i][j] == a)
				return i;
	}
}

void unite (int seta, int setb) {
	int i;
	for (i = 0; i < forest[setb].size(); i++) {
		forest[seta].push_back(forest[setb][i]);
	}
	forest[setb].clear();
}
