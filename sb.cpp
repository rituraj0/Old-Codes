#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define sz size()

using namespace std;
vector<int>A,B;
void subsets(vector<int> v, vector<int>&ans){
    ans.clear();
    int n=v.sz;
    for(int mask=0;mask<(1<<n);mask++){
        int sum=0;
        for(int j=0;j<v.sz;j++)if(mask&(1<<j))sum+=v[j];
        ans.push_back(sum);
    }
    sort(all(ans));
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int N,X,Y,n,nx;
    cin>>N>>X>>Y;
    vector<int>v(N);
    for(int i=0;i<N;i++)cin>>v[i];
    n=N/2;
    subsets(vector<int>(v.begin(),v.begin()+n),A);
    subsets(vector<int>(v.begin()+n,v.end()),B);
    long long ans=0;
    for(int i=0;i<A.sz;i++){
        int val=A[i];
        int frs=X-val;
        int scd=Y-val;
        int x1=lower_bound(all(B),frs)-B.begin();
        int y1=upper_bound(all(B),scd)-B.begin();
        if(y1>=x1)ans+=(y1-x1);
    }
    cout<<ans<<endl;
    return 0;
}

