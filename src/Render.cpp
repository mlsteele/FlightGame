#include "FlightGame.h"

void FlightGame::Render3D() {
	Ship& MainShip = *(*FGArena.Ships.begin());
	
	// Enable Depth
	glEnable(GL_DEPTH_TEST);
	
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Camera MODELVIEW & PERSPECTIVE Transformations
	Cam.ViewPerspective();
	Cam.ViewModel();
	
	// Enable lighting & update light positions
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
	
	// Render Arena & Minions
	FGArena.Render();
	
	// Color Targets
	MainShip.PaintTargets();
	
	
	// Targeting assist
	V3D<float> tline;
	tline += MainShip.Vel;
	tline += MainShip.Fd;
	tline = tline.Normalized() * 100;
	tline += MainShip.Pos;
	
	glDisable(GL_LIGHTING);
	glColor3f(.9, .9, .9);
	glPushMatrix();
		glTranslatef(tline.x, tline.y, tline.z);
		glBegin(GL_LINE_STRIP);
			gluSphere(GLUQ, .5, 10, 10);
		glEnd();
	glPopMatrix();
}

void FlightGame::Render2D() {
	Ship& MainShip = *(*FGArena.Ships.begin());
	
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
	
	
	// Tractor HUD
	float thrad = 5;
	float thpad = 5;
	glPushMatrix();
	glTranslatef(WIDTH/2, thrad + 5, 0);
	if (MainShip.TractorDir == 0) {
		// Tractor is off
		glColor3f(.5, .5, .5);
	} else if (MainShip.TractorDir == 1) {
		// Tractor is push
		glTranslatef(-2*thrad - thpad, 0, 0);
		glColor3f(1, 1, 1);
	} else if (MainShip.TractorDir == -1) {
		// Tractor is pull
		glTranslatef(2*thrad + thpad, 0, 0);
		glColor3f(0, 0, 0);
	} else {
		std::cout << "Strange, the tractor beam is not going the right way\t" << __FILE__ << ": " << __LINE__ << "\n";
	}
	gluDisk(GLUQ, 0, thrad, 32, 1);
	glPopMatrix();
		
	// Mid-Screen
	glPushMatrix();
	glTranslatef(WIDTH/2, HEIGHT/2, 0);
	
	// Reticle
	glColor3f(.1, .1, .1);
	gluDisk(GLUQ, 17, 20, 32, 1);
	
	// Accel Indicator
	// gluPartialDisk(quad, inner, outer, slices, loops, start, sweep)
	//glColor3f(.25, .25, .25);
	//gluPartialDisk(GLUQ, 21, 23, 32, 1, 0, MainShip.Vel.Length()*500);
	//glColor3f(0.6, .6, .6); // Purple
	//gluPartialDisk(GLUQ, 24, 26, 32, 1, .5, MainShip.Fd.Dot(MainShip.Vel) *500);
	
	// Airbrake Indicator
	if (MainShip.BrakeVal != 0) {
		glColor3f(.2, .2, .2);
		gluDisk(GLUQ, 27, 30, 32, 1);
	}
	
	// End Mid-Screen
	glPopMatrix();
	
	// Mouse Cursor
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mX, mY, 0);
	glScalef(.7, .7, 1);
	glColor3f(.4, .4, .4);
	glBegin(GL_TRIANGLES);
		glVertex3f(10, 0, 0);
		glVertex3f(-10, 0, 0);
		glVertex3f(0, 10, 0);
	glEnd();
	glColor3f(.23, .23, .23);
	gluDisk(GLUQ, 15, 20, 4, 1);
	glPopMatrix();
}
