#include "Orientable.h"

// Constructor
// Set to origin
Orientable::Orientable() {
	Zero();
}

// Zero
// Zeros the camera in global space
void Orientable::Zero() {
	Pos.Set(0,0,0);
	Rt.Set(1, 0, 0);
	Up.Set(0, 1, 0);
	Fd.Set(0, 0, 1);
}

// TranslateGlobal
// Translates the camera along the global space
void Orientable::TranslateGlobal(float _x, float _y, float _z) {
	Pos.x += _x;
	Pos.y += _y;
	Pos.z += _z;
}

// TranslateLocal
// Translates the camera along local space
void Orientable::TranslateLocal(float _right, float _up, float _forw) {
	Pos += Rt * _right;
	Pos += Up * _up;
	Pos += Fd * _forw;
}

// Pitch
// Pitch the camera around up vector
void Orientable::Pitch(float _theta) {
	Up.SpinAxis(_theta, Rt);
	Fd.SpinAxis(_theta, Rt);
}

// Yaw
// Yaw the camera around up vector
void Orientable::Yaw(float _theta) {
	Rt.SpinAxis(_theta, Up);
	Fd.SpinAxis(_theta, Up);
}

// Roll
// Rolls the camera around forward vector
void Orientable::Roll(float _theta) {
	Up.SpinAxis(_theta, Fd);
	Rt.SpinAxis(_theta, Fd);
}

// Calibrate
// Normalize camera axis
void Orientable::Calibrate() {
	Fd.Normalize();
	Rt.Normalize();
	Up.Normalize();
}
