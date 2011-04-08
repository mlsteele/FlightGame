#include <iostream>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Oggler.h"

int main(int argc, char** argv) {
	
	sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode();
	sf::ContextSettings OGLContext(
		24,	// depth
		8,	// stencil
		4,	// antialiasing
		2,	// major
		0);	// minor
	float WIDTH = DesktopMode.Width;
	float HEIGHT = DesktopMode.Height;
	float AspectRatio = float(WIDTH)/float(HEIGHT);
	sf::Window Window(DesktopMode, "SFML Window", sf::Style::Fullscreen, OGLContext);
	Window.SetActive();
	
	const sf::Input& WInput = Window.GetInput();
	Window.ShowMouseCursor(false);
	Window.SetCursorPosition(WIDTH/2, HEIGHT/2);
	GLUquadric* MouseQuadric = gluNewQuadric();
	
	bool Running = true;
	
	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
//	// glFog Setup
//	glFogi(GL_FOG_MODE, GL_EXP2);
//	glFogf(GL_FOG_DENSITY, .05);
//	glEnable(GL_FOG);
	
	// General Lighting
	GLfloat ambientcolor[] = {.2, .2, .2, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	// Individual Lights
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	GLfloat light0pos[] = {0, 0, -1, 1};
	GLfloat light0dif[] = {1, .8, .8, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	GLfloat light1pos[] = {5, -2, 8, 1};
	GLfloat light1dif[] = {.4, 1, .2, 1};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	GLfloat light2pos[] = {-2, 10, -15, 1};
	GLfloat light2dif[] = {.3, .2, 1, 1};
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	
	// Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, AspectRatio, .1f, 500.f);
	glMatrixMode(GL_MODELVIEW);
	
	// Camera Setup
	Oggler Cam;
	
	sf::Event Event;
	// Array to store whether or not keys are pressed
	bool Keys[500]; // Arbitrary large length; TODO: find out what it should be
	// Zero out Keys
	for (int i=0; i < 256; ++i) {Keys[i] = false;}
	
	// Main Loop
	while (Running) {
		
		// Event Handling
		while (Window.GetEvent(Event)) {
			if (Event.Type == sf::Event::Closed)
				{Running = false;}
			else if (Event.Type == sf::Event::KeyPressed) {
				if (Event.Key.Code == sf::Key::Escape)
					{Running = false; }
				else if (Event.Key.Code == sf::Key::O) {
					Cam.Zero();
					Window.SetCursorPosition(WIDTH/2, HEIGHT/2);
					
				}
				else if (Event.Key.Code == sf::Key::W)
					{Keys[Event.Key.Code] = true;}
				else if (Event.Key.Code == sf::Key::A)
					{Keys[Event.Key.Code] = true;}
				else if (Event.Key.Code == sf::Key::S)
					{Keys[Event.Key.Code] = true;}
				else if (Event.Key.Code == sf::Key::D)
					{Keys[Event.Key.Code] = true;}
				else if (Event.Key.Code == sf::Key::Q)
					{Keys[Event.Key.Code] = true;}
				else if (Event.Key.Code == sf::Key::E)
					{Keys[Event.Key.Code] = true;}
			}
			else if (Event.Type == sf::Event::KeyReleased) {
				if (Event.Key.Code == sf::Key::W)
					{Keys[Event.Key.Code] = false;}
				else if (Event.Key.Code == sf::Key::A)
					{Keys[Event.Key.Code] = false;}
				else if (Event.Key.Code == sf::Key::S)
					{Keys[Event.Key.Code] = false;}
				else if (Event.Key.Code == sf::Key::D)
					{Keys[Event.Key.Code] = false;}
				else if (Event.Key.Code == sf::Key::Q)
					{Keys[Event.Key.Code] = false;}
				else if (Event.Key.Code == sf::Key::E)
					{Keys[Event.Key.Code] = false;}
			}
			else if (Event.Type == sf::Event::Resized)
				{glViewport(0, 0, Event.Size.Width, Event.Size.Height);}
		}
				
		// Setup a perspective projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.f, AspectRatio, .1f, 500.f);
		glMatrixMode(GL_MODELVIEW);
		
		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Render camera axis
		glPushMatrix();
		glTranslatef(0, 0, -1);
		glScalef(.25, .25, .25);
		glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(-1*Cam.Up.x, -1*Cam.Up.y, -1*Cam.Up.z);
			
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(-1*Cam.Rt.x, -1*Cam.Rt.y, -1*Cam.Rt.z);
			
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(-1*Cam.Fd.x, -1*Cam.Fd.y, -1*Cam.Fd.z);
		glEnd();
		glPopMatrix();
		
		// Apply camera transform
		Cam.View();
		
		// Camera Translation Handling
		if (Keys[sf::Key::W])
			{Cam.TranslateLocal(0, 0, .1);}
		if (Keys[sf::Key::A])
			{Cam.TranslateLocal(.1, 0, 0);}
		if (Keys[sf::Key::S])
			{Cam.TranslateLocal(0, 0, -.1);}
		if (Keys[sf::Key::D])
			{Cam.TranslateLocal(-.1, 0, 0);}

		// Camera Rotation
		if (
				sqrt(
					pow(
						(WInput.GetMouseX()-(WIDTH/2.f))
						, 2)
					+
					pow(
						(WInput.GetMouseY()-(HEIGHT/2.f))
						, 2)
				)
			> 50.f)
		{
			Cam.Yaw((WInput.GetMouseX()-(WIDTH/2.f))/float(WIDTH) * -.4);
			Cam.Pitch((WInput.GetMouseY()-(HEIGHT/2.f))/float(HEIGHT) * .4);
		}
		
		// Camera Roll
		if (Keys[sf::Key::E]) {
			Cam.Roll(.03);
		}
		if (Keys[sf::Key::Q]) {
			Cam.Roll(-.03);
		}
		
		// Enable Lighting
		// Update Light Positions
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
		glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
		
		// Draw a sphere
		glPushMatrix();
		glTranslatef(0.f, 0.f, -6.f);
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
		
		// Draw a Spiral!
		glPushMatrix();
		glColor3f(1.0f, 0.80f, 0.20f);
		for (int spix = 0; spix < 500; ++spix) {
			glBegin(GL_POINTS);
				glVertex3f(0, 0, 0);
			glEnd();
			glTranslatef(.1, .01, .1);
			glRotatef(1, 0, 1, 0);
			glRotatef(1, 1, 0, 0);
			glScalef(.994, .994, .994);
		}
		glPopMatrix();
		
		// Draw a Spiral!
		glPushMatrix();
		glScalef(-1, 1, 1);
		glTranslatef(-5, 0, 0);
		glColor3f(0.0f, 0.80f, 0.00f);
		for (int spix = 0; spix < 500; ++spix) {
			glBegin(GL_POINTS);
				glVertex3f(0, 0, 0);
			glEnd();
			glTranslatef(.1, .01, .1);
			glRotatef(1, 0, 1, 0);
			glRotatef(1, 1, 0, 0);
			glScalef(.994, .994, .994);
		}
		glPopMatrix();
		
		// Draw a grid
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
		
		
		// 2D Rendering Setup
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// 2D objects
		
		// 2D mid-screen
		glPushMatrix();
		glTranslatef(WIDTH/2, HEIGHT/2, -.1);
		glColor3f(.1, .05, .3);
		gluDisk(MouseQuadric, 47, 50, 32, 1);
		glPopMatrix();
		
		// 2D mouse cursor
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(WInput.GetMouseX(), WInput.GetMouseY(), 0);
		glColor3f(.7, .3, .8);
		glBegin(GL_TRIANGLES);
			glVertex3f(10, 0, 0);
			glVertex3f(-10, 0, 0);
			glVertex3f(0, 10, 0);
		glEnd();
		glColor3f(.4,.2,1);
		gluDisk(MouseQuadric, 15, 20, 4, 1);
		glPopMatrix();
		
		// Display Window
		Window.Display();
		
	}
	
	return EXIT_SUCCESS;
}
