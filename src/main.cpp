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
	
	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, AspectRatio, .1f, 500.f);
	glMatrixMode(GL_MODELVIEW);
	
	// Setup Camera Matrix
	float CamMat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, CamMat);
//	// Print Camera (Current) Matrix to stdout
//	for (int i=0; i < 16; ++i)
//		{ std::cout << CamMat[i] << "\n"; }
	
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
		
		// Rendering Setup
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		// Camera Rotation Handling
		glRotatef(
			(WInput.GetMouseX()-(WIDTH/2.f))/float(WIDTH) * 2,
			0, 1, 0);
		glRotatef(
			(WInput.GetMouseY()-(HEIGHT/2.f))/float(HEIGHT) * 2,
			1, 0, 0);
		if (Keys[sf::Key::E]) {
			glRotatef(
				.3,
				0, 0, 1);
		}
		if (Keys[sf::Key::Q]) {
			glRotatef(
				-.3,
				0, 0, 1);
		}
		
		// Camera Translation Handling
		if (Keys[sf::Key::W])
			{glTranslatef(0, 0, .1);}
		if (Keys[sf::Key::A])
			{glTranslatef(.1, 0, 0);}
		if (Keys[sf::Key::S])
			{glTranslatef(0, 0, -.1);}
		if (Keys[sf::Key::D])
			{glTranslatef(-.1, 0, 0);}
		
		// Camera application and reassignment
		glMultMatrixf(CamMat); // Camera transformation
		glGetFloatv(GL_MODELVIEW_MATRIX, CamMat);
		
		// Draw a sphere
		glPushMatrix();
		glTranslatef(0.f, 0.f, -6.f);
		glColor3f(0.0f,0.0f,1.0f);
		glutSolidSphere(1, 32, 32);
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
		
		// Draw a Spiral!
		glPushMatrix;
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
		glPopMatrix;
		
		// Draw a Spiral!
		glPushMatrix;
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
		glPopMatrix;
		
		// Draw a grid
		glPushMatrix;
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
		glPopMatrix;
		
		
		// 2D Rendering Setup
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// 2D objects (mouse cursor)
		glPushMatrix;
		glTranslatef(WInput.GetMouseX(), WInput.GetMouseY(), 0);
		glColor3f(.7, .3, .8);
		glBegin(GL_TRIANGLES);
			glVertex3f(10, 0, 0);
			glVertex3f(-10, 0, 0);
			glVertex3f(0, 10, 0);
		glEnd();
		glColor3f(.4,.2,1);
		gluDisk(MouseQuadric, 15, 20, 16, 1);
		glPopMatrix;
		
		// Display Window
		Window.Display();
		
	}
	
	return EXIT_SUCCESS;
}
