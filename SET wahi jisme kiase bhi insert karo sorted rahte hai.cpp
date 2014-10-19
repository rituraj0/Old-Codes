#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<set>
using namespace std;
int main()
{
    set<int> v;
    int n=10;
   int c;
    while(n--)
    {
            cin>>c;
            v.insert(c);
            v.insert(c);
            
    }
             /*          
              while(!v.empty())
              {
                 cout<<v.front();
                  v.pop_front();              
                  } */    
                  
          set<int>::iterator p;
          p=v.begin();
          while(p!=v.end())
          {  
                           cout<<*p<<" ";
                           p++;
                           }                 
                   
                   
                   cout<<"\n\n";
                   system("pause");                    
            return 0;
            }
