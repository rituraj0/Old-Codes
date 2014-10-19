#include<iostream>
using namespace std;
int main()
{
int n,i,j,temp;

cout<<"\nEnter the number of elements\n";
cin>>n;

int a[99];
for(i=0;i<n;i++)
cin>>a[i];

cout<<"\nIntial Array is :\n";


cout<<"\nSorted Array is :\n";

for(i=0;i<n;i++)
cout<<a[i]<<"  ";

return 0;
}
