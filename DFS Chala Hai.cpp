#include<iostream>
using namespace std;
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
void dfs(int);

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







void dfs(int d)
{
node *cool=new node;
cool=a[d].stat;
cout<<d<<"  ";
a[d].col='b';

while(cool!=NULL)
{
if(a[cool->targ].col=='w')
dfs(cool->targ);

cool=cool->next;
}

a[d].col='b';

}


int main()
{
int i,n,s,t;


for(i=0;i<105;i++)
a[i].col='w';

cout<<"\nNumbet of edges\n";
cin>>n;

for(i=0;i<n;i++)
{cin>>s>>t;
inser(s,t);
inser(t,s);
}
disp();

cout<<"\nStarting node\n";
cin>>n;
dfs(n);
return 0;
}



