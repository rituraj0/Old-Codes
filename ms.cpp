#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
int main()
{

long long int i,j,n,mn,k,x,a[1000000]={0},cn;
multiset<long long int> st;

multiset<long long int>::iterator lb,up,p,sv;


scanf("%lld",&n);

for(i=0;i<n;i++)
scanf("%lld",&a[i]);

scanf("%lld",&k);


for(i=0;i<n;i++)
 {
 
 x=a[i];

  st.insert(x);

  lb=st.begin();
  up=st.find(x); 

  sv=up;
  
  while( (*sv)>=x && sv!=lb)
   sv--;
  
  st.erase(lb,sv);


   if(i==k-1)
  {
   p=st.end();
  p--;
 printf("%lld ",*p);
  }


  if(i>k-1)//matlab pahla window complete ho gaya uske bad
  {  

  x=a[i-k];
  p=st.find(x);
  if(p!=st.end() )
  st.erase(p);

  p=st.end();
  p--;
  printf("%lld ",*p);
  }

 }//end for
printf("\n");
return 0;
}


/*5
5 4 5 2 5
3
5 2 5 */
