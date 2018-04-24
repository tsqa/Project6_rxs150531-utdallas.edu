#include <iostream>
#include "cdk.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

uint32_t magic;  // big endian here...
uint32_t versionNumber;
uint64_t numRecords;
uint8_t strLength;
char stringBuffer[25];


  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
stringstream ss;
string str;

ifstream input ("cs3377.bin", ios::binary);

input.read(reinterpret_cast<char *>(&magic), sizeof(magic)); // directly load bytes into uint32_t
ss << "Magic: " << hex << magic;
str = ss.str();
setCDKMatrixCell(myMatrix, 1, 1, str.c_str());
ss.str("");

input.read(reinterpret_cast<char *>(&versionNumber), sizeof(versionNumber));	
ss << "Version: " << hex << versionNumber;
str = ss.str();
setCDKMatrixCell(myMatrix, 1, 2, str.c_str());
ss.str("");

input.read(reinterpret_cast<char *>(&numRecords), sizeof(numRecords));
ss << "NumRecords: " << hex << numRecords;
str = ss.str();
setCDKMatrixCell(myMatrix, 1, 3, str.c_str());
ss.str("");


string temp = "";
int temp2 = 0;
for(int i = 1; i <= 4; i++){
input.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
input.read(reinterpret_cast<char *>(&stringBuffer), sizeof(stringBuffer));
//cout << "stringBuffer is: ";
//cout << hex << stringBuffer << endl;
string s(stringBuffer); 
temp2 = strlen(s.c_str());
cout << "the string is: " << s << " the length of the string is: " << temp2 << endl;
//temp = to_string(temp2);
//setCDKMatrixCell(myMatrix, i, 2, temp.c_str());
setCDKMatrixCell(myMatrix, i+1, 2, stringBuffer);
}

input.close();

cout << " done";
unsigned char ax;
cin >> ax;

//drawCDKMatrix(myMatrix, true);
//setCDKMatrixCell(myMatrix, 2, 2, "test");
drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();


}