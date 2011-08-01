#include "FlightGame.h"

void FlightGame::InputHandler() {
	const sf::Input &WInput = Window.GetInput();
	Ship& MainShip = *(*FGArena.Ships.begin());
	
	// Initialize or stash mouse position
	if (nFrame < 2){
		mX = WIDTH/2;
		mY = HEIGHT/2;
	} else {
		mX = WInput.GetMouseX();
		mY = WInput.GetMouseY();
	}
	
	while (Window.GetEvent(Event)) {
		if (Event.Type == sf::Event::Closed) {
			Exit();
		}
		else if (Event.Type == sf::Event::Resized) {
			glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}
		
		// MainShip
		// Firing on mouse
		else if (Event.Type == sf::Event::MouseButtonPressed) {
			MainShip.Shoot();
		}
//		else if (Event.Type == sf::Event::MouseButtonReleased) {
//			MainShip.ConnectOff();
//		}
	}
	if ( WInput.IsKeyDown(sf::Key::Escape) ) {
		Exit();
	}
	
	// Main Ship Control
	// Translate
	MainShip.KillThrust();
	if ( WInput.IsKeyDown(sf::Key::W) ) {
		MainShip.AddThrust(0, 0, 1);
	}
	if ( WInput.IsKeyDown(sf::Key::S) ) {
		MainShip.AddThrust(0, 0, -1);
	}
	if ( WInput.IsKeyDown(sf::Key::A) ) {
		MainShip.AddThrust(-1, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::D) ) {
		MainShip.AddThrust(1, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::R) ) {
		MainShip.AddThrust(0, 1, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::F) ) {
		MainShip.AddThrust(0, -1, 0);
	}
	
	// Brake
	MainShip.BrakeOff();
	if ( WInput.IsKeyDown(sf::Key::RAlt) ) {
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
	if ( WInput.IsKeyDown(sf::Key::Q) ) {
		MainShip.AddRoll(-.01);;
	}
	if ( WInput.IsKeyDown(sf::Key::E) ) {
		MainShip.AddRoll(.01);;
	}
	
	// Grapple
	if ( WInput.IsKeyDown(sf::Key::Space) )
		MainShip.GrappleOn();
	else
		MainShip.GrappleOff();
	
	// Tractor Beam
	MainShip.TractorOff();
	if ( WInput.IsKeyDown(sf::Key::LShift) ) {
		MainShip.TractorIn();
	}
	if ( WInput.IsKeyDown(sf::Key::RShift) ) {
		MainShip.TractorOut();
	}
}
