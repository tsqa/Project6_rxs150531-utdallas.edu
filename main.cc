//Rishav Sinha rxs150531 - rxs150531@utdallas.edu
//Program 6
#include <iostream>
#include "cdk.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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


  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
  stringstream ss; //exists for hex conversion to c string
  string str; //holds string to be output to matrix

  ifstream input ("cs3377.bin", ios::binary);

  if (!input.is_open()) //check to see if file can be opened
    {
     cout << "can't open file" << endl;
     exit(1);
    }

  input.read(reinterpret_cast<char *>(&magic), sizeof(magic)); // directly load bytes into uint32_t
  ss << "Magic: " << hex << magic;
  str = ss.str();
  setCDKMatrixCell(myMatrix, 1, 1, str.c_str());
  ss.str(""); //clear the holding var

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


  string temp = "strlen: ";
  char intStr[10];
  int temp2 = 0;
 
  for(int i = 1; i <= 4; i++){
    input.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    input.read(reinterpret_cast<char *>(&stringBuffer), sizeof(stringBuffer));
    string s(stringBuffer); 
    cout << "the string is: " << s << " the length of the string is: " << (int)strLength << endl;
    temp2 = (int)strLength;
    sprintf(intStr, "strlen: %d",temp2);
    setCDKMatrixCell(myMatrix, i+1, 1, intStr);
    setCDKMatrixCell(myMatrix, i+1, 2, stringBuffer);
  }

  input.close();



  drawCDKMatrix(myMatrix, true);

  // delay the screen clear so results can be seen
  unsigned char a;
  cin >> a;

  //clean screen
  endCDK();


}
