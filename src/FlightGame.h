#ifndef _FLIGHTGAME_H_
	#define _FLIGHTGAME_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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
	
	public:
		FlightGame();
		
		int Execute();
		void Initialize();
		void Loop();
		
		void InputHandler();
		void Logic();
		void Physics();
		void Render();
		
		void Exit();
		void Cleanup();
};

#endif
