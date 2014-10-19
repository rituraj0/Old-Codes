#include<iostream>
using namespace std;

struct node{
	int targ;
	node *next;
	float val;
}*nw,*save,*prev;

struct basen 
{
	node *stat;
	char col;
	int pr;
	int d;
}a[100];

int dp[100],fr=0;

void inser(int,int,float);
void disp();
void dfs(int);



void dfs(int u)
{
	int k;

node *kl; 

a[u].col='b';
//cout<<u<<" ";
dp[fr]=u;
fr++;

kl=a[u].stat;

while(kl!=NULL)
{
if( a[kl->targ].col=='w')
dfs(kl->targ);

kl=kl->next;
}

a[u].col='b';
}












int main(){
	int i;
int nd;
cout<<"\nNUmber of nides involved\n";
cin>>nd;

int c,g,j,k;

	for(i=1;i<=nd;i++)
          {   

cout<<"\nNext is \t"<<i<<"\n";   cin>>k;     cin>>c;
             for(j=0;j<c;j++)
               {cin>>g;
		inser(i,g);
}
        //n";       
	}
	disp();	

//Dfs Mahual
for(i=1;i<=nd;i++)
	a[i].col='w';
/*	
for(i=1;i<=nd;i++)
{
if(a[i].col=='w')
dfs(i);
}
*/
cout<<"\nNte the nid e from u Sratring point for DFS path\n";
cin>>i;
int ds;
cout<<"\nDestination\n";
cin>>ds;
dfs(i);
cout<<"\nPath is \n";
i=0;
while(dp[i]!=ds)
{
cout<<dp[i]<<"  ";
i++;
}

cout<<ds<<"\n";


return 0;
}

void inser(int s,int t)
{
	nw=new node;
	
	nw->next=NULL;
	nw->targ=t;
    	
	 if(a[s].stat==NULL)
	 a[s].stat=nw;
	 else
	 {
		 save=a[s].stat;
		 while(save!=NULL)
		 {
			 prev=save;
			 save=save->next;
		 }
		 
		 prev->next=nw;
	 }
	 
 }
 
 
 void disp()
 {
	 int i;
	 cout<<"Enterd data is\n";
	 cout<<"Bas\tTar\tVAl\n";
	 for(i=0;i<100;i++)
	 {
		 if(a[i].stat!=NULL)
		 {
			 save=a[i].stat;
			 
			 while(save!=NULL)
			 {
				 cout<<i<<"\t"<<save->targ<<"\n";
				 save=save->next;
			 }
		 }
	 }
 }
