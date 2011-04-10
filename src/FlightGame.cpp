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
	mX = WIDTH/2; mY = HEIGHT/2;
	
	
	// Camera, Ship, Object Setup
	Ball.Pos = V3D(0, 0, -6);
	Cam.Attach(&MainShip);
	
	
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
		light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
		light0dif[0] = 1; light0dif[1] = .8; light0dif[2] = .8; light0dif[3] = 1;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
		light1dif[0] = .4; light1dif[1] = 1; light1dif[2] = .2; light1dif[3] = 1;
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		light1pos[0] = -2; light1pos[1] = 10; light1pos[2] = -1; light1pos[3] = 1;
		light1dif[0] = .3; light1dif[1] = .2; light1dif[2] = 1; light1dif[3] = 1;
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
		
		// Cheese Grater Physics
		// Update physics n frames pers second, maximum updates
		TimeStack += Clock.GetElapsedTime();
		Clock.Reset();
		// Safety for spiral of death
		if (TimeStack >= .2) {
			TimeStack = .2;
			std::cerr << "Physics Safety Valve Tripped!";
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
	MainShip.Update();
	Ball.Update();
}


void FlightGame::Render3D() {
	// Enable Depth
	glEnable(GL_DEPTH_TEST);
	
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float FOV = 1/17.;
	glFrustum(-ASPECT*FOV, ASPECT*FOV, -1*FOV, 1*FOV, .1, 500);
	glMatrixMode(GL_MODELVIEW);
		
	// Camera Transformation
	Cam.View();
	
	// Axis visualization
	glTranslatef(0, 0, -1);
	glBegin(GL_LINES);
		// Red X
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		
		// Green Y
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		
		// Blue Z
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
	glEnd();
	
	// Enable lighting & update light positions
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
	
	// Draw a sphere (as PushMe avatar)
	glPushMatrix();
	glTranslatef(Ball.Pos.x, Ball.Pos.y, Ball.Pos.z);
	glColor3f(1, .5, .5);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();
	
	// Draw a square with colors
	glPushMatrix();
	glTranslatef(5.f, 0.f, -10.f);
	glBegin(GL_QUADS);
		glColor3f(1, .2, .2);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glColor3f(.2, .2, 1);
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glColor3f(.2, 1, .2);
		glVertex3f(-1.0f,-1.0f, 0.0f);
	glEnd();
	glPopMatrix();
	
	// Draw a grid
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0f, 0.80f, 0.90f);
	int griddims[3] = {20, 20, 20};
	glTranslatef(-griddims[0], -griddims[1], -griddims[2]);
	for (int gridx = 0; gridx < griddims[0]; ++gridx) {
		for (int gridy = 0; gridy < griddims[1]; ++gridy) {
			for (int gridx = 0; gridx < griddims[0]; ++gridx) {
				
				glBegin(GL_POINTS);
					glVertex3f(0, 0, 0);
				glEnd();
				
				glTranslatef(0, 0, 2);
			}
			glTranslatef(2, 0, 0);
			glTranslatef(0, 0, -2*griddims[2]);
		}
		glTranslatef(-2*griddims[1], 0, 0);
		glTranslatef(0, 2, 0);
	}
	glPopMatrix();
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
