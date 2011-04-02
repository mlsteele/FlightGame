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
	gluPerspective(90.f, 1.f, 1.f, 500.f);
	
	sf::Event Event;
	while (Running) {
		// Event Handling
		while (Window.GetEvent(Event)) {
			if (Event.Type == sf::Event::Closed) {
				Running = false;
			} else if (Event.Type == sf::Event::KeyPressed) {
				if (Event.Key.Code == sf::Key::Escape) {
					Running = false;
				}
			} else if (Event.Type == sf::Event::Resized) {
			    glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}
		}
		
		
		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluPerspective(90.f, AspectRatio, 1.f, 500.f);
		
		glTranslatef(0.f, 0.f, -6.f);
		glColor3f(0.0f,0.0f,1.0f);
		glutSolidSphere(1, 8, 8);
		
		glTranslatef(3.f, 0.f, 0.f);
		glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glVertex3f( 1.0f, 1.0f, 0.0f);
			glVertex3f( 1.0f,-1.0f, 0.0f);
			glVertex3f(-1.0f,-1.0f, 0.0f);
		glEnd();
		
		// Display Window (yep)
		Window.Display();
		
	}
	
	return EXIT_SUCCESS;
}
