#include<iostream>
using namespace std;
int main()
{
    int a[99],i,j,temp,n,x;

cout<<"\nNuber of entries\n";
cin>>n;
for(i=0;i<n;i++)
cin>>a[i];

for(j=1;j<n;j++)
{x=a[j];

for(i=j-1;i>=0 &&a[i]>x;i--)
a[i+1]=a[i];

a[i+1]=x;
}
cout<<"Sorted array is \n";
for(i=0;i<n;i++)
cout<<a[i]<<" ";

cin>>i;
return 0;
}
