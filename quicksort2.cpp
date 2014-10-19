#include<iostream>
#include<conio.h>
using namespace std;
void swap(int &i,int &j)
{
	int temp;
	temp=i;
	i=j;
	j=temp;
}
int partition(int A[],int l,int h)
{
	int r=A[h];
	int i=l-1;
	for(int j=l;j<h;j++)
	{
		if(A[j]<=r)
		{
			i++;			
			swap(A[j],A[i]);
		}
	}
	swap(A[i+1],A[h]);
	return (i+1);
}
void quicksort(int A[],int l,int h)
{

    if(l<h)
	{
		int p=partition(A,l,h);
		quicksort(A,l,p-1);
		quicksort(A,p+1,h);
	}
}


int main()
{
	int x,i;
	cout<<"Enter n:\n";
	cin>>x;	
	int *A=new int(x);
	//int A[20];
	cout<<"Enter the nos:\n";
    for(i=0;i<x;i++)
	{
		cin>>A[i];
	}
	quicksort(A,0,x-1);
	for(i=0;i<x;i++)
	{
		cout<<A[i]<<" ";
	}getch();
	return 0;
}
