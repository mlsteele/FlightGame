#include "FlightGame.h"

void FlightGame::InputHandler() {
	Ship& MainShip = *(*FGArena.Ships.begin());

	// Initialize or stash mouse position
	if (nFrame < 2){
		mX = WIDTH/2;
		mY = HEIGHT/2;
	} else {
		mX = sf::Mouse::getPosition(Window).x;
		mY = sf::Mouse::getPosition(Window).y;
	}

	sf::Event event;
	while (Window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			Exit();
		}
		else if (event.type == sf::Event::Resized) {
			glViewport(0, 0, event.size.width, event.size.height);
		}

		// MainShip
		// Firing on mouse
		else if (event.type == sf::Event::MouseButtonPressed) {
			MainShip.Shoot();
		}
//		else if (event.type == sf::Event::MouseButtonReleased) {
//			MainShip.ConnectOff();
//		}
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
		Exit();
	}

	// Main Ship Control
	// Translate
	MainShip.KillThrust();
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
		MainShip.AddThrust(0, 0, 1);
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
		MainShip.AddThrust(0, 0, -1);
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
		MainShip.AddThrust(-1, 0, 0);
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
		MainShip.AddThrust(1, 0, 0);
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R) ) {
		MainShip.AddThrust(0, 1, 0);
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::F) ) {
		MainShip.AddThrust(0, -1, 0);
	}

	// Brake
	MainShip.BrakeOff();
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt) ) {
		MainShip.ConnectOn();
	} else {
		MainShip.ConnectOff();
	}

	MainShip.KillRot();
	// Pitch & Yaw
//	if (sqrt(pow(mX-WIDTH/2, 2) + pow(mY-HEIGHT/2, 2)) > 20) {
		MainShip.AddYaw( ((mX - WIDTH/2)/float(WIDTH)) * -.04 );
		MainShip.AddPitch( ((mY - HEIGHT/2)/float(HEIGHT)) * -.04*ASPECT );
//	}

	// Roll
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ) {
		MainShip.AddRoll(-.01);;
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E) ) {
		MainShip.AddRoll(.01);;
	}

	// Grapple
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
		MainShip.GrappleOn();
	else
		MainShip.GrappleOff();

	// Tractor Beam
	MainShip.TractorOff();
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ) {
		MainShip.TractorIn();
	}
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) ) {
		MainShip.TractorOut();
	}
}
