#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node
{
	int data;
	node *next;
};

int main()
{
	int n,i,j,ip, start;
	node *tnode,*pnode;
	queue <int> que;
	vector <bool> visited;

	cout << "Enter the number of nodes: ";
	cin >> n;
	
	node *vertices = new node[n];
	visited.resize (n);

	for (i=0; i<n; i++)
	{
		(vertices+i)->data = i;
		(vertices+i)->next = NULL;
		visited[i] = 0;
	}	

	for (i=0; i<n; i++)
	{
		pnode = vertices+i;
		
		cout << "Enter the vertices adjacent to "<<i+1<<". End with -1: ";
		cin >> ip;		

		while (ip!=-1)
		{
			tnode = new node;
			
			tnode->data = ip-1;
			tnode->next = NULL;			
			pnode->next = tnode;
			
			pnode = tnode;
	
			cin >> ip;
		}
	}

	cout << "Enter the node to start BFS from: ";
	cin >> start;

	cout << "\nBFS: ";
	cout << start << ' ';
	visited [start-1] = 1;
	que.push (start-1);

	while (!que.empty())
	{
		start = que.front();
		que.pop();
		for (tnode = (vertices+start)->next; tnode != NULL; tnode = tnode->next)
		{
			if (visited[tnode->data] == 0)
			{
				cout << (tnode->data + 1) << ' ';
				visited[tnode->data] = 1;
				que.push (tnode->data);
			}
		}
	}
	cout << endl;
	 
	return 0;	
}
