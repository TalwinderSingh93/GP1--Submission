/*
=================
cScore.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cScore.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cScore::cScore() : cSprite()
{
	
}

/*
=================================================================
  Sets the velocity for the Cloud
=================================================================
*/
int cScore::updateIfnewHighScore(int score, int *highscore)
{
	int iPosition = -1;
	
	for (int iCount = 9; iCount >= 0; iCount--)
	{
		if (highscore[iCount] < score)
		{
			iPosition = iCount;
		}
		else
		{
			break;
		}

	}

					
	if (iPosition >= 0)
	{
		for (int iCount = 9; (iCount > iPosition) && (iCount > 0); iCount--)
		{
			highscore[iCount] = highscore[iCount - 1];
		}

		highscore[iPosition] = score;
	}

	return iPosition;
}

