#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;
int n,a,b,c,d;
vector<int> nums[4],X[2];
int search_b(vector<int> &nums, int n)
{
    int start=0,end=nums.size()-1;
    int mid;
    while(start<end)
    {
        mid=(start+end)/2;
        if(nums[mid]<n)
        {
            start=mid+1;
            continue;
        }
        if(nums[mid]>=n)
        {
            end=mid;
            continue;
        }
    }
    return end;
}
int search_b2(vector<int> &nums, int n)
{
    int start=0,end=nums.size()-1;
    int mid;
    int ans=0;
    while(start<=end)
    {
        mid=(start+end)/2;
        if(nums[mid]<n)
        {
            start=mid+1;
            continue;
        }
        if(nums[mid]>n)
        {
            end=mid-1;
            continue;
        }
        ans++;
        for(int i=mid-1;i>=0 && nums[i]==nums[mid];i--)ans++;
        for(int i=mid+1;i<nums.size() && nums[i]==nums[mid];i++)ans++;
        return ans;

    }
    return 0;
}
int getans()
{
    int max=0,min=0;
    max=-X[1][0];min=-X[1][n*n-1];
    int start=search_b(X[0],min);
    int ans=0;
    for(int j=start;j<n*n && X[0][j]<=max;j++)
    {
        int x=search_b2(X[1],-X[0][j]);
        ans+=x;
    }
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        nums[0].push_back(a);
        nums[1].push_back(b);
        nums[2].push_back(c);
        nums[3].push_back(d);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            X[0].push_back(nums[0][i]+nums[1][j]);
            X[1].push_back(nums[2][i]+nums[3][j]);
        }
    }
    sort(X[0].begin(),X[0].end());sort(X[1].begin(),X[1].end());
    printf("%d\n",getans());
}

