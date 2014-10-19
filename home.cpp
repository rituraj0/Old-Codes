#include<iostream>
#include<stdio.h>
using namespace std;
int mila=0,no;
struct node{
	int targ;
	node *next;
}*nw,*save,*prev,*de;

struct basen 
{
	node *stat;
	char col;
}a[105];

void inser(int,int);
void dfs(int ,int t);

int main()
{
    int n,i,j,s,t,q;
    int test;
    scanf("%d",&test);
    while(test--)
    {
    scanf("%d%d",&no,&n); 
    for(i=0;i<n;i++)
    {
                    scanf("%d%d",&s,&t);
    inser(s,t);
    inser(t,s);
 }
 
 scanf("%d",&q);
 
 for(i=0;i<q;i++)
 {
  scanf("%d%d",&s,&t);            
 mila=0;
 for(j=0;j<105;j++)
 a[j].col='w';
 
 dfs(s,t);
 
 if(mila)
 printf("YO\n");
 else
 printf("NO\n");
 
}


for(i=1;i<105;i++)
save=a[i].stat;

}

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
 
 
 void dfs(int d,int t)
{
node *cool=new node;
cool=a[d].stat;
if(d==t)
{mila=5;
return;
}
a[d].col='b';
while(cool!=NULL)
{
      if(a[cool->targ].col=='w')
      dfs(cool->targ,t);
      
      cool=cool->next;
      }          
}
