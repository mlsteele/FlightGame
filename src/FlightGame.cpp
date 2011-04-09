#include "FlightGame.h"

FlightGame::FlightGame() {}


void FlightGame::Initialize() {
	Running = true;
	nFrame = 0;
	Clock.Reset();
	TimeStack = 0;
	
	sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode();
	sf::ContextSettings OGLContext(
		24,	// depth
		8,	// stencil
		4,	// antialiasing
		2,	// major
		0);	// minor
	WIDTH = DesktopMode.Width;
	HEIGHT = DesktopMode.Height;
	ASPECT = float(WIDTH)/float(HEIGHT);
	Window.Create(DesktopMode, "FlightGame", sf::Style::Fullscreen, OGLContext);
	Window.SetActive();
	
	Window.ShowMouseCursor(false);
	Window.SetCursorPosition(WIDTH/2, HEIGHT/2);
}


int FlightGame::Execute() {
	Initialize();
	
	while (Running) {
		++nFrame;
		
		InputHandler();
		
		Logic();
		
		// Update physics n frames pers second, maximum updates
		TimeStack += Clock.GetElapsedTime();
		Clock.Reset();
		if (TimeStack >= .2) {TimeStack = .2;} // Safety for spiral of death
		while (TimeStack >= 1/60.f) {
			Physics();
			TimeStack -= 1/60.f;
		}
		
		Render();
	}
	
	Cleanup();
	
	return EXIT_SUCCESS;
}


void FlightGame::InputHandler() {
	float mx = Window.GetInput().GetMouseX();
	float my = Window.GetInput().GetMouseY();
	
	while (Window.GetEvent(Event)) {
		if (Event.Type == sf::Event::Closed) {
			Exit();
		}
		else if (Event.Type == sf::Event::KeyPressed) {
			if (Event.Key.Code == sf::Key::Escape) {
				Exit();
			}
		}
	}
}


void FlightGame::Logic() {
	
}


void FlightGame::Physics() {
	
}


void FlightGame::Render() {
	Window.Display();
}


void FlightGame::Exit() {
	Running = false;
}


void FlightGame::Cleanup() {
	Window.Close();
}
