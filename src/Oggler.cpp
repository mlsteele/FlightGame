#include "Oggler.h"

Oggler::Oggler() {
	Dolly = new Orientable();
	OwnDolly = true;
}

Oggler::Oggler(Orientable* _dolly) {
	Dolly = _dolly;
	OwnDolly = false;
}

// Attach
// Attach camera to an orientable
void Oggler::Attach(Orientable* _dolly) {
	if (OwnDolly) {
		delete Dolly;
	}
	
	Dolly = _dolly;
	OwnDolly = false;
}

// View
// Applies openGL transformations to MODLELVIEW
void Oggler::View() {
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Apply to modelview matrix	
	gluLookAt(
		Dolly->Pos.x, Dolly->Pos.y, Dolly->Pos.z,
		Dolly->Pos.x + Dolly->Fd.x, Dolly->Pos.y + Dolly->Fd.y, Dolly->Pos.z + Dolly->Fd.z,
		Dolly->Up.x, Dolly->Up.y, Dolly->Up.z
	);
}
