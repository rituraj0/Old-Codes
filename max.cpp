#include<iostream>
using namespace std;
long long int  a[500000];
int main()
{
    int i;
    a[0]=0;
    for(i=1;i<500000;i++)
    a[i]=a[i-1]+i;
    
    cout<<a[499999];
    system("pause");
    return 0;
}
