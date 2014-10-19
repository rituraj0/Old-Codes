#include<cstdio>
#include<vector>
using namespace std;
void nqueen(int i,int n,vector<int> col);
bool check(int i,vector<int> col);
vector<vector <int> >ans;
int ab(int x);
int main()
{
	int n;
	vector<int> col;
	printf("Enter the size of board:");
	scanf("%d",&n);
	col.resize(n);
	nqueen(-1,n,col);
	printf("No. of solutions= %d\n",ans.size());
	for(int i=0;i<ans.size();i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				if(ans[i][j]==k)
				printf("Q");
				else
				printf("-");
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
void nqueen(int i,int n,vector<int> col)
{
	int j;
	if(check(i,col))
	{
		if(i==n-1)
		ans.push_back(col);
		else
		{
			for(j=0;j<n;j++)
			{
				col[i+1]=j;
				nqueen(i+1,n,col);
			}
		}
	}
}
bool check(int i,vector<int> col)
{
	for(int j=0;j<i;j++)
	{
		if(col[i]==col[j] || ab(col[i]-col[j])==(i-j))
		return 0;
	}
	return 1;
}
int ab(int x)
{
	if(x<0)
	return (-x);
	else
	return x;
}
