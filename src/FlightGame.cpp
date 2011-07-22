#include "FlightGame.h"

FlightGame::FlightGame() :
	  Running (false)
{
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
	std::string windowName = "FlightGame";
	
	// Fullscreen Switch
	if (true) {
		WIDTH = DesktopMode.Width;
		HEIGHT = DesktopMode.Height;
		ASPECT = WIDTH/HEIGHT;
		Window.Create(DesktopMode, windowName, sf::Style::Fullscreen, OGLContext);
	} else {
		WIDTH = 800;
		HEIGHT = 600;
		ASPECT = WIDTH/HEIGHT;
		Window.Create(sf::VideoMode(WIDTH, HEIGHT), windowName, sf::Style::Default, OGLContext);
	}
	
	Window.SetActive();
	Window.ShowMouseCursor(false);
	Window.SetCursorPosition(WIDTH/2, HEIGHT/2);
	mX = WIDTH/2; mY = HEIGHT/2;
	
	// Setup Arena
	// Ship
	Ship& MainShip = *FGArena.Register( new Ship( V3D(0, 0, 100), &FGArena) );
	
	// Random Orbs
	for (int i = 0; i < 40; ++i) {
		V3D randpos(
			  (rand() / static_cast<float>(RAND_MAX) * 50) - 25
			, (rand() / static_cast<float>(RAND_MAX) * 50) - 25
			, (rand() / static_cast<float>(RAND_MAX) * 50) - 25
		);
		FGArena.Register( new Orb ( randpos, 1.f ) );
	}
	
	for (int i = 0; i < 4; ++i) {
		V3D randpos(
			  (rand() / static_cast<float>(RAND_MAX) * 50) - 25
			, (rand() / static_cast<float>(RAND_MAX) * 50) - 25
			, (rand() / static_cast<float>(RAND_MAX) * 50) - 25
		);
		FGArena.Register( new Orb ( randpos, 5.f ) );
	}
	
	// Camera
	Cam.Settings(90, ASPECT, .1, 500);
	Cam.Attach(*FGArena.Ships.begin());
	
	
	/////////////////////////////////
	// Let the OpenGL setup begin! //
	/////////////////////////////////
	
	// Color & Depth Clear Values
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	// Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	// Lighting
	GLfloat ambientcolor[] = {.6, .6, .6, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	// Fog
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, .012);
//	glFogi(GL_FOG_MODE, GL_LINEAR);
//	glFogf(GL_FOG_START, 40.f);
//	glFogf(GL_FOG_END, 100.f);
	float FogCol[3] = {0,0,.2};
	glFogfv(GL_FOG_COLOR, FogCol);
	
	// Lights
	glEnable(GL_LIGHT0);
		light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
		light0dif[0] = .3; light0dif[1] = .15; light0dif[2] = .15; light0dif[3] = 1;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
		light1dif[0] = .3; light1dif[1] = .8; light1dif[2] = .1; light1dif[3] = 1;
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		light2pos[0] = -2; light2pos[1] = 10; light2pos[2] = -1; light2pos[3] = 1;
		light2dif[0] = .3; light2dif[1] = .2; light2dif[2] = 1;  light2dif[3] = 1;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	glEnable(GL_LIGHT3);
		light3pos[0] = -140; light3pos[1] = -110; light3pos[2] = 70; light3pos[3] = 1;
		light3dif[0] = .3; light3dif[1] = 0; light3dif[2] = 0;  light3dif[3] = 1;
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3dif);
	
	// Quadric (Misc)
	GLUQ = gluNewQuadric();
}


int FlightGame::Execute() {
	Running = true;
	
	while (Running) {
		++nFrame;
		
		InputHandler();
		
		Logic();
		
		// Cheese Grater Physics
		// Update physics n frames pers second, maximum updates
		TimeStack += Clock.GetElapsedTime();
		Clock.Reset();
		// Safety for spiral of death
		if (TimeStack >= .2) {
			TimeStack = .2;
			std::cerr << "ERROR: " << __TIME__ << ": Physics Safety Valve Tripped!\n";
		}
		while (TimeStack >= 1/100.f) {
			Physics();
			TimeStack -= 1/100.f;
		}
		
		Render3D();
		Render2D();
		
		Window.Display();
	}
	
	Cleanup();
	
	return EXIT_SUCCESS;
}


void FlightGame::Logic() {
	
}


void FlightGame::Physics() {
	FGArena.Update();
}

void FlightGame::Exit() {
	Running = false;
}


void FlightGame::Cleanup() {
	Window.Close();
}
