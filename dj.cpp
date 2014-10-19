#include<iostream>
using namespace std;
int nd;
struct node
{int tar;//Node to be introduced
int wt;//Weight asspcoietde with it
node *next;//Next Node
}*nw,*save,*prev;

struct head
{
bool used;//Whterhge it is used or nt
int key;//Key for Relax
node *stat;//Staring 
int bap;//Baaap
}a[99];

void inser(int,int,int);
int min();
void disp();


int main()
{

int i,j,s,t,w,ed,u,v;
cout<<"\nBhai a zero basis par liya gya hai\n\n\n";
cout<<"\nEnter the number od nodes\n";
cin>>nd;
cout<<"\nEnter the num ber of edges\n";
cin>>ed;
for(i=0;i<ed;i++)
{cin>>s>>t>>w;
inser(s,t,w);
//inser(t,s,w);
}

disp();

cout<<"\nNEter the starting point\n";
cin>>s;

for(i=0;i<nd;i++)
{a[i].bap=-1;
a[i].key=99999;
}

a[s].key=0;
//That was our intilization call

//Nor Distra starts

for(i=0;i<nd;i++)
{
u=min();
save=a[u].stat;

while(save)
{
v=save->tar;

if(a[v].key>a[u].key+save->wt)
{a[v].key=a[u].key+save->wt;
a[v].bap=u;
}

save=save->next;
}//end while

}//End for

cout<<"Beta  Baaap\n";
for(i=0;i<nd;i++)
cout<<i<<"  "<<a[i].bap<<endl;

return 0;
}



void inser(int st,int t,int w)
{
 node *nd=new node;
nd->next=NULL;
nd->wt=w;
nd->tar=t;

save=a[st].stat;
if(save==NULL)
a[st].stat=nd;
else
{while(save!=NULL)
{prev=save;
save=save->next;
}
prev->next=nd;
}
}


void disp()
{
cout<<"Sorce  targ  weight\n";
for(int i=0;i<20;i++)
{save=a[i].stat;
while(save!=NULL)
{
cout<<" "<<i<<"      "<<save->tar<<"     "<<save->wt<<"\n";
save=save->next;
}
}
}


int min()
{

int m=99999,in=0,i;

for(i=0;i<=nd;i++)
{
if(a[i].used==false)
if(a[i].key<m)
{m=a[i].key;
in=i;
}

}

a[in].used=true;
return in;
}


/*Input**

5
9
0 1 1            
1 3 2
3 4 1
4 2 3
2 0 2
0 3 2 
0 4 10
3 2 4
3 4 6




5
10
0 1 10
0 3 5
1 2 1
1 3 2
2 4 4
3 4 2
3 2 9
3 1 3
4 2 6
4 0 7


*/
