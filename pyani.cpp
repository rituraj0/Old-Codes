#include<iostream>
#include<cstdio>
#include<set>
#include<cstdlib>
using namespace std;
typedef long long int lg;

int main()
{

 lg n,i,k,uq;

 multiset<lg> st;

 scanf("%lld",&n);
  
  for(i=0;i<n;i++)
 {
   scanf("%lld",&k);
 
  st.insert(k);

 }


 multiset<lg>::iterator p;

for(p=st.begin();p!=st.end();p++)
    if( st.count(*p)==1)
       {uq=*p;break;
        }

printf("%lld\n",uq);

return 0;
}


