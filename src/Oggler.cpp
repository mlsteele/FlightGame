#include "Oggler.h"

// Constructor
// Set to origin
Oggler::Oggler() :
	Center(V3D()),
	Rotation(V3D())
{
	
}

// Zero
// Zeros the camera in global space
void Oggler::Zero() {
	Center.Zero();
	Rotation.Zero();
}

// TranslateGlobal
// Translates the camera along the global space
void Oggler::TranslateGlobal(float _x, float _y, float _z) {
	Center.x += _x;
	Center.y += _y;
	Center.z += _z;
}

// RotateGlobal
// Rotates the camera through the global space
void Oggler::RotateGlobal(float _pitch, float _yaw, float _roll) {
	Rotation.x += _pitch;
	Rotation.y += _yaw;
	Rotation.z += _roll;
}

// View
// Applies openGL transformations to MODLELVIEW
void Oggler::View() {
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;
	
	// Rotation
	// Pitch
	glRotatef(
		Rotation.x, 
		1, 0, 0);
	// Yaw
	glRotatef(
		Rotation.y, 
		0, 1, 0);
	// Roll
	glRotatef(
		Rotation.z, 
		0, 0, 1);
	
	// Translation
	glTranslatef(Center.x, Center.y, Center.z);
}
