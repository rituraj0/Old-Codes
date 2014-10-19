#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;

int n,i,w,W;
int weight[50],v[50];
int C[50][50];

void knapsack(int n,int W)
{
for(i = 1; i <= n; i++)
	C[i][0] = 0;

for(i=1;i<=n;i++)
{
	  for(w=0;w<=W;w++)
		  if(weight[i]<=w)						   //item can be put in knapsack
			 if(v[i]+C[i-1][w-weight[i]]>C[i-1][w])
		  C[i][w]=v[i]+C[i-1][w-weight[i]];
	else
		  C[i][w]=C[i-1][w];
		 else
			 C[i][w]=C[i-1][w];			 // w[i]>w
}
cout<<C[i][w];

} 

int main()
{
 cout<<"Enter number of items";
 cin>>n;
 cout<<"Enter Max Weight: ";
 cin>>W;
 cout<<"Enter individual weights: ";
 for(i=0;i<n;i++)
 {
  cin>>weight[i];
 }
 cout<<"Enter price of each item: ";
	for(i=0;i<n;i++)
 {
  cin>>v[i];
 }
knapsack(n,W);
getch();
return 0;
}


 
