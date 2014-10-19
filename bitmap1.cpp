#include<iostream>
#include<vector>
#include<queue>
struct pixel
{
	int i,j;
};
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		int ansGrid[182][182];
		int grid[182][182];
		vector<struct pixel> whitePixels;

		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				char ch;
				cin>>ch;
				if(ch=='\n')
					cin>>ch;
				grid[i][j]=ch-'0';
				if(grid[i][j]==0)
					ansGrid[i][j]=10000;
				else
				{
					ansGrid[i][j]=0;
					struct pixel x={i,j};
					whitePixels.push_back(x);
				}
			}

		queue <struct pixel> bfs;
		for(int i=0;i<whitePixels.size();i++)
		bfs.push(whitePixels[i]);

		while(!bfs.empty())
		{
			struct pixel x=bfs.front();
			bfs.pop();
			if((x.i+1)<n && ansGrid[x.i+1][x.j]>ansGrid[x.i][x.j]+1)
			{
				ansGrid[x.i+1][x.j]=ansGrid[x.i][x.j]+1;
				struct pixel y={x.i+1,x.j};
				bfs.push(y);
			}
			if((x.i-1)>=0 && ansGrid[x.i-1][x.j]>ansGrid[x.i][x.j]+1)
			{
				ansGrid[x.i-1][x.j]=ansGrid[x.i][x.j]+1;
				struct pixel y={x.i-1,x.j};
				bfs.push(y);
			}
			if((x.j+1)<m && ansGrid[x.i][x.j+1]>ansGrid[x.i][x.j]+1)
			{
				ansGrid[x.i][x.j+1]=ansGrid[x.i][x.j]+1;
				struct pixel y={x.i,x.j+1};
				bfs.push(y);
			}
			if((x.j-1)>=0 && ansGrid[x.i][x.j-1]>ansGrid[x.i][x.j]+1)
			{
				ansGrid[x.i][x.j-1]=ansGrid[x.i][x.j]+1;
				struct pixel y={x.i,x.j-1};
				bfs.push(y);
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout<<ansGrid[i][j]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
