#include "Oggler.h"

// Constructor
// Set to origin
Oggler::Oggler() :
	Center(V3D()),
	Rotation(V3D())
{
	
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
	Center.x += _pitch;
	Center.y += _yaw;
	Center.z += _roll;
}

// View
// Applies openGL transformations to MODLELVIEW
void Oggler::View() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;
	glTranslatef(Center.x, Center.y, Center.z);
}
