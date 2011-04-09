#include "Pushable.h"

Pushable::Pushable (float _x, float _y, float _z) {
	Zero();
	Pos.Set(_x, _y, _z);
}

// Return pushable to origin
void Pushable::Zero() {
	Pos.Zero();
	Vel.Zero();
	Accel.Zero();
}

void Pushable::PushGlobal (float _x, float _y, float _z) {
	Accel.x += _x;
	Accel.y += _y;
	Accel.z += _z;
}

void Pushable::Update() {
	Vel += Accel;
	Pos += Vel;
	Accel.Zero();
}