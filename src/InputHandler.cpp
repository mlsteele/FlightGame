#include "FlightGame.h"

void FlightGame::InputHandler() {
	const sf::Input &WInput = Window.GetInput();
	Ship& MainShip = *(FGArena.Ships[0]);
	
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
	
	// Tractor Beam
	MainShip.TractorOff();
	if ( WInput.IsKeyDown(sf::Key::LShift) ) {
		MainShip.TractorIn();
	}
	if ( WInput.IsKeyDown(sf::Key::RShift) ) {
		MainShip.TractorOut();
	}
}

void FlightGame::PhysicalInput() {
	const sf::Input &WInput = Window.GetInput();
	Ship& MainShip = *(FGArena.Ships[0]);
	Orb& BallA = *(FGArena.Orbs[0]);
	
	// BallA Control
	float thrust = 0.0002;
	if ( WInput.IsKeyDown(sf::Key::I) ) {
		BallA.PushGlobal(0, 0, -thrust);
	}
	if ( WInput.IsKeyDown(sf::Key::K) ) {
		BallA.PushGlobal(0, 0, thrust);
	}
	if ( WInput.IsKeyDown(sf::Key::J) ) {
		BallA.PushGlobal(-thrust, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::L) ) {
		BallA.PushGlobal(thrust, 0, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::U) ) {
		BallA.PushGlobal(0, thrust, 0);
	}
	if ( WInput.IsKeyDown(sf::Key::O) ) {
		BallA.PushGlobal(0, -thrust, 0);
	}
	
	if ( WInput.IsKeyDown(sf::Key::RShift) ) {
		if ( ((MainShip.Pos + MainShip.Fd*5) - BallA.Pos).Length() < 5 ) {
			BallA.PushGlobal( MainShip.Fd.Normalized()/100 );
		}
	}
}
