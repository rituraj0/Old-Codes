// Exercise. 16.04 : ex16_04.cpp
// Evaluate 3 sides of a triangle
#include <iostream>

using std::cout;
using std::cin;

#include <string>

using std::string;

#include <cstdlib>

int main()
{
   char postString[ 1024 ] = ""; // variable to hold query string
   string dataString = "";
   string oneString = "";
   string twoString = "";
   string threeString = "";

   int contentLength = 0;
   
   // content was submitted
   if ( getenv( "CONTENT_LENGTH" ) ) {

      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
      cin.read( postString, contentLength );
      dataString = postString;
   
   } // end if

   // output header
   cout << "Content-type: text/html\n\n";
   
   // output XML declaration and DOCTYPE
   cout << "<?xml version = \"1.0\"?>"
        << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 "
        << "Transitional//EN\" \"http://www.w3.org/TR/xhtml1"
        << "/DTD/xhtml1-transitional.dtd\">";

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
        << "<head><title>Using POST with Forms</title></head>"
        << "<body>";
   
   // output xhtml form
   cout << "<p>Enter three integers:</p>"
        << "<form method = \"post\" action = \"ex16_04.cgi\">"
        << "One<br/><input type = \"text\" name = \"one\" /><br/>"
        << "Two<br/><input type = \"text\" name = \"two\" /><br/>"
        << "Three<br/><input type = \"text\" name = \"three\" /><br/>"
        << "<br/><input type = \"submit\" value = \"Submit Numbers\" />"
        << "</form>";
   
   // data was sent using POST
   if ( contentLength > 0 ) {

	   
      // retrieve first value
	  int oneLocation = 
         dataString.find( "one=" ) + 4;
      
      int endOne = dataString.find( "&two" ) ;
      
      oneString = dataString.substr( oneLocation,
         endOne - oneLocation );

      // retrieve second value
	  int twoLocation = 
         dataString.find( "two=" ) + 4;
      
      int endTwo = dataString.find( "&three" ) ;
      
      twoString = dataString.substr( twoLocation,
         endTwo - twoLocation );

      // retrieve third value
	  int threeLocation = 
         dataString.find( "three=" ) + 6;
      
      //int endThree = dataString.find( "&three" ) ;
      
      threeString = dataString.substr( threeLocation );
		  //,       endThree - threeLocation );

      int one = atoi(oneString.data());
      int two = atoi(twoString.data());
      int three = atoi(threeString.data());

	  // equilateral triangle
      if( one == two && two == three )
		  cout << "This is an equilateral triangle";

	  // isosceles triangle
	  if( (one == two && one != three) || (two == three && two != one)
		  || (one == three && one != two))
		  cout << "This is an isosceles triangle";

	  
	  int onesquared = one * one;
	  int twosquared = two * two;
	  int threesquared = three * three;
	  
	  // right triangle
	  if( (onesquared == (twosquared + threesquared)) ||
		  (twosquared == (onesquared + threesquared)) ||
		  (threesquared == (onesquared + twosquared)))
	     cout << "This is a right triangle.";

   } // end if
   
   // no data was sent
   else
      cout << "<p>Please enter data in the form.</p>";
   
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
