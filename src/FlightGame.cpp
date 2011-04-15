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
	WIDTH = DesktopMode.Width;
	HEIGHT = DesktopMode.Height;
	ASPECT = float(WIDTH)/float(HEIGHT);
	Window.Create(DesktopMode, "FlightGame", sf::Style::Fullscreen, OGLContext);
	Window.SetActive();
	
	Window.ShowMouseCursor(false);
	Window.SetCursorPosition(WIDTH/2, HEIGHT/2);
	mX = WIDTH/2; mY = HEIGHT/2;
	
	// Setup Arena
	// Ship
	FGArena.Register( new Ship( V3D(0, 0, 0), 1 ) );
	// Orbs
	Orb* BallA = FGArena.Register( new Orb ( V3D(0, 0, -6), 1 ) );
	Orb* BallB = FGArena.Register( new Orb ( V3D(2, 4, -7), 1 ) );
	Orb* BallC = FGArena.Register( new Orb ( V3D(6, 3, -4), 2 ) );
	Orb* BallD = FGArena.Register( new Orb ( V3D(1, -4, 2), .5 ) );
	// Strands
	FGArena.Register( new Strand ( BallA, BallB, 10 ) );
	FGArena.Register( new Strand ( BallB, BallC, 10 ) );
	FGArena.Register( new Strand ( BallA, BallC, 2 ) );
	FGArena.Register( new Strand ( BallD, BallA, 10 ) );
	FGArena.Register( new Strand ( BallD, BallB, 10 ) );
		
	// Camera
	Cam.Settings(90, ASPECT, .1, 500);
	Cam.Attach(FGArena.Ships[0]);
	
	
	/////////////////////////////////
	// Let the OpenGL setup begin! //
	/////////////////////////////////
	
	// Color & Depth Clear Values
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	// Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	// Fog
	glEnable(GL_FOG);
//	glFogi(GL_FOG_MODE, GL_EXP2);
//	glFogf(GL_FOG_DENSITY, .05);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 40.f);
	glFogf(GL_FOG_END, 500.f);
	float FogCol[3]={0, 0, 0};
	glFogfv(GL_FOG_COLOR, FogCol);
	
	// Lighting
	GLfloat ambientcolor[] = {.15, .15, .15, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	// Lights
	glEnable(GL_LIGHT0);
		light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
		light0dif[0] = 1; light0dif[1] = .8; light0dif[2] = .8; light0dif[3] = 1;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
		light1dif[0] = .4; light1dif[1] = 1; light1dif[2] = .2; light1dif[3] = 1;
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		light2pos[0] = -2; light2pos[1] = 10; light2pos[2] = -1; light2pos[3] = 1;
		light2dif[0] = .3; light2dif[1] = .2; light2dif[2] = 1;  light2dif[3] = 1;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	
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
			std::cerr << "ERROR: Physics Safety Valve Tripped!\n";
		}
		while (TimeStack >= 1/100.f) {
			PhysicalInput();
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
