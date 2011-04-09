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
	
	/////////////////////////////////
	// Let the OpenGL setup begin! //
	/////////////////////////////////
	
	// Color & Depth Clear Values
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	// Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
//	// Fog
//	glFogi(GL_FOG_MODE, GL_EXP2);
//	glFogf(GL_FOG_DENSITY, .05);
//	glEnable(GL_FOG);
	
	// Lighting
	GLfloat ambientcolor[] = {.2, .2, .2, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	// Lights
	glEnable(GL_LIGHT0);
		GLfloat light0pos[4] = {0, 0, -1, 1};
		GLfloat light0dif[4] = {1, .8, .8, 1};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		GLfloat light1pos[4] = {5, -2, 8, 1};
		GLfloat light1dif[4] = {.4, 1, .2, 1};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		GLfloat light2pos[4] = {-2, 10, -15, 1};
		GLfloat light2dif[4] = {.3, .2, 1, 1};
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	
	// Quadric (Misc)
	GLUQ = gluNewQuadric();
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
		
		Render3D();
		Render2D();
		Window.Display();
	}
	
	Cleanup();
	
	return EXIT_SUCCESS;
}


void FlightGame::InputHandler() {
	mX = Window.GetInput().GetMouseX();
	mY = Window.GetInput().GetMouseY();
	
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


void FlightGame::Render3D() {
	// Enable Depth
	glEnable(GL_DEPTH_TEST);
	
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, ASPECT, .1f, 500.f);
	glMatrixMode(GL_MODELVIEW);
	
	// Enable lighting & update light positions
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
}

void FlightGame::Render2D() {
	// Disable Depth
	glDisable(GL_DEPTH_TEST);
	
	// Orthographic Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Lighting Disable
	glDisable(GL_LIGHTING);
	
	// Mid-Screen Circle
	glPushMatrix();
	glTranslatef(WIDTH/2, HEIGHT/2, 0);
	glColor3f(.1, .05, .3);
	gluDisk(GLUQ, 17, 20, 32, 1);
	glPopMatrix();
	
	// Mouse Cursor
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mX, mY, 0);
	glScalef(.7, .7, 1);
	glColor3f(.7, .3, .8);
	glBegin(GL_TRIANGLES);
		glVertex3f(10, 0, 0);
		glVertex3f(-10, 0, 0);
		glVertex3f(0, 10, 0);
	glEnd();
	glColor3f(.4, .2, 1);
	gluDisk(GLUQ, 15, 20, 4, 1);
	glPopMatrix();
}

void FlightGame::Exit() {
	Running = false;
}


void FlightGame::Cleanup() {
	Window.Close();
}
