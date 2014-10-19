#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
typedef long long int lg;
using namespace std;
int main()
{

 lg test,n,sm,i,j,x;
  
 scanf("%lld",&n);
 
 while(n!=0)
  {
    vector<lg> cp,cs;//cp is candy_price  cs is claas strnehht
   
     

      for(i=0;i<n;i++)
      { scanf("%lld",&x);
           cs.push_back(x);
       }

       for(i=0;i<n;i++)
      { scanf("%lld",&x);
           cp.push_back(x);
       }

         sort(cs.begin(),cs.end());
     
           sort(cp.begin(),cp.end());

              sm=0;
           for(i=0;i<n;i++)
              sm+=cs[i]*cp[n-1-i];

             printf("%lld\n",sm);
      scanf("%lld",&n);
   }

return 0;
} 

        
