#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#ifdef _DEBUG 
#pragma comment ( lib , "sfml-audio-d.lib" )
#pragma comment ( lib , "sfml-main-d.lib" ) 
#pragma comment ( lib , "sfml-system-d.lib" ) 
#pragma comment ( lib , "sfml-window-d.lib" ) 
#pragma comment ( lib , "sfml-graphics-d.lib" ) 
#elif defined (NDEBUG) 
#pragma comment ( lib , "sfml-audio.lib" )
#pragma comment ( lib , "sfml-main.lib" ) 
#pragma comment ( lib , "sfml-system.lib" ) 
#pragma comment ( lib , "sfml-window.lib" ) 
#pragma comment ( lib , "sfml-graphics.lib" ) 
#else 
#error "Unrecognized configuration!" 
#endif 


//Object
enum players { random, player, computer };
enum colors { Yellow, Red, Green, Cyan, Blue, Magenta, White, Black };

//GameBoard
static const int NUM_OF_OBJECTS = 30;
static const sf::Vector2f BOARD_SIZE = { 900.0, 900.0 };
static const sf::Vector2f POSITON_BOARD = { 250.0, 5.0 };//posion on screen
static const float OBJECT_SIZE = { BOARD_SIZE.x / (NUM_OF_OBJECTS * (float)sqrt(2)) };

//Controller
static const sf::Vector2f WINDOE_SIZE = { 1200.0 , 1050.0 };

//Menu
static const float W_BUTTENS_SIZE = 100;//The width of a button
static const int NUM_OF_BUTTENS = 2;//Number of buttons
static const sf::Vector2f POSITON_MENU = { 0, 0 };
static const sf::Vector2f SIZE_BUTTON = { 100.0, 100.0 };
static const sf::Vector2f SIZE_MENU = { W_BUTTENS_SIZE * NUM_OF_BUTTENS, 900.0 };
