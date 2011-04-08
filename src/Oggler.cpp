#include "Oggler.h"

// Constructor
// Set to origin
Oggler::Oggler() {
	
}

// View
// Applies openGL transformations to MODLELVIEW
void Oggler::View() {
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Apply to modelview matrix	
	gluLookAt(
		Center.x, Center.y, Center.z,
		Center.x + Fd.x, Center.y + Fd.y, Center.z + Fd.z,
		Up.x, Up.y, Up.z
	);
}
