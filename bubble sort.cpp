#include<iostream.h>
#include<conio.h>
class ab
{public:
      int a[20];
      int n,i,j;
       void sort();
      ab()
      {
          cout<<"\nNeter the nimber of arrays\n";
          cin>>n;
          cout<<"\nNetre the interger\n";
          for(i=0;i<n;i++)
          cin>>a[i];
          cout<<"\nIts what u hav enterd\n";
           for(i=0;i<n;i++)
          cout<<"\n"<<a[i];
          sort();
            cout<<"\nIAfter shotring\n";
           for(i=0;i<n;i++)
          cout<<"\n"<<a[i];
          }
          
          
      
       } ;  

void ab::sort()
{
     int k,m;
     for(k=0;k<n;k++)
     {
                     for(j=0;j<n-k-1;j++)
     {
                     if(a[j]>a[j+1])
                     {int temp;
                                    temp=a[j];
                                    a[j]=a[j+1];
                                    a[j+1]=temp;
                                    }
                                    
                                    }
    
    
                                    }
}


int main()
{
    ab a;
    getch();
    return 0;
}
