#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <iomanip.h>
#include <string>
#include <ctype.h>

/*
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(void)
{
        char buf[512];
        ssize_t rb,wb;
        int fd=fopen("/path/to/dev", O_RDWR);
        if(fd < 0)
        {
                perror("Couldn't open device");
                return(1);
        }

        rb=read(fd, buf, 512);
        fprintf(stderr, "Read %d bytes\n", (int)rb);

        if(lseek(fd, 0L, SEEK_SET) != 0L)
        {
                perror("Couldn't seek");
                close(fd);
                return(1);
        }

        wb=write(fd, buf, rb);
        fprintf(stderr, "Wrote %d bytes\n", (int)wb);

        close(fd);
        return(0);
}
*/


void wipepart(char name[])
{
   FILE *f = fopen("\\.\E:","w");
   fputc( 0, f );
}

main()
{
           	display:
      //		light();
        //		clrscr();

      		cout<<"\n\n\t\t\t\t";cprintf("     FILE WIPER");
     			textcolor(RED);
     			cout <<"\n\t\t\t\t";cprintf("     ---- -----\n");

      		cout <<"\n\t\t\t\t";cprintf("       WIPE");
      		textcolor(BLUE);
      		cout <<"\n\t\t\t\t";cprintf("       ----");cout<<"\n\n\n";

      		cout <<"\t\t\t\t1. Wipe a File\n\n";
      		cout <<"\t\t\t\t2. Wipe a Partition\n\n";
      		cout <<"\t\t\t\t3. Wipe a Partition [Official]\n\n";
            cout <<"\t\t\t\t4. Back\n\n";

    		   textcolor(GREEN);
      		cout <<"\t\t\t\t";cprintf("Enter your Choice: ");
      		backg(); gotoxy(52,18);
      		cin>>ch;

      		switch(ch)
      		{
       		   case 1:
            	cout <<"\nX\t\t\tEnter the Name of File to Delete: ";
            	gets(name);
          //  	light();
          //  	wipefile(name);

               goto display;

          		case 2:
               cout <<"\nX\t\t\tEnter the Drive letter of Partition to Wipe: ";
            	gets(name);

            	textcolor(GREEN);
            	cout<<"X\t\t\t\t";cprintf("Are you Really Sure? (Y/N) : ");
            	cin>>cho;

            	if ((cho=='y') || (cho=='Y'))
                    {
                     cout<<"X\t\t\t\t";cprintf("This will take some time...");
                 		light();
                 		wipepart(name);
                		}

            	goto display;

               case 3:
               cout <<"\nX\t\t\tEnter the Drive letter of Partition to Wipe: ";
            	gets(name);

            	textcolor(GREEN);
            	cout<<"X\t\t\t\t";cprintf("Are you Really Sure? (Y/N) : ");
            	cin>>cho;

            	if ((cho=='y') || (cho=='Y'))
                    {
                     cout<<"X\t\t\t\t";cprintf("  This will take some time...");
            //     		light();
             //    		wipepartoff(name);
                		}

            	goto display;

               case 4:
            		goto modifi;
      		}
} */