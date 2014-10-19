//{rim algoritjm
#include<iostream>

using namespace std;
int nd;
struct prio
{int  key;
bool used;
}vr[99];

struct node{
	int targ;
	node *next;
	int val;
}*nw,*save,*prev;

struct basen 
{
	node *stat;
	int bap;
}a[100];

void inser(int,int,int);
void disp();
int min();





int main()
{cout<<"Here 0 se start hogan\n";
int ed,i,j,k,u,v,s,t,r;
cout<<"Enter he nuber of nodes\n";
cin>>nd;
cout<<"Enerthe number od EGDEs\n";
cin>>ed;
for(i=0;i<ed;i++)
{cin>>s>>t>>v;
inser(s,t,v);
inser(t,s,v);
}

disp();

cout<<"\nNEe teh what u want to be a ROOT of the tree\n";
cin>>r;
//Now clrs suru
for(i=0;i<=nd;i++)
{vr[i].key=99999;
vr[i].used=false;
a[i].bap=-1;//Koe nahi hai abhi tak iska baap
}



vr[r].key=0;
k=nd;
node *lo=new node;
while(k--)
{
   u=min();
   lo=a[u].stat;
   
   while(lo)
   {v=lo->targ;
   
   if(vr[v].used==false && lo->val<vr[v].key )
   {a[v].bap=u;
   vr[v].key=lo->val;
  }
  
  lo=lo->next;
}//End INNEr While

}//End outer while

cout<<"Beta   BAap\n";
for(i=0;i<=nd;i++)
cout<<i<<"    "<<a[i].bap<<endl;


cin>>i;
return 0;
}




void inser(int s,int t,int v)
{
	nw=new node;
	
	nw->next=NULL;
	nw->targ=t;
	nw->val=v;
	
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
				 cout<<i<<"\t"<<save->targ<<"\t"<<save->val<<"\n";
				 save=save->next;
			 }
		 }
	 }
 }
 
 
 int min()
 {
     int i,in,m=99999;
     for(i=0;i<=nd;i++)
     {
      if(vr[i].used==false)//matlab used nahi hhua hai abhi tak
      if(vr[i].key<m)
      {m=vr[i].key;
      in=i;
      }
      
      }
      vr[in].used=true;//Chalo mane 
      return in;
      
      }
     
