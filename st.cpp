#include<iostream>
#include<set>
#include<cstdio>
using namespace std;

int main()
{
int i,n,k,x;
multiset<int> st;
multiset<int>::iterator p,a,b;

for(i=0;i<7;i++)
{scanf("%d",&k);
st.insert(k);
}


p=st.begin();

while(p!=st.end())
{
cout<<"   "<<*p;
p++;

}

cout<<endl;
cout<<"Lower bound\n";
scanf("%d",&k);
p=st.lower_bound(k);
cout<<*p<<"  ";
p++;
cout<<*p<<"  "<<endl;

cout<<"For upper bound\n";
scanf("%d",&x);
p=st.upper_bound(x);
if(p==st.end() )
p--;
cout<<*p<<endl;

/*a=st.find(k);
b=st.find(x);

st.erase(a,b);

p=st.end();

while(p!=st.begin())
{
p--;
cout<<"   "<<*p;

}
*/





return 0;
}
