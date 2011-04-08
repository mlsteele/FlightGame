#include "Oggler.h"

// Constructor
// Set to origin
Oggler::Oggler() {
	Zero();
}

// Zero
// Zeros the camera in global space
void Oggler::Zero() {
	Center.Set(0,0,0);
	Rt.Set(-1, 0, 0);
	Up.Set(0, -1, 0);
	Fd.Set(0, 0, -1);
}

// TranslateGlobal
// Translates the camera along the global space
void Oggler::TranslateGlobal(float _x, float _y, float _z) {
	Center.x += _x;
	Center.y += _y;
	Center.z += _z;
}

// TranslateLocal
// Translates the camera along local space
void Oggler::TranslateLocal(float _right, float _up, float _forw) {
	Center += Rt * _right;
	Center += Up * _up;
	Center += Fd * _forw;
}

// Pitch
// Pitch the camera over up vector
void Oggler::Pitch(float _theta) {
	Up.SpinAxis(_theta, Rt);
	Fd.SpinAxis(_theta, Rt);
}

// Yaw
// Yaw the camera over up vector
void Oggler::Yaw(float _theta) {
	Rt.SpinAxis(_theta, Up);
	Fd.SpinAxis(_theta, Up);
}

// Roll
// Rolls the camera over forward vector
void Oggler::Roll(float _theta) {
	Up.SpinAxis(_theta, Fd);
	Rt.SpinAxis(_theta, Fd);
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
	
	/* DEPRECATED
	// Camera rotation matrix
	// http://www.songho.ca/opengl/gl_anglestoaxes.html
	GLfloat m_rot[16] = {
		Rt.x, Rt.y, Rt.z, 0,
		Up.x, Up.y, Up.z, 0,
		Fd.x, Fd.y, Fd.z, 0,
		0, 0, 0, 1
	};
	glLoadMatrixf(m_rot);
	*/	
}

// Calibrate
// Normalizes camera axis
void Oggler::Calibrate() {
	Fd.Normalize();
	Rt.Normalize();
	Up.Normalize();
}
