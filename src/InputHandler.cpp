#include "FlightGame.h"

void FlightGame::InputHandler() {
	const sf::Input &WInput = Window.GetInput();
	
	// TODO: Find more elegant solution
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
}

void FlightGame::PhysicalInput() {
	const sf::Input &WInput = Window.GetInput();
	
	//// Main Ship Control
	// Translate
	float thrust = 0.001;
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
		MainShip.Roll(-.01);;
	}
	if ( WInput.IsKeyDown(sf::Key::E) ) {
		MainShip.Roll(.01);;
	}
	
	// Pitch & Yaw
	if (sqrt(pow(mX-WIDTH/2, 2) + pow(mY-HEIGHT/2, 2)) > 20) {
		MainShip.Yaw( ((mX - WIDTH/2)/float(WIDTH)) * -.04 );
		MainShip.Pitch( ((mY - HEIGHT/2)/float(HEIGHT)) * -.04*ASPECT );
	}
	
	//// BallA Control
	thrust = 0.0002;
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
	
	// Tractor Beam!
	if ( WInput.IsKeyDown(sf::Key::LShift) ) {
		if ( ((MainShip.Pos + MainShip.Fd*5) - BallA.Pos).Length() > 2 ) {
			BallA.PushGlobal( ((MainShip.Pos + MainShip.Fd* 5) - BallA.Pos).Normalized()*.1 );
		} else {
			BallA.Vel *= .7;
		}
	}
	if ( WInput.IsKeyDown(sf::Key::RShift) ) {
		if ( ((MainShip.Pos + MainShip.Fd*5) - BallA.Pos).Length() < 5 ) {
			BallA.PushGlobal( MainShip.Fd.Normalized()/100 );
		}
	}
}
