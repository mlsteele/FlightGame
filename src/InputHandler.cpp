#include "FlightGame.h"

void FlightGame::InputHandler() {
	const sf::Input &WInput = Window.GetInput();
	
	mX = WInput.GetMouseX();
	mY = WInput.GetMouseY();
	
	while (Window.GetEvent(Event)) {
		if (Event.Type == sf::Event::Closed) {
			Exit();
		}
		else if (Event.Type == sf::Event::Resized) {
			glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}
	}
	if ( WInput.IsKeyDown(sf::Key::Escape) ) {
		Exit();
	}
	
	//// Main Ship Control
	// Translate
	float thrust = 0.002;
	if ( WInput.IsKeyDown(sf::Key::W) ) {
		MainShip.PushLocal(0, 0, thrust);
	}
	if ( WInput.IsKeyDown(sf::Key::S) ) {
		MainShip.PushLocal(0, 0, -thrust);
	}
	if ( WInput.IsKeyDown(sf::Key::A) ) {
		MainShip.PushLocal(-thrust, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::D) ) {
		MainShip.PushLocal(thrust, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::R) ) {
		MainShip.PushLocal(0, thrust, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::F) ) {
		MainShip.PushLocal(0, -thrust, 0);
	}
	
	// Roll
	if ( WInput.IsKeyDown(sf::Key::Q) ) {
		MainShip.Roll(-.02);;
	}
	if ( WInput.IsKeyDown(sf::Key::E) ) {
		MainShip.Roll(.02);;
	}
	
	// Pitch & Yaw
	if (sqrt(pow(mX-WIDTH/2, 2) + pow(mY-HEIGHT/2, 2)) > 20) {
		MainShip.Yaw( ((mX - WIDTH/2)/float(WIDTH)) * .08 );
		MainShip.Pitch( ((mY - HEIGHT/2)/float(HEIGHT)) * .08*ASPECT );
	}
	
	// Ball Control
	thrust = 0.0002;
	if ( WInput.IsKeyDown(sf::Key::I) ) {
		Exit();
	}
	if ( WInput.IsKeyDown(sf::Key::K) ) {
		Exit();
	}
	if ( WInput.IsKeyDown(sf::Key::J) ) {
		Exit();
	}
	if ( WInput.IsKeyDown(sf::Key::L) ) {
		Exit();
	}
	if ( WInput.IsKeyDown(sf::Key::U) ) {
		Exit();
	}

	if ( WInput.IsKeyDown(sf::Key::O) ) {
		Exit();
	}
}