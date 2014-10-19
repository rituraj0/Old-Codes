#include<iostream>
using namespace std;
int main()
{
int n,i,j,temp,x;

cout<<"\nEnter the number of elements\n";
cin>>n;

int a[99];
for(i=0;i<n;i++)
cin>>a[i];

cout<<"\nIntial Array is :\n";

for(i=0;i<n;i++)
cout<<a[i]<<"  ";

for(j=1;j<n;j++)
{
x=a[j];
i=j-1;
while(i>=0 && a[i]>x) 
{
a[i+1]=a[i];
i=i-1;
}

a[i+1]=x;
}


cout<<"\nSorted Array is :\n";

for(i=0;i<n;i++)
cout<<a[i]<<"  ";
return 0;

}
