#include <iostream>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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
	
	bool Running = true;
	
	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, AspectRatio, 1.f, 500.f);
	
	// Setup Camera Matrix
	float CamMat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, CamMat);
//	// Print Camera (Current) Matrix to stdout
//	for (int i=0; i < 16; ++i)
//		{ std::cout << CamMat[i] << "\n"; }
	
	sf::Event Event;
	
	// Main Loop
	while (Running) {
		
		// Rendering Setup
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glMultMatrixf(CamMat); // Camera transformation
		
		// Event Handling
		while (Window.GetEvent(Event)) {
			if (Event.Type == sf::Event::Closed)
				{Running = false;}
			else if (Event.Type == sf::Event::KeyPressed) {
				if (Event.Key.Code == sf::Key::Escape)
					{Running = false; }
				else if (Event.Key.Code == sf::Key::W)
					{glTranslatef(0, 0, .1);}
				else if (Event.Key.Code == sf::Key::A)
					{glTranslatef(.1, 0, 0);}
				else if (Event.Key.Code == sf::Key::S)
					{glTranslatef(0, 0, -.1);}
				else if (Event.Key.Code == sf::Key::D)
					{glTranslatef(-.1, 0, 0);}
			} else if (Event.Type == sf::Event::Resized)
				{glViewport(0, 0, Event.Size.Width, Event.Size.Height);}
		}
		
		// Reassign camera matrix after event handling
		glGetFloatv(GL_PROJECTION_MATRIX, CamMat);
		
		// Draw a sphere
		glPushMatrix();
		glTranslatef(0.f, 0.f, -6.f);
		glColor3f(0.0f,0.0f,1.0f);
		glutSolidSphere(1, 8, 8);
		glPopMatrix();
		
		// Draw a square with colors
		glPushMatrix();
		glTranslatef(5.f, 0.f, -10.f);
		glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glVertex3f( 1.0f, 1.0f, 0.0f);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f( 1.0f,-1.0f, 0.0f);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(-1.0f,-1.0f, 0.0f);
		glEnd();
		glPopMatrix();
		
		// Display Window
		Window.Display();
		
	}
	
	return EXIT_SUCCESS;
}
