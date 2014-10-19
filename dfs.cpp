#include<iostream>
using namespace std;
struct conn
{
conn *next;
int tar;
float wt;
}*nw,*save,*prev,*nd;

struct node
{char col;
conn *targ;
}base[20];

void disp();
void inser(int,int,float);
void dmain();
void dfs(int);



int main()
{
int ed,s,t;
float w;
cout<<"\nEnter the number of edges\n";
cin>>ed;
cout<<"\nPlz enter the info in oredre of source,targ and weight\n";
for(int i=0;i<ed;i++)
{cin>>s>>t>>w;
inser(s,t,w);
}

disp();
dmain();

return 0;
}

void disp()
{
cout<<"Sorce  targ  weight\n";
for(int i=0;i<20;i++)
{save=base[i].targ;
while(save!=NULL)
{
cout<<" "<<i<<"      "<<save->tar<<"     "<<save->wt<<"\n";
save=save->next;
}
}
}


void inser(int st,int t,float w)
{
 nd=new conn;
nd->next=NULL;
nd->wt=w;
nd->tar=t;

save=base[st].targ;
if(save==NULL)
base[st].targ=nd;
else
{while(save!=NULL)
{prev=save;
save=save->next;
}
prev->next=nd;
}
}

void dmain()
{
for(int i=0;i<20;i++)
base[i].col='w';
cout<<"\nNTere the number from whre i want 2 dfs\n";
int n;
cin>>n;
dfs(n);
}

void dfs(int d)
{
save=base[d].targ;
int k=save->tar;;
cout<<d<<"  ";

while(save!=NULL)
{
if(base[k].col=='w')
dfs(k);
}
base[d].col='b';



}

