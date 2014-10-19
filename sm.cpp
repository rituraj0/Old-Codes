#include<iostream>
#include<cstdio>
using namespace std;
#include<set>
int main()
{

long long int n,i,k,x,a[99999],mn=0;
set<long long int> st;

set<long long int>::iterator p,lb,up;

cout<<"cool\n";

scanf("%lld",&n);

for(i=0;i<n;i++)
scanf("%lld",&a[i]);


cout<<"yaha se aage\n";
//scanf("%lld",&k);

//cout<<k;
//mn=1000000;
 
cout<<"cool  o";

for(i=0;i<n;i++)
 {
 x=a[i];
 if(mn>x)
 mn=x;


st.insert(x);
cout<<"cool in";

 lb=st.find(mn);
 up=st.find(x);
 //up--;
 

 st.erase(lb,up);
 
 if(i>=k-1)
 {  
 p=st.begin();
 //printf("%lld  ",*p);
 }

}
return 0;
}


