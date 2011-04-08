#include "Oggler.h"

// Constructor
// Set to origin
Oggler::Oggler() {
	Dolly = new Orientable();
}

// View
// Applies openGL transformations to MODLELVIEW
void Oggler::View() {
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Apply to modelview matrix	
	gluLookAt(
		Dolly->Center.x, Dolly->Center.y, Dolly->Center.z,
		Dolly->Center.x + Dolly->Fd.x, Dolly->Center.y + Dolly->Fd.y, Dolly->Center.z + Dolly->Fd.z,
		Dolly->Up.x, Dolly->Up.y, Dolly->Up.z
	);
}
