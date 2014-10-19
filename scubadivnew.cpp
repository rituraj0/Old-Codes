#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
#define FOR(i, first, last) for (int i = first; i < last; ++i)

#define FORZ(i,n) FOR(i,0,n)
int ox[1000], ni[1000], wt[1000], oxy, nit,n;
int arr[200][200];
int main()
{
	int t ;
         cin>>t;
	while(t--) {

       cin>>oxy>>nit>>n;
	
	FORZ(i,n)
	{
             cin>>ox[i]>>ni[i]>>wt[i];
		
	}
	memset(arr, -1, sizeof(arr));
	arr[0][0] = 0;
	int ret = -1;
	for(int i = 0; i < n; i++)
	{
		for(int j = oxy + 21; j >= ox[i] ; j--)
		for(int k = nit + 79; k >= ni[i] ; k--)
		{
			if(arr[j - ox[i]][k - ni[i]] != -1)
			{
				if(arr[j][k] == -1 || arr[j-ox[i]][k - ni[i]] < arr[j][k] - wt[i])
				{	
					arr[j][k] = arr[j - ox[i]][k - ni[i]] + wt[i];
					if(j >= oxy && k >= nit && (ret == -1 || ret > arr[j][k])) ret = arr[j][k];
				}
			}
		}
	}
	printf("%d\n",ret);
	}
	return 0;
}

