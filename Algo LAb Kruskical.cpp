/*BHai a kruscila algorithm for minimun spanning tree hai*/

#include<iostream>
using namespace std;
struct node
{
       int mem;
       node *next;
       }*save,*prev,*nw;
       
struct head
{
  node *next;
}a[99];

struct edge
{int s;
int t;
int wt;
bool sl;
}e[99];

int findset(int);
void unun(int,int);
int nd;

int main()
{
    int i,j,ed;
    edge temp;
    
    cout<<"\nEnter the number of nodes\n";
    cin>>nd;
    
    for(i=0;i<=nd;i++)
    {
      nw=new node;
       nw->mem=i;
       nw->next=NULL;
       
       
       a[i].next=nw;
       }              
    
    cout<<"number of Edgges\n";
    cin>>ed;
    for(i=0;i<ed;i++)
    {cout<<"Sor  tarf  weit\n";
    cin>>e[i].s>>e[i].t>>e[i].wt;
    e[i].sl=false;
}
cout<<"YAh acoo hai\n";

//Now sortin the edged using their weight as key\n";
for(i=0;i<ed;i++)
for(j=i+1;j<ed;j++)
{if(e[i].wt>e[j].wt)
{temp=e[i];
e[i]=e[j];
e[j]=temp;
}
}
//chalo soting ka kam khatam
int ur,vr;
for(i=0;i<ed;i++)
{
   ur=findset(e[i].s );
   vr=findset(e[i].t);
   if(ur!=vr)
   {unun(e[i].s,e[i].t);
   e[i].sl=true;
}

}
//Now printing the edges

for(i=0;i<ed;i++)
if(e[i].sl)
cout<<e[i].s<<"  "<<e[i].t<<endl;

cin>>i;           

return 0;
}

void unun(int u,int v)
{
    
    int ur,vr;
     ur=findset(u);
      vr=findset(v);
     
     save=a[ur].next;//bai iske matlab b ke bande ko assif=gn kar rahe hai
     
     while(save)
     {prev=save;
     save=save->next;
     }
     
     prev->next=a[vr].next;//chalo ab sabse last wale ko assign kar dia
     
     a[vr].next=NULL;
     
     }
     
     
  int findset(int u)
  {
int i;
      for(i=0;i<=nd;i++)
      {
      save=a[i].next;
       while(save)
       {
       if(save->mem==u)
       return i;
       else
       save=save->next;
       }
       
       }//ebd for
       
       }  
