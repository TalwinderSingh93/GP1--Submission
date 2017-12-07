//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\	cGame.cpp                               
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#include "cGame.h"

//Istantiate clouds 50pixel outside the screen on right side and stop rendering after 50pixel down zero on left side of screen
#define X_AXIS_CLOUDS_OFF_LIMIT -300 
#define X_AXIS_CLOUDS_ON_LIMIT	300 

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 cGame                              
//\ DESCRIPTION = Constructor                       
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
cGame::cGame()
{

}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 getInstance                              
//\ DESCRIPTION = Singleton Design Pattern, ensured that a class has only one instance                       
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 initialise                              
//\ DESCRIPTION = initialise variables and objects for the game                       
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	theAreaClicked = { 0, 0 };

	// Declare games texture 
	textureName = { "building","airplane", "cloud","theHelicopter","theBackground", "heli_menu", "build_menu", "build2_menu","HowToPlay"};
	texturesToUse = { "Images\\building5.png","Images\\Plane.png", "Images\\Clouds_1.png", "Images\\helicopter.png", "Images\\blue_bk.jpg", "Images\\heli_menu.png", "Images\\building_menu.png", "Images\\building2_menu.png", "Images\\HowToPlay.png" };
	// Add textures
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}

	// Declare buttons name and the texture to use
	btnNameList = { "exit_btn", "instructions_btn", "highscore_btn", "menu_btn", "play_btn", "playagain_btn"};
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_how-to-play.png", "Images/Buttons/button_high-score.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_play-again.png"};
	btnPos = { { 400, 525 },{ 400, 375 },{ 400, 450 },{ 400, 450 },{ 400, 300 },{ 400, 375 } };
	// Add button texture
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	//Istantiate buttons
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;
	theBtnType = EXIT;

	// Add different fonts
	theFontMgr->addFont("Diagon", "Fonts/Diagon.otf", 72);
	theFontMgr->addFont("Diagon2", "Fonts/Diagon.otf", 36);
	theFontMgr->addFont("Diagon3", "Fonts/Diagon.otf", 22);
	

	// Declare text Textures
	gameTextNames = { "HighScore", "Score", "TitleTxt", "HowToPlay1", "HowToPlay2", "GameOver"};
	gameTextList = { "High Score:34", "Score:24","Helicopter Run", "Gain altitude - mouse left button down","Lose altitude - mouse left button up", "Game Over !"};
	// Add text textures
	for (int text = 0; text < gameTextNames.size(); text++)
	{
		theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("Diagon")->createTextTexture(theRenderer, gameTextList[text], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
	}
	
	
	// Declare game sounds
	soundList = { "theme", "click", "explosion", "gameOver", "helicopterSound" };
	soundTypes = { MUSIC, SFX, SFX, MUSIC, SFX };
	soundsToUse = { "Audio/theme.wav", "Audio/mouseClick.wav", "Audio/helicopter_explosion.wav","Audio/gameOver.wav", "Audio/Helicopter_Sound.wav" };
	//Add game sounds
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	//Play game theme sound as a loop
	theSoundMgr->getSnd("theme")->play(-1);

	
	//Set game background
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	//Set menu helicopter image
	spriteBkgdHeli.setSpritePos({ 50, 50 });
	spriteBkgdHeli.setTexture(theTextureMgr->getTexture("heli_menu"));
	spriteBkgdHeli.setSpriteDimensions(theTextureMgr->getTexture("heli_menu")->getTWidth(), theTextureMgr->getTexture("heli_menu")->getTHeight());

	//Set menu buidings image
	spriteBkgdBuilding.setSpritePos({ 0, 400 });
	spriteBkgdBuilding.setTexture(theTextureMgr->getTexture("build_menu"));
	spriteBkgdBuilding.setSpriteDimensions(theTextureMgr->getTexture("build_menu")->getTWidth(), theTextureMgr->getTexture("build_menu")->getTHeight());
	spriteBkgdBuilding2.setSpritePos({ 550, 335 });
	spriteBkgdBuilding2.setTexture(theTextureMgr->getTexture("build2_menu"));
	spriteBkgdBuilding2.setSpriteDimensions(theTextureMgr->getTexture("build2_menu")->getTWidth(), theTextureMgr->getTexture("build2_menu")->getTHeight());

	//Set game's instructions image
	spriteBkgdHowToPlay.setSpritePos({ 50, 50 });
	spriteBkgdHowToPlay.setTexture(theTextureMgr->getTexture("HowToPlay"));
	spriteBkgdHowToPlay.setSpriteDimensions(theTextureMgr->getTexture("HowToPlay")->getTWidth(), theTextureMgr->getTexture("HowToPlay")->getTHeight());

	//Set game helicopter
	theHelicopter.setSpritePos({ renderWidth/10, renderHeight/2 });
	theHelicopter.setTexture(theTextureMgr->getTexture("theHelicopter"));
	theHelicopter.setSpriteDimensions(theTextureMgr->getTexture("theHelicopter")->getTWidth(), theTextureMgr->getTexture("theHelicopter")->getTHeight());
	theHelicopter.setHelicopterVelocity({ 0, 0 });

	iCloudsCycle = 0;
	iBuildingsCycle = 0;
	iAirplanesCycle = 0;
	iScoreCycle = 0;
	iGoingUp = 0;
	iCycleHelicopterSound = 500;
	iScore = 0;

	// read and load high score list from file 
	file.readData(iHighScoreList);
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 run                              
//\ DESCRIPTION = calls input, update and render functions to keep game running                   
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 render                              
//\ DESCRIPTION = render game elements such as player and background sprites                  
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	//Elements to render in the menu scene
	case MENU:
	{
		// Render background image
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render helicopter image
		spriteBkgdHeli.render(theRenderer, &spriteBkgdHeli.getSpriteDimensions(), &spriteBkgdHeli.getSpritePos(), spriteBkgdHeli.getSpriteRotAngle(), &spriteBkgdHeli.getSpriteCentre(), spriteBkgdHeli.getSpriteScale());
		// Render buildings image
		spriteBkgdBuilding.render(theRenderer, &spriteBkgdBuilding.getSpriteDimensions(), &spriteBkgdBuilding.getSpritePos(), spriteBkgdBuilding.getSpriteRotAngle(), &spriteBkgdBuilding.getSpriteCentre(), spriteBkgdBuilding.getSpriteScale());
		spriteBkgdBuilding2.render(theRenderer, &spriteBkgdBuilding2.getSpriteDimensions(), &spriteBkgdBuilding2.getSpritePos(), spriteBkgdBuilding2.getSpriteRotAngle(), &spriteBkgdBuilding2.getSpriteCentre(), spriteBkgdBuilding2.getSpriteScale());


		// Render the Title
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 335, 150, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// Render Buttons
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("instructions_btn")->render(theRenderer, &theButtonMgr->getBtn("instructions_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("instructions_btn")->getSpritePos(), theButtonMgr->getBtn("instructions_btn")->getSpriteScale());
		theButtonMgr->getBtn("highscore_btn")->render(theRenderer, &theButtonMgr->getBtn("highscore_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("highscore_btn")->getSpritePos(), theButtonMgr->getBtn("highscore_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	//Elements to render in the main level scene
	case PLAYING:
	{
		// Render background image
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		
		// Render each cloud in the vector array
		for (int draw = 0; draw < theClouds.size(); draw++)
		{
			theClouds[draw]->render(theRenderer, &theClouds[draw]->getSpriteDimensions(), &theClouds[draw]->getSpritePos(), theClouds[draw]->getSpriteRotAngle(), &theClouds[draw]->getSpriteCentre(), theClouds[draw]->getSpriteScale());
		}

		// Render each airplane in the vector array
		for (int draw = 0; draw < theAirplanes.size(); draw++)
		{
			theAirplanes[draw]->render(theRenderer, &theAirplanes[draw]->getSpriteDimensions(), &theAirplanes[draw]->getSpritePos(), theAirplanes[draw]->getSpriteRotAngle(), &theAirplanes[draw]->getSpriteCentre(), theAirplanes[draw]->getSpriteScale());
		}

		// Render each building in the vector array
		for (int draw = 0; draw < theBuildings.size(); draw++)
		{
			theBuildings[draw]->render(theRenderer, &theBuildings[draw]->getSpriteDimensions(), &theBuildings[draw]->getSpritePos(), theBuildings[draw]->getSpriteRotAngle(), &theBuildings[draw]->getSpriteCentre(), theBuildings[draw]->getSpriteScale());
		}

		//update score text texture
		string szScoreString = "Score: " + to_string(iScore) + " M";
		LPCSTR pScore = szScoreString.c_str();
		theTextureMgr->deleteTexture("Score");
		theTextureMgr->addTexture("Score", theFontMgr->getFont("Diagon2")->createTextTexture(theRenderer, pScore, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
		
		// Render the Score
		cTexture* tempTextTexture = theTextureMgr->getTexture("Score");
		SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// render helicopter
		theHelicopter.render(theRenderer, &theHelicopter.getSpriteDimensions(), &theHelicopter.getSpritePos(), theHelicopter.getSpriteRotAngle(), &theHelicopter.getSpriteCentre(), theHelicopter.getSpriteScale());

	}
	break;
	//Elements to render in the instructions scene
	case INSTRUCTIONS:
	{
		// Render background image
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render instructions image
		spriteBkgdHowToPlay.render(theRenderer, &spriteBkgdHowToPlay.getSpriteDimensions(), &spriteBkgdHowToPlay.getSpritePos(), spriteBkgdHowToPlay.getSpriteRotAngle(), &spriteBkgdHowToPlay.getSpriteCentre(), spriteBkgdHowToPlay.getSpriteScale());
		// Render buildings image
		spriteBkgdBuilding.render(theRenderer, &spriteBkgdBuilding.getSpriteDimensions(), &spriteBkgdBuilding.getSpritePos(), spriteBkgdBuilding.getSpriteRotAngle(), &spriteBkgdBuilding.getSpriteCentre(), spriteBkgdBuilding.getSpriteScale());
		spriteBkgdBuilding2.render(theRenderer, &spriteBkgdBuilding2.getSpriteDimensions(), &spriteBkgdBuilding2.getSpritePos(), spriteBkgdBuilding2.getSpriteRotAngle(), &spriteBkgdBuilding2.getSpriteCentre(), spriteBkgdBuilding2.getSpriteScale());

		// Create instructions text 1
		LPCSTR pTxt = "Gain altitude - mouse left button down";
		theTextureMgr->deleteTexture("HowToPlay1");
		theTextureMgr->addTexture("HowToPlay1", theFontMgr->getFont("Diagon3")->createTextTexture(theRenderer, pTxt, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));

		// render instructions text 1
		tempTextTexture = theTextureMgr->getTexture("HowToPlay1");
		pos = { 300, 250, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// Create instructions text 2
		pTxt = "Lose altitude - mouse left button up";
		theTextureMgr->deleteTexture("HowToPlay2");
		theTextureMgr->addTexture("HowToPlay2", theFontMgr->getFont("Diagon3")->createTextTexture(theRenderer, pTxt, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));

		// render instructions text 2
		tempTextTexture = theTextureMgr->getTexture("HowToPlay2");
		pos = { 300, 280, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//Render buttons
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
	}
	break;
	//Elements to render in the highscore scene
	case SCORE:
	{
		// Render background image
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render buildings image
		spriteBkgdBuilding.render(theRenderer, &spriteBkgdBuilding.getSpriteDimensions(), &spriteBkgdBuilding.getSpritePos(), spriteBkgdBuilding.getSpriteRotAngle(), &spriteBkgdBuilding.getSpriteCentre(), spriteBkgdBuilding.getSpriteScale());
		spriteBkgdBuilding2.render(theRenderer, &spriteBkgdBuilding2.getSpriteDimensions(), &spriteBkgdBuilding2.getSpritePos(), spriteBkgdBuilding2.getSpriteRotAngle(), &spriteBkgdBuilding2.getSpriteCentre(), spriteBkgdBuilding2.getSpriteScale());

		
		//Render high score list
		for (int iCount = 0; iCount < 10; iCount++)
		{
			string szScoreString = "High Score " + to_string(iCount +1) + ": " + to_string(iHighScoreList[iCount]) + " M";
			LPCSTR pScore = szScoreString.c_str();
			theTextureMgr->deleteTexture("HighScore");
			theTextureMgr->addTexture("HighScore", theFontMgr->getFont("Diagon2")->createTextTexture(theRenderer, pScore, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
			
			// Render the Score
			tempTextTexture = theTextureMgr->getTexture("HighScore");
			pos = { 370, 100 +(iCount*30), tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			scale = { 1, 1 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		}
		
		//Render buttons
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
	}
	break;
	//Elements to render in the end scene
	case END:
	{
		// Render background image
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render buildings image
		spriteBkgdBuilding.render(theRenderer, &spriteBkgdBuilding.getSpriteDimensions(), &spriteBkgdBuilding.getSpritePos(), spriteBkgdBuilding.getSpriteRotAngle(), &spriteBkgdBuilding.getSpriteCentre(), spriteBkgdBuilding.getSpriteScale());
		spriteBkgdBuilding2.render(theRenderer, &spriteBkgdBuilding2.getSpriteDimensions(), &spriteBkgdBuilding2.getSpritePos(), spriteBkgdBuilding2.getSpriteRotAngle(), &spriteBkgdBuilding2.getSpriteCentre(), spriteBkgdBuilding2.getSpriteScale());

		tempTextTexture = theTextureMgr->getTexture("GameOver");
		pos = { 300, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		
		//Create score text
		string szScoreString = "Score: " + to_string(iOldScore) + " M";
		LPCSTR pScore = szScoreString.c_str();
		theTextureMgr->deleteTexture("Score");
		theTextureMgr->addTexture("Score", theFontMgr->getFont("Diagon2")->createTextTexture(theRenderer, pScore, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));

		// Render the Score
		tempTextTexture = theTextureMgr->getTexture("Score");
		pos = { 430, 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//Render buttons
		theButtonMgr->getBtn("playagain_btn")->render(theRenderer, &theButtonMgr->getBtn("playagain_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("playagain_btn")->getSpritePos(), theButtonMgr->getBtn("playagain_btn")->getSpriteScale());
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case QUIT:
	{
		theSoundMgr->getSnd("click")->play(0);
		loop = false;
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{
	SDL_RenderPresent(theRenderer);
}


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 update                              
//\ DESCRIPTION = update game elements visibility and position                   
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void cGame::update(double deltaTime)
{
	theGameOldState = theGameState;

	//Check if a button is clicked in the menu screen
	if (theGameState == MENU)
	{
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
		theGameState = theButtonMgr->getBtn("instructions_btn")->update(theGameState, INSTRUCTIONS, theAreaClicked);
		theGameState = theButtonMgr->getBtn("highscore_btn")->update(theGameState, SCORE, theAreaClicked);
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
		
		theAreaClicked = { 0, 0 };
	}
	//Check if a button is clicked in the instruction screen
	else if (theGameState == SCORE || theGameState == INSTRUCTIONS)
	{
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
		theAreaClicked = { 0, 0 };
	}
	//Check if a button is clicked in the end screen
	else if (theGameState == END)
	{
		theGameState = theButtonMgr->getBtn("playagain_btn")->update(theGameState, PLAYING, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
		theAreaClicked = { 0, 0 };
	}

	//If a button is clicked produce the click sound
	if (theGameState != theGameOldState)
	{
		theSoundMgr->getSnd("click")->play(0);
		theGameOldState = theGameState;
	}

	switch (theGameState)
	{
	case PLAYING:
	{
		// Update the visibility and position of each cloud
		vector<cCloud*>::iterator cloudIterartor = theClouds.begin();
		while (cloudIterartor != theClouds.end())
		{
			if ((*cloudIterartor)->isActive() == false)
			{
				cloudIterartor = theClouds.erase(cloudIterartor);
			}
			else
			{
				(*cloudIterartor)->update(deltaTime);
				++cloudIterartor;
			}
		}

		// Update the visibility and position of each airplane
		vector<cAirplane*>::iterator airplaneIterartor = theAirplanes.begin();
		while (airplaneIterartor != theAirplanes.end())
		{
			if ((*airplaneIterartor)->isActive() == false)
			{
				airplaneIterartor = theAirplanes.erase(airplaneIterartor);
			}
			else
			{
				(*airplaneIterartor)->update(deltaTime);
				++airplaneIterartor;
			}
		}

		// Update the visibility and position of each building
		vector<cBuilding*>::iterator buildingIterartor = theBuildings.begin();
		while (buildingIterartor != theBuildings.end())
		{
			if ((*buildingIterartor)->isActive() == false)
			{
				buildingIterartor = theBuildings.erase(buildingIterartor);
			}
			else
			{
				(*buildingIterartor)->update(deltaTime);
				++buildingIterartor;
			}
		}

		//Produce helicopter sound during main level screen
		if (iCycleHelicopterSound > 100)
		{
			theSoundMgr->getSnd("helicopterSound")->play(0);
			iCycleHelicopterSound = 0;
		}
		else
		{
			iCycleHelicopterSound++;
		}
		

		/*
		==============================================================
		| Check for collisions
		==============================================================
		*/

		//collision with airplanes
		for (vector<cAirplane*>::iterator airplaneIterartor = theAirplanes.begin(); airplaneIterartor != theAirplanes.end(); ++airplaneIterartor)
		{
			//if there is a colission between helicopter and airplane trigger game over	
			if (theHelicopter.collidedWith(&(theHelicopter.getBoundingRect()), &(*airplaneIterartor)->getBoundingRect()))
			{
				theAreaClicked = { 0, 0 };
				iOldScore = iScore;

				int iCheckUpdateScore = -1;

				//Check if there is a new high score
				iCheckUpdateScore = score.updateIfnewHighScore(iScore, iHighScoreList);

				//Update file if new high score
				if (iCheckUpdateScore >= 0)
				{
					file.writeData(iHighScoreList);
				}
					
				//Reset game variable
				iScore = 0;
				theGameState = END;
				theClouds.clear();
				theBuildings.clear();
				theAirplanes.clear();
				theSoundMgr->getSnd("explosion")->play(0);

				break;
					
			}
		}

		//collision with buildings
		for (vector<cBuilding*>::iterator buildingIterartor = theBuildings.begin(); buildingIterartor != theBuildings.end(); ++buildingIterartor)
		{
			//if there is a colission between helicopter and building trigger game over	
			if (theHelicopter.collidedWith(&(theHelicopter.getBoundingRect()), &(*buildingIterartor)->getBoundingRect()))
			{
				theAreaClicked = { 0, 0 };
				iOldScore = iScore;

				int iCheckUpdateScore = -1;

				//Check if there is a new high score
				iCheckUpdateScore = score.updateIfnewHighScore(iScore, iHighScoreList);

				//Update file if new high score
				if (iCheckUpdateScore >= 0)
				{
					file.writeData(iHighScoreList);
				}

				//Reset game variable
				iScore = 0;
				theGameState = END;
				theClouds.clear();
				theBuildings.clear();
				theAirplanes.clear();
				theSoundMgr->getSnd("explosion")->play(0);

				break;

			}
		}
		

		/*
		==============================================================
		| SetActive to false when a element goes outside the screen
		==============================================================
		*/

		for (vector<cCloud*>::iterator cloudIterartor = theClouds.begin(); cloudIterartor != theClouds.end(); ++cloudIterartor)
		{
			if ((*cloudIterartor)->getSpritePos().x < X_AXIS_CLOUDS_OFF_LIMIT)
			{
				(*cloudIterartor)->setActive(false);
			}
		}

		for (vector<cAirplane*>::iterator airplaneIterartor = theAirplanes.begin(); airplaneIterartor != theAirplanes.end(); ++airplaneIterartor)
		{
			if ((*airplaneIterartor)->getSpritePos().x < X_AXIS_CLOUDS_OFF_LIMIT)
			{
				(*airplaneIterartor)->setActive(false);
			}
		}

		for (vector<cBuilding*>::iterator buildingIterartor = theBuildings.begin(); buildingIterartor != theBuildings.end(); ++buildingIterartor)
		{
			if ((*buildingIterartor)->getSpritePos().x < X_AXIS_CLOUDS_OFF_LIMIT)
			{
				(*buildingIterartor)->setActive(false);
			}
		}




		/*
		==============================================================
		| Istanciate clouds randomly
		==============================================================
		*/
		if (iCloudsCycle > 25)
		{
			theClouds.push_back(new cCloud);
			int numClouds = theClouds.size() - 1;
			theClouds[numClouds]->setSpritePos({ X_AXIS_CLOUDS_ON_LIMIT + renderWidth, rand() % 450 });
			theClouds[numClouds]->setSpriteTranslation({ 2, 2 });
			theClouds[numClouds]->setTexture(theTextureMgr->getTexture("cloud"));
			theClouds[numClouds]->setSpriteDimensions(theTextureMgr->getTexture("cloud")->getTWidth(), theTextureMgr->getTexture("cloud")->getTHeight());
			theClouds[numClouds]->setCloudVelocity({ 2, 2 });
			theClouds[numClouds]->setActive(true);

			iCloudsCycle = 0;
		}
		else
		{
			iCloudsCycle++;
		}

		/*
		==============================================================
		| Istanciate airplanes randomly
		==============================================================
		*/
		if (iAirplanesCycle > 100)
		{
			theAirplanes.push_back(new cAirplane);
			int numAirplanes = theAirplanes.size() - 1;
			theAirplanes[numAirplanes]->setSpritePos({ X_AXIS_CLOUDS_ON_LIMIT + renderWidth, rand() % 300 });
			theAirplanes[numAirplanes]->setSpriteTranslation({ 3, 2 });
			theAirplanes[numAirplanes]->setTexture(theTextureMgr->getTexture("airplane"));
			theAirplanes[numAirplanes]->setSpriteDimensions(theTextureMgr->getTexture("airplane")->getTWidth(), theTextureMgr->getTexture("airplane")->getTHeight());
			theAirplanes[numAirplanes]->setAirplaneVelocity({ 2, 2 });
			theAirplanes[numAirplanes]->setActive(true);

			iAirplanesCycle = 0;
		}
		else
		{
			iAirplanesCycle++;
		}

		/*
		==============================================================
		| Istanciate buildings randomly
		==============================================================
		*/
		if (iBuildingsCycle > 125)
		{
			theBuildings.push_back(new cBuilding);
			int numBuildings = theBuildings.size() - 1;
			theBuildings[numBuildings]->setSpritePos({ X_AXIS_CLOUDS_ON_LIMIT + renderWidth, 440});
			theBuildings[numBuildings]->setSpriteTranslation({ 2, 2 });
			theBuildings[numBuildings]->setTexture(theTextureMgr->getTexture("building"));
			theBuildings[numBuildings]->setSpriteDimensions(theTextureMgr->getTexture("building")->getTWidth(), theTextureMgr->getTexture("building")->getTHeight());
			theBuildings[numBuildings]->setBuildingVelocity({ 2, 2 });
			theBuildings[numBuildings]->setActive(true);

			iBuildingsCycle = 0;
		}
		else
		{
			iBuildingsCycle++;
		}

		//Update score value
		if (iScoreCycle > 4)
		{
			iScore++;
			iScoreCycle = 0;
		}
		else
		{
			iScoreCycle++;
		}


		
		//Ensure that helicopter stays inside the screen
		if ((theHelicopter.getSpritePos().y < theHelicopter.getBoundingRect().h) && (iGoingUp > 0))
		{
			theHelicopter.setSpriteTranslation({ 0, 0 });
		}
		else if ((theHelicopter.getSpritePos().y > (renderHeight - theHelicopter.getBoundingRect().h)) && (iGoingUp <= 0))
		{
			theHelicopter.setSpriteTranslation({ 0, 0 });
		}

		// Update the helicopter position
		theHelicopter.update(deltaTime);
	}
	break;
	case END:
	{
		
		/*
		==============================================================
		| SetActive to false every element
		==============================================================
		*/
		for (vector<cCloud*>::iterator cloudIterartor = theClouds.begin(); cloudIterartor != theClouds.end(); ++cloudIterartor)
		{
			(*cloudIterartor)->setActive(false);
		}

		for (vector<cAirplane*>::iterator airplaneIterartor = theAirplanes.begin(); airplaneIterartor != theAirplanes.end(); ++airplaneIterartor)
		{
			(*airplaneIterartor)->setActive(false);
		}

		for (vector<cBuilding*>::iterator buildingIterartor = theBuildings.begin(); buildingIterartor != theBuildings.end(); ++buildingIterartor)
		{
			(*buildingIterartor)->setActive(false);
		}
		
	}
	}
}


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 getInput                              
//\ DESCRIPTION = update game elements visibility and position                   
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					// set the area clicked
					theAreaClicked = { event.motion.x, event.motion.y };

					//Move helicopter to up
					iGoingUp = 1;
					theHelicopter.setSpriteTranslation({ 0, 10 });

				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					//Move helicopter to down
					iGoingUp = 0;
					theHelicopter.setSpriteTranslation({ 0, -10 });
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			break;
			default:
			break;
		}

	}
	return theLoop;
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 getElapsedSeconds                              
//\ DESCRIPTION = get the time that passed since the last frame                   
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//\ NAME        =                 cleanUp                              
//\ DESCRIPTION = closes and destroys elements of the game that were created. the function is called before closing the game                   
//\ PARAMETER   =                                                         
//\ DATE        =                                           
//\ AUTHOR      = Talwinder Singh                             
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

