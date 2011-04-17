#include "FlightGame.h"

void FlightGame::Render3D() {
	Ship& MainShip = *(FGArena.Ships[0]);
	
	// Enable Depth
	glEnable(GL_DEPTH_TEST);
	
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Camera PERSPECTIVE Transformation
	Cam.ViewPerspective();
	
	// Velocity Visualizer
	V3D vdv = MainShip.Vel * 1;
	vdv = MainShip.OGTL(vdv);
	glPushMatrix();
	glTranslatef(-1.5, -1.5, -2);
	glBegin(GL_LINES);
		glColor3f(1, .2, .2);
		glVertex3f(0, 0, 0);
		glVertex3f(vdv.x, 0, 0);
		
		glColor3f(.2, 1, .2);
		glVertex3f(0, 0, 0);
		glVertex3f(0, vdv.y, 0);
		
		glColor3f(.2, .2, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -vdv.z);
		
		glColor3f(.8, .8, .8);
		glVertex3f(0, 0, 0);
		glVertex3f(vdv.x, vdv.y, -vdv.z);
	glEnd();
	glPopMatrix();
	
	// Camera MODELVIEW Transformation
	Cam.ViewModel();
	
/*
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
*/
	
	// Enable lighting & update light positions
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
	
	// Render Arena & Minions
	FGArena.Render();
	
/*
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
*/
	
/*
	// Draw a grid
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0f, 0.80f, 0.90f);
	int griddims[3] = {25, 25, 25};
	glTranslatef(-griddims[0], -griddims[1], -griddims[2]);
	for (int gridx = 0; gridx < griddims[0]; ++gridx) {
		for (int gridy = 0; gridy < griddims[1]; ++gridy) {
			for (int gridx = 0; gridx < griddims[0]; ++gridx) {
				
				glBegin(GL_POINTS);
					glVertex3f(0, 0, 0);
				glEnd();
				
				glTranslatef(0, 0, 4);
			}
			glTranslatef(4, 0, 0);
			glTranslatef(0, 0, -4*griddims[2]);
		}
		glTranslatef(-4*griddims[1], 0, 0);
		glTranslatef(0, 4, 0);
	}
	glPopMatrix();
*/
}

void FlightGame::Render2D() {
	Ship& MainShip = *(FGArena.Ships[0]);
	
	// Depth Disable
	glDisable(GL_DEPTH_TEST);
	
	// Orthographic Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Lighting Disable
	glDisable(GL_LIGHTING);
	
	// Reusable Bar Variables
	float BarWidth;
	float VizQ;
	
	// Speed Visualizer
	BarWidth = 15;
	VizQ = MainShip.Speed();
	VizQ *= 500; // Visualization scale
	glPushMatrix();
	glTranslatef(BarWidth, HEIGHT, 0);
	glRotatef(170, 0, 0, -1);
	glColor3f(.3, .3, 1);
	glBegin(GL_QUADS);
		glVertex3f(0,			0, 0);
		glVertex3f(BarWidth,	0, 0);
		glVertex3f(BarWidth,	VizQ, 0);
		glVertex3f(0,			VizQ, 0);
	glEnd();
	glPopMatrix();
	
	// Tractor HUD
	float thrad = 5;
	float thpad = 5;
	glPushMatrix();
	glTranslatef(WIDTH/2 - 2*thrad - thpad, thrad + 5, 0);
	if (MainShip.TractorDir == 0) {
		// Tractor is off
		glColor3f(0, 0, .8);
	} else if (MainShip.TractorDir == 1) {
		// Tractor is push
		glTranslatef(2*thrad + thpad, 0, 0);
		glColor3f(0, .8, 0);
	} else if (MainShip.TractorDir == -1) {
		// Tractor is pull
		glTranslatef(2*thrad + thpad, 0, 0);
		glTranslatef(2*thrad + thpad, 0, 0);
		glColor3f(.8, 0, 0);
	} else {
		std::cout << "Strange, the tractor beam is not going the right way\t" << __LINE__ << "\n";
	}
	gluDisk(GLUQ, 0, thrad, 32, 1);
	glPopMatrix();
		
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
