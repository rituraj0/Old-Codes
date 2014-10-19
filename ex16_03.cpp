// Exercise. 16.03 : ex16_03.cpp
// Numbers 1 through 10 and their squares
#include <iostream>

using std::cout;

#include <cstdlib>


int main()
{

   // output header
   cout << "Content-type: text/html\n\n";

   // output XML declaration and DOCTYPE
   cout << "<?xml version = \"1.0\"?>" 
        << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 "
        << "Transitional//EN\"";
   
   // output html element and its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
        << "<head><title>Numbers 1 through 10 Squared</title>"
        << "</head><body>Numbers 1 through 10 Squared"
		<< "<br/><br/>";

   
   // iterate from 1 to 10
   for(int i = 1; i <= 10; i++) {
	   
	   cout << "The square of " << i 
		    << " is " << i * i << "<br/>";
   } // end for


   cout << "</body></html>\n";

   return 0;

} // end main

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/