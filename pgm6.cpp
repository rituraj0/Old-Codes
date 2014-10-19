#include <iostream>
#include <stack>
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
	stack <int> stk;
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

	cout << "Enter the node to start DFS from: ";
	cin >> start;

	cout << "\nDFS: ";
	stk.push (start-1);
	visited [start-1] =1;
	while (!stk.empty())
	{
		start = stk.top();
		stk.pop();
		cout << start+1 << ' ' ;
		for (tnode = (vertices+start)->next; tnode != NULL; tnode = tnode->next)
		{
			if (visited[tnode->data] == 0)
			{
				visited[tnode->data] = 1;
				stk.push (tnode->data);
			}
		}
	}
	cout << endl;
	 
	return 0;	
}
