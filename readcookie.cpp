// Fig. 15.16 : readcookie.cpp
// Program to read cookie data.
#include <iostream>

using std::cout;
using std::cin;

#include <cstdlib>
#include <string>

using std::string;

int main()
{
   char *data = getenv( "HTTP_COOKIE" );
   
   string dataString = "";
   string nameString = "";
   string ageString = "";
   string colorString = "";
   
   dataString = data;
   
   // search through cookie data string
   int nameLocation = dataString.find( "Name=" ) + 5;
   int endName = dataString.find( "age:" );
   
   int ageLocation = dataString.find( "age:" ) + 4;
   int endAge = dataString.find( "color:" );
   
   int colorLocation = dataString.find( "color:" ) + 6;
   
   // store cookie data in strings
   nameString = dataString.substr( nameLocation, endName - 
      nameLocation );
   ageString = dataString.substr( ageLocation, endAge - 
      ageLocation);
   colorString = dataString.substr( colorLocation );
   
   // output header
   cout << "Content-type: text/html\n\n";
   
   // output XML declaration and DOCTYPE
   cout << "<?xml version = \"1.0\"?>"
        << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 "
        << "Transitional//EN\" \"http://www.w3.org/TR/xhtml1"
        << "/DTD/xhtml1-transitional.dtd\">";

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
        << "<head><title>Read Cookies</title></head>"
        << "<body>";
   
   // data was found
   if ( data != 0 )
      cout << "<h3>The following data is saved in a cookie on"
           << " your computer</h3>"
           << "<p>Name: "  << nameString  << "<br/></p>"
           << "<p>Age: "   << ageString   << "<br/></p>"
           << "<p>Color: " << colorString << "<br/></p>";

   // no data was found
   else
      cout << "<p>No cookie data.</p>";
   
   cout << "</body></html>";
   
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
