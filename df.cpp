#include<iostream>
using namespace std;
int mila;
struct node
{
int targ;
node *next;
}*save,*nw,*prev;

struct base
{
char col;
node *stat;
}a[105];

void disp();
void inser(int,int);
void dfs(int s,int t);

void disp()
{
cout<<"Sorce  targ\n";
for(int i=0;i<105;i++)
{save=a[i].stat;
while(save!=NULL)
{
cout<<" "<<i<<"      "<<save->targ<<"     "<<"\n";
save=save->next;
}
}
}

void inser(int s,int t)
{
nw=new node;
nw->next=NULL;
nw->targ=t;

save=a[s].stat;

if(save==NULL)
a[s].stat=nw;
else
{
while(save!=NULL)
{prev=save;
save=save->next;
}

prev->next=nw;
}

}







void dfs(int d,int t)
{
node *cool=new node;
cool=a[d].stat;
if(d==t)
mila=5;
a[d].col='b';
while(cool!=NULL)
{
if(a[cool->targ].col=='w')
dfs(cool->targ,t);
cool=cool->next;
}}


int main()
{
int i,n,s,t,j;


for(i=0;i<105;i++)
a[i].col='w';

int no;
cout<<"\nNodes and edges\n";
//cin>>no>>n;
cin>>n;

for(i=0;i<n;i++)
{cin>>s>>t;
inser(s,t);
inser(t,s);
}
disp();

int q;
cout<<"Quries\n";
cin>>q;

for(i=0;i<q;i++)
{cin>>s>>t;
mila=0;
for(j=0;j<105;j++)
a[j].col='w';

dfs(s,t);

if(mila!=0)
cout<<"YO\n";
else
cout<<"NO\n";

}



return 0;
}



