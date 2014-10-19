/*we do a DFS search. When a DFS call on a child node returns, we check if the child and the parent are both unselected. If yes, we select the parent node.
After all the DFS finishes (we traverse the tree), those selected nodes form the minimum vertex cover. The cost is O(N).
The pseudo code is as follow:
void min_vertex_cover(TreeNode *root)
{
   if(isLeaf(root)) return; 

   for(int i=0; i<root->num_of_children; i++)
   { 
        min_vertex_cover(root->children[i]);

        if(!root->selected && !root->children[i]->selected)
               root->selected = true;
         
   }
}*/

#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
struct node
{
vector<int> list;
}base[10005];

bool selected[10005],visited[10005];


void vertex(int u)
{

 int i=0,j,x,y;
 
 if(selected[u])
  return;

 x=base[u].list.size();

visited[u]=true;
 
 for(i=0;i<x;i++)
 {
      y=base[u].list[i];
     if(!visited[y])
      vertex(y);
   
      bool partselected=false;
       
    for(j=0;j<x;j++)
        if( selected[base[u].list[j] ] )
            partselected=true;  

         if(!selected[u] && (!partselected) )
           selected[u]=true;
  }

   if(x==1)
 return;

}

int main()
{
int n,i,j,mx,x,in,u,v,cn;
cin>>n;//number of edges so number of vertices is n+1

for(i=1;i<=n;i++)
{
 cin>>u>>v;
 base[u].list.push_back(v);
 base[v].list.push_back(u);
}

for(i=0;i<10005;i++)
visited[i]=selected[i]=false;
 


cout<<"   ~~~~  \n";


for(i=1;i<=n+1;i++)
  {
   x=base[i].list.size();
   for(j=0;j<x;j++)
     cout<<base[i].list[j]<<"  ";
   
    cout<<endl;
 }

mx=-1,in=-1;

cout<<"   ^^^  \n";

 for(i=1;i<=n+1;i++)
 {
  x=base[i].list.size();
   if(x>=mx)
    {mx=x;
      in=i;
    }
 }

cout<<" in  is "<<in<<"   -<"<<endl;
vertex(in);


cout<<"Vertex pura\n";
cn=0;


for(i=1;i<=n+1;i++)
    if(selected[i])
     cn++;

printf("cn is  %d\n",cn);

return 0;
}





