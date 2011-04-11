#ifndef _FLIGHTGAME_H_
	#define _FLIGHTGAME_H_

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Oggler.h"
#include "Pushable.h"

class FlightGame {
	public:
		// Process Properties
		bool Running;
		unsigned int nFrame;
		sf::Clock Clock;
		float TimeStack;
		
		// Window & Properties
		sf::Window Window;
		float WIDTH;
		float HEIGHT;
		float ASPECT;
		
		// Mouse Position and Input
		sf::Event Event;
		float mX;
		float mY;
		
		// OpenGL & GLUT
		GLfloat light0pos[4];
		GLfloat light0dif[4];
		GLfloat light1pos[4];
		GLfloat light1dif[4];
		GLfloat light2pos[4];
		GLfloat light2dif[4];
		GLUquadric* GLUQ;
		
		// Game Objects
		Oggler Cam;
		Pushable MainShip;
		Pushable Ball;
	
	public:
		FlightGame();
		
		int Execute();
		void Initialize();
		void Loop();
		
		void Logic();
		void Physics();
		
		// InputHandler.cpp
		void InputHandler();
		void PhysicalInput();
		
		// Render.cpp
		void Render3D();
		void Render2D();
		
		void Exit();
		void Cleanup();
};

#endif
