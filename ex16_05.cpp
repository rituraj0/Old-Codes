// Exercise. 16.05 : ex16_05.cpp
// Soothsayer Exercise
#include <iostream>

using std::cout;
using std::cin;

#include <string>

using std::string;

#include <cstdlib>
#include <ctime>

int main()
{
   char postString[ 1024 ] = ""; // variable to hold posted string
   string dataString = "";
   string questionString = "";

   int contentLength = 0;
   
   // content was submitted
   if ( getenv( "CONTENT_LENGTH" ) ) {

      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
   
      cin.read( postString, contentLength );
      dataString = postString;
   }

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
   cout << "<p>Please enter a question:</p>"
        << "<form method = \"post\" action = \"ex16_05.cgi\">"
        << "<input type = \"text\" name = \"question\" size=50/><br/>"
        << "<br/><input type = \"submit\" value = \"Ask Question\" />"
        << "</form>";
   
   // data was sent using POST
   if ( contentLength > 0 ) {

	   
      // retrieve first value
	  int questionLocation = 
         dataString.find( "question=" ) + 9;
      
      questionString = dataString.substr( questionLocation );

      srand( time ( 0 ) );
	  int randomnumber = 1 + rand() % 5;

	  switch ( randomnumber )
	  {

	  case 1:
		  cout << "It Could be.";
		  break;
	  
	  case 2:
		  cout << "Probably not.";
		  break;

	  case 3:
		  cout << "Definitely.";
		  break;

	  case 4:
		  cout << "Not looking too good.";
		  break;

	  case 5:
		  cout << "Yes.";
		  break;
	  
	  default:
		  cout << "Your question was too vague.";
		  break;
	  
	  } // end switch

		  cout << "<br/><br/>"
			   << "Please ask another question.";

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