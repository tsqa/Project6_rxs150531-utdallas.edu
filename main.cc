#include <iostream>
#include "cdk.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 4
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Test Matrix"

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

ifstream input ("cs3377.bin", ios::binary);
input.read(reinterpret_cast<char *>(&magic), sizeof(magic)); // directly load bytes into uint32_t

	cout << "magicNum is: ";
	cout << hex << magic;
input.read(reinterpret_cast<char *>(&versionNumber), sizeof(versionNumber));	
	cout << "versionNum is: ";
	cout << hex << versionNumber;
input.read(reinterpret_cast<char *>(&numRecords), sizeof(numRecords));
	cout << "numRecords is: ";
	cout << hex << numRecords;
input.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
	cout << "strLength is: ";
	cout << hex << strLength;
input.read(reinterpret_cast<char *>(&stringBuffer[0]), sizeof(stringBuffer[0]));
	cout << "stringBuffer is: ";
	cout << hex << stringBuffer;

stringstream ss;
ss << hex << magic;
string str = ss.str();
	cout << "\n magicNum is: ";
	cout << str;

	cout << " done";
	unsigned char ax;
  	cin >> ax;

}