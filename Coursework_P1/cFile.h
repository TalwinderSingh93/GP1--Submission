/*
=================
cFile.h
- Header file for class definition - SPECIFICATION
- Header file for the File class which is a child of cSprite class
=================
*/
#ifndef _CFILE_H
#define _CFILE_H

#define FILE_NAME "HighScore.txt"

#include "helicopterGame.h"


class cFile : public cSprite
{
private:
	

public:
	cFile();
	void readData(int *highScore);		// read high score list from file
	void writeData(int *highScore);   // write high score list into file
			
};
#endif