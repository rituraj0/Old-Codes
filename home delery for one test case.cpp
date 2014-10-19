#include<iostream>
using namespace std;
//Note bad me printf and scanf ka use karenge bcz to many inputs and outputs
int mila=0,no;
struct node{
	int targ;
	node *next;
}*nw,*save,*prev;

struct basen 
{
	node *stat;
	char col;
}a[105];

void inser(int,int);
void disp();
void dfs(int ,int t);/*t to be searcehed*/ //Dekh bhai agar o waha mil gaya to wahi print kara denge otherwise ek global varialble ka use karke

int main()
{
    int n,i,j,s,t,q;
    
    cin>>no>>n;;//NUmber of inputes
    //dekh bhai ek bar ke bad sabko NULL karna hoga  otherwise NExt wale me ulta aaega hi 
    
    for(i=0;i<n;i++)
    {cin>>s>>t;
    inser(s,t);
    inser(t,s);
 }
 
 disp();
 
 cin>>q;
 
 for(i=0;i<q;i++)
 {
              
 cin>>s>>t;
 //cout<<s<<t<<"  _ ";
 mila=0;
 for(j=0;j<105;j++)
 a[j].col='w';
 
 dfs(s,t);
 
 if(mila!=0)
 cout<<"Yo\n";
 else
 cout<<"NO\n";
 
}


for(i=1;i<105;i++)
a[i].stat=NULL;
cout<<"\nSuccesfilly deleted\n";
system("pause");
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
mila=5;
a[d].col='b';
while(cool!=NULL)
{
      if(a[cool->targ].col=='w')
      dfs(cool->targ,t);
      
      cool=cool->next;
      }          
}



 void disp()
 {
	 int i;
	 cout<<"Enterd data is\n";
	 cout<<"Bas\tTar\n";
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
