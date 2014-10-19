#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<vector <int> >forest;
struct edge
{
	int a,b,w;
};
void unite(int x,int y);
int findset(int a);

int main()
{
	int n,x,y,we,a1,a2,mine,seta,setb;
	bool present;
	vector<vector <int> >adj,w;
	vector<edge*>mst,edgelist;
	edge *edge1;
	cout<<"Enter no. of nodes:";
	cin>>n;
	forest.resize(n+1);
	for (int i = 1; i < n+1; i++) {
		forest[i].push_back(i);
	}	
	adj.resize(n+1);
	w.resize(n+1);
	for(x=1;x<=n;x++)
	{
		cout<<"Enter neighbours of "<<x<<"and weight.. -1 -1 to terminate:";
		cin>>y>>we;
		while(y!=-1)
		{
			adj[x].push_back(y);
			w[x].push_back(y);
			if(x>y)
			{
				a1=y;
				a2=x;
			}
			else
			{
				a1=x;
				a2=y;
			}
			present=0;
			for(int i=0;i<edgelist.size();i++)
			{
				if(edgelist[i]->a==a1 && edgelist[i]->b==a2)
				present=1;
			}
			if(present==0)
			{
				edge1->a=a1;
				edge1->b=a2;
				edge1->w=we;
				edgelist.push_back(edge1);
			}
			cin>>y>>we;
		}
	}
	for (int i = 0; i < edgelist.size() - 1; i++) {
		mine = i;
		for (int j = i+1; j < edgelist.size(); j++) {
			if (edgelist[j]->w < edgelist[mine]->w) {
				mine = j;
			}
		}
		if (mine != i) {
			edge1 = edgelist[i];
			edgelist[i] = edgelist[mine];
			edgelist[mine] = edge1;
		}
	}
	for(int i=0;i<edgelist.size();i++)
	{
		a1=edgelist[i]->a;
		a2=edgelist[i]->b;
		we=edgelist[i]->w;
		seta=findset(a1);
		setb=findset(a2);
		if(seta!=setb)
		{
			mst.push_back(edgelist[i]);
			if(mst.size()==n-1)
			break;
			unite(seta,setb);
		}
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
		
		
				
