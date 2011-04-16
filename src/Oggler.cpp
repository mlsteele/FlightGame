#include "Oggler.h"

Oggler::Oggler() {
	Dolly = new Orientable();
	OwnDolly = true;
	Fov = 90;
	Aspect = 4/3;
	Near = 1;
	Far = 500;
}

Oggler::Oggler(Orientable* _dolly) {
	Dolly = _dolly;
	OwnDolly = false;
	Fov = 90;
	Aspect = 4/3;
	Near = 1;
	Far = 500;
}

// Settings
// Camera settings
void Oggler::Settings(float _fov, float _aspect, float _near, float _far) {
	Fov = _fov;
	Aspect = _aspect;
	Near = _near;
	Far = _far;
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
// Applies openGL transformations to MODLELVIEW and PERSPECTIVE
void Oggler::ViewModel() {
	// Modelview Setup
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		Dolly->Pos.x, Dolly->Pos.y, Dolly->Pos.z,
		Dolly->Pos.x + Dolly->Fd.x, Dolly->Pos.y + Dolly->Fd.y, Dolly->Pos.z + Dolly->Fd.z,
		Dolly->Up.x, Dolly->Up.y, Dolly->Up.z
	);
}

void Oggler::ViewPerspective() {
	// Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(Fov, Aspect, Near, Far);
	glMatrixMode(GL_MODELVIEW);
}