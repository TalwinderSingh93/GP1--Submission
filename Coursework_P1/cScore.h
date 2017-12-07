/*
=================
cScore.h
- Header file for class definition - SPECIFICATION
- Header file for the Score class which is a child of cSprite class
=================
*/
#ifndef _CSCORE_H
#define _CSCORE_H
#include "cSprite.h"


class cScore : public cSprite
{
private:


public:
	cScore();
	int updateIfnewHighScore(int score, int *highscore);
};
#endif