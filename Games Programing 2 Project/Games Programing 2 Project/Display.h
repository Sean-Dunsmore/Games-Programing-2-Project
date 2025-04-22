#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

//Display class to manage display window
class Display
{
public:

	Display(); //Constructor
	~Display();	//Deconstructor

	//Init
	void initDisplay();

	//Swap Buffers
	void swapBuffer();

	//Clear Screen to specific color value
	void clearDisplay(float r, float g, float b, float a);

	//Get screen height and width
	float getWidth();
	float getHeight();

private:
	
	//Return error
	void returnError(std::string errorString);

	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window

	//Height and width of screen
	float screenWidth;
	float screenHeight;
};


