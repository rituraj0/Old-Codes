#include<iostream>
using namespace std;
class ab
{
      public:
int a1[33],b1[33],c1[33];
int cont,conti;
int ar,br,cr;

void tower(int,char,char,char);
int  popo(int (&m)[33],int &);//passing int to check which is irts rear///better will be u pass n with refrence
void  push(int (&m)[33],int ,int &);
void done(char ,char );
void disp();

int i,n;
ab()
{int f,cn,ak[999][999];

cin>>f;

     for(cn=0;cn<f;cn++)
     {cin>>ak[cn][0]>>ak[cn][1];
 }
		 
		 
		     for(cn=0;cn<f;cn++)
     { 
	 
		  //cout<<"\nEnter  the number of disk\n";
    n=ak[cn][0];
    //cout<<"\nEnter the nymberbof moves\n";
    cont=ak[cn][1];
    conti=0;
    ar=n-1;
    br=cr=-1;
    
    for(i=0;i<n;i++)
    a1[i]=n-i;
    
    for(i=0;i<n;i++)
    b1[i]=c1[i]=99;
    
    tower(n,'a','c','b');
    disp();
 }   
 } 



};

int ab::popo(int (&m)[33],int &rr)
{int i;
i=m[rr];
rr=rr-1;

return i;
}

void ab::push(int (&m)[33],int n,int &rr)
{
     int i;
rr=rr+1;
m[rr]=n;
}


void ab::tower(int n,char base,char targ,char auxl)
{int k;
    if(conti<cont)
    {
     if(n==1)
     {//cout<<"\nMove  "<<n<<"  from "<<base<<" to "<<targ;
     done(base,targ);
     conti++;
   // disp();
}     
    else
    {
     tower(n-1,base,auxl,targ);
     
    tower(1,base,targ,auxl);
     
         //disp();
     
     tower(n-1,auxl,targ,base);
     }
     
     }
     //else disp();
     }

void ab::done(char base ,char targ)
{
     int k;
     if(base=='a'&&targ=='b')
     { k=popo(a1,ar);
     push(b1,k,br);
     }
     
     
     if(base=='a'&&targ=='c')
     { k=popo(a1,ar);
     push(c1,k,cr);
     }
     
     if(base=='b'&&targ=='a')
     { k=popo(b1,br);
     push(a1,k,ar);
     }
     
     if(base=='b'&&targ=='c')
     { k=popo(b1,br);
     push(c1,k,cr);
     }

     if(base=='c'&&targ=='a')
     { k=popo(c1,cr);
     push(a1,k,ar);
     }
     
     if(base=='c'&&targ=='b')
     { k=popo(c1,cr);
     push(b1,k,br);
     }

}

void ab::disp()
{
     //cout<<"\nNoe displaying content of the ARRAYS\n";
     int i;
     cout<<"\n1: ";
     if(ar>-1)
     cout<<a1[0];
     
     for(i=1;i<ar+1;i++)
     cout<<"|"<<a1[i];
     
      cout<<"\n2: ";
      if(cr>-1)
      cout<<c1[0];
     for(i=1;i<cr+1;i++)
     cout<<"|"<<c1[i];
     
      cout<<"\n3: ";
      //cout<<
      if(br>-1)
      cout<<b1[0];
     for(i=1;i<br+1;i++)
     cout<<"|"<<b1[i];
     
     //cout<<"\n";
     }
     

    int main()
{
    int n;
    ab a;
        return 0;
}



