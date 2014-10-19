#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
main()
{
clrscr();
float a,b,c,d,l,m,n,k,p,D,q,r,s,x,y,z;
printf("PROGRAM TO SOLVE THREE VARIABLE LINEAR SIMULTANEOUS
EQUATIONS");
printf("The equations are of theform:
ax+by+cz+d=0
lx+my+nz+k=0
px+qy+rz+s=0
");
printf("Enter the coefficients in the order a,b,c,d,l,m,n,k,p,q,r,s");
scanf("%f%f%f%f%f%f%f%f%f%f%f%f",&a,&b,&c,&d,&l,&m,&n,&k,&p,&q,&r,&s);
printf("The equations you have input are:");
printf("  %.2f*x + %.2f*y + %.2f*z + %.2f = 0",a,b,c,d);
printf("  %.2f*x + %.2f*y + %.2f*z + %.2f = 0",l,m,n,k);
printf("  %.2f*x + %.2f*y + %.2f*z + %.2f = 0",p,q,r,s);

 D = (a*m*r+b*p*n+c*l*q)-(a*n*q+b*l*r+c*m*p);
 x = ((b*r*k+c*m*s+d*n*q)-(b*n*s+c*q*k+d*m*r))/D;
 y = ((a*n*s+c*p*k+d*l*r)-(a*r*k+c*l*s+d*n*p))/D;
 z = ((a*q*k+b*l*s+d*m*p)-(a*m*s+b*p*k+d*l*q))/D;

printf("The solutions to the above three equations are :");
printf("  x = %5.2f
  y = %5.2f
  z = %5.2f
",x,y,z);
getch();
return 0;
}
</stdlib.h></conio.h></stdio.h>
