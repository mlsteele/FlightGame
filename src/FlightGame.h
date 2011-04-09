#ifndef _FLIGHTGAME_H_
	#define _FLIGHTGAME_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class FlightGame {
	public:
		bool Running;
		unsigned int nFrame;
		sf::Clock Clock;
		float TimeStack;
		
		sf::Window Window;
		sf::Event Event;
		float WIDTH;
		float HEIGHT;
		float ASPECT;
		
		float mX;
		float mY;
		
		GLfloat light0pos[4];
		GLfloat light0dif[4];
		GLfloat light1pos[4];
		GLfloat light1dif[4];
		GLfloat light2pos[4];
		GLfloat light2dif[4];
		
		GLUquadric* GLUQ;
		
	public:
		FlightGame();
		
		int Execute();
		void Initialize();
		void Loop();
		
		void InputHandler();
		void Logic();
		void Physics();
		void Render3D();
		void Render2D();
		
		void Exit();
		void Cleanup();
};

#endif
