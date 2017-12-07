/*
=================
cFile.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cFile.h"


/*
=================================================================
Defualt Constructor
=================================================================
*/
cFile::cFile() : cSprite()
{
	
}

/*
=================================================================
  read data from file
=================================================================
*/
void cFile::readData(int *highScore)
{
	ifstream inFile;
	inFile.open(FILE_NAME);

	if (inFile.is_open())
	{
		for (int iCount = 0; iCount < 10; iCount++)
		{
			inFile >> highScore[iCount];
		}
		inFile.close();
	}
	
}
/*
=================================================================
  write data from file
=================================================================
*/
void cFile::writeData(int *highScore)
{
	ofstream outFile;
	outFile.open(FILE_NAME);

	if (outFile.is_open())
	{
		for (int iCount = 0; iCount < 10; iCount++)
		{
			outFile << highScore[iCount];
			outFile << endl;
		}
		outFile.close();
	}

}
