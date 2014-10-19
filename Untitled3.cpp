#include<iostream.h>
#include<conio.h>
void disp();
struct node
{
       int info;
       node *next,*prev;
       }*strt,*save,*nw,*nptr,*here;
       
       
       
int main()
{int i,po,l=1,j;
    char ch='y';
    while(ch=='y')
    {
    cout<<"Inter the positon u want to insert\n";
    cin>>po;
    cout<<"\nEnyer the infoart of the node \n";
    cin>>i;
    nw=new node;
    nw->next=NULL;
    nw->prev=NULL;
    nw->info=i;
    
    save=strt;
    while(save!=NULL)
    {
                     save=save->next;
                     l++;
                     }
    
    save=strt;
    
    if(po<1||po>l+1)
    cout<<"\nINvalid chois of POsition\n";
    else if(strt==NULL)
    strt=nw;
    else if(po==1)
    {
         nw->next=save;
         save->prev=nw;
         strt=nw;
         }
         else if(po==l+1)
         {
              while(save->next!=NULL)
              {save=save->next;
              }
              save->next=nw;
              nw->prev=save;
              }
    else
    {
        for(j=1;j<po;j++)
        save=save->next;
        
        here=save->next;
        
        nw->next=here;
        here->prev=nw;
        
        save->next=nw;
        nw->prev=save;
        }
        
       disp(); 
        cout<<"\nYo conti ue Press y\n";
        cin>>ch;
        }
        
        
        getch();
        }
        
        
        void disp()
        { cout<<"\nThe list is\n";
          save=strt;
             while(save!=NULL)
             {
            cout<<save->info<<"\n";
            save=save->next;
            }
            }
        
    
