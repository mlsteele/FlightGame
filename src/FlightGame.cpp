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
	if (false) {
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
	Ship& MainShip = *FGArena.Register( new Ship( V3D<float>(0, 0, FGArena.asize), &FGArena) );
	// Hammer
//	Orb* Hammer = FGArena.Register( new Orb(
//		MainShip.Pos + MainShip.Fd * 10, 1) );
//	FGArena.Register(new Strand(&MainShip, Hammer));
	
	// Create random orbs
	int smalln = 400;
	Orb* smalls[smalln];
	int bign = 40;
	Orb* bigs[bign];
	int rcons = 10;
	
	// smalls
	for (int i = 0; i < smalln; ++i) {
		V3D<float> randpos(
			  (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
			, (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
			, (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
		);
		smalls[i] = FGArena.Register( new Orb ( randpos, 1 ) );
	}
	
	// bigs
	for (int i = 0; i < bign; ++i) {
		V3D<float> randpos(
			  (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
			, (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
			, (rand() / static_cast<float>(RAND_MAX) * FGArena.asize*2) - FGArena.asize
		);
		bigs[i] = FGArena.Register( new Orb ( randpos, 5 ) );
	}
	
	// random connections
	floop:
	for (int i = 0; i < smalln; ++i)
		for (int j = i+1; j < smalln; ++j)
			if ( ((smalls[i]->Pos - smalls[j]->Pos).Length() < 70) && (rcons > 0) ) {
				FGArena.Register(new Strand(smalls[i], smalls[j], 10));
				--rcons;
				if (j-i > 2)
					++i;
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
	glFogf(GL_FOG_DENSITY, .005);
//	glFogi(GL_FOG_MODE, GL_LINEAR);
//	glFogf(GL_FOG_START, 40.f);
//	glFogf(GL_FOG_END, 100.f);
	float FogCol[3] = {0,0,0};
	glFogfv(GL_FOG_COLOR, FogCol);
	
	// Lights
	glEnable(GL_LIGHT0);
		light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
		light0dif[0] = .2; light0dif[1] = .2; light0dif[2] = .2; light0dif[3] = 1;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
		light1dif[0] = .2; light1dif[1] = .2; light1dif[2] = .2; light1dif[3] = 1;
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		light2pos[0] = -2; light2pos[1] = 10; light2pos[2] = -1; light2pos[3] = 1;
		light2dif[0] = .2; light2dif[1] = .2; light2dif[2] = .2;  light2dif[3] = 1;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	glEnable(GL_LIGHT3);
		light3pos[0] = -140; light3pos[1] = -110; light3pos[2] = 70; light3pos[3] = 1;
		light3dif[0] = .2; light3dif[1] = .2; light3dif[2] = .2;  light3dif[3] = 1;
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
			std::cerr << "WARN: " << __TIME__ << ": Physics Safety Valve Tripped!\n";
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
