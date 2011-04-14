#ifndef _FLIGHTGAME_H_
	#define _FLIGHTGAME_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Oggler.h"
#include "Pushable.h"
#include "Strand.h"
#include "Ship.h"

/// \brief Master game class
/// 
/// Holds objects and handles loop.
/// \n This class operates on a looping basis and contains two timescales.
/// \n The slower loop runs as fast as it can and includes Render3D() and Render2D().
/// \n The fast runs based on a cheesegrater implementation and includes Physics().

class FlightGame {
	public:
		// Process Properties
		bool Running;
		/// \brief Frame number
		unsigned int nFrame;
		sf::Clock Clock;
		/// \brief Time accumulator used for cheese-grater physics updates
		float TimeStack;
		
		// Window & Properties
		sf::Window Window;
		float WIDTH;
		float HEIGHT;
		/// \brief Aspect ratio
		float ASPECT;
		
		// Mouse Position and Input
		/// \brief Event container used for input analysis
		sf::Event Event;
		/// \brief Mouse X position (cache-like)
		float mX;
		/// \brief Mouse Y position (cache-like)
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
		/// \brief Primary game camera
		Oggler Cam;
		/// \brief View player's ship
		Ship MainShip;
		Pushable BallA;
		Pushable BallB;
		Pushable BallC;
		Pushable BallD;
		Strand StrandA;
		Strand StrandB;
		Strand StrandC;
		Strand StrandD;
		Strand StrandE;
	
	public:
		FlightGame();
		
		/// \brief Initiates loop
		int Execute();
		
		void Logic();
		
		/// \brief Evaluate physics
		///
		/// Called every 1/k seconds based on a cheesegrater implementation.
		/// As time passes, cheese is added to the TimeStack.
		/// Physics() is then run to grate off discrete chunks of unevaluated time.
		void Physics();
		
		// InputHandler.cpp
		/// \brief Handles per-frame input
		void InputHandler();
		/// \brief Handles input which affects physics (faster)
		void PhysicalInput();
		
		// Render.cpp
		/// \brief Render scenes 3D object or hand down to subordinates
		void Render3D();
		/// \brief Render 2D elements
		void Render2D();
		
		/// \brief Command to exit cleanly
		void Exit();
		/// \brief Wind-down and return
		void Cleanup();
};

#endif
