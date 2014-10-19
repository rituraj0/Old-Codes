#include<iostream>
#include<set>
using namespace std;
int main()
{
    typedef std::list<int> l;
    l p;
    
    int n=10;
    int i;
    
    while(n--)
{
    cin>>i;
    p.insert(i);
}

l::const_iterator it;
it=p.begin();

while(it!=p.end())
{
                  cout<<*it<<"  ";
                  }
                  
                  cout<<"\n\n\n";
                  system("pause");
                  return 0;
                  }
