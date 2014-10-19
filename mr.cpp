#include<iostream>
using namespace std;
int a[99];
void msort(int,int);
void merge(int,int,int);
 

int main()
{
int n,i,j,temp;

cout<<"\nEnter the number of elements\n";
cin>>n;
for(i=0;i<n;i++)
cin>>a[i];

cout<<"\nIntial Array is :\n";

for(i=0;i<n;i++)
cout<<a[i]<<"  ";


msort(0,n-1);

cout<<"\nSorted Array is :\n";

for(i=0;i<n;i++)
cout<<a[i]<<"  ";
return 0;
}



void msort(int b,int d)
{
int l;
l=(d+b)/2;
if(d>b)
{
msort(b,l);
msort(l+1,d);
merge(b,l,d);
}

}


void merge(int b, int l, int d)
{
int m[99],n[99],f[99],i,j,k;

for(i=0;i<l-b+1;i++)
m[i]=a[b+i];


for(i=l+1;i<=d;i++)
n[i-l-1]=a[i];


/*
for(i=0;i<l-b+1;)
{

for(j=1;j<d-l;)
{*/
k=b;
i=b;
j=l+1;

while(i<=l && j<=d)
{
if( m[i-b]<n[j-l-1] )
{
a[k]=m[i-b];
i=i+1;
k=k+1;
}
else
{
a[k]=n[j-l-1];
j=j+1;
k=k+1;
}

}



while(j<=d)
{
a[k]=n[j-l-1];
k++;
j++;
}

while(i<=l)
{
a[k]=m[i-b];
k++;
i++;
}



}



