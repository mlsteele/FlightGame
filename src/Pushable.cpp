#include "Pushable.h"
#include "iostream"

Pushable::Pushable (V3D<float> _pos, float _mass, float _rad) {
	Mass = _mass;
	Rad = _rad;
	Pos.Set(_pos);
	Vel.Zero();
	Accel.Zero();
}

void Pushable::PushGlobal(V3D<float> _force) {
	_force /= Mass;
	Accel += _force;
}

void Pushable::PushLocal(V3D<float> _force) {
	_force /= Mass;
	Accel += (Rt * _force.x);
	Accel += (Up * _force.y);
	Accel += (Fd * _force.z);
}

/// Explicit Euler integration
void Pushable::Update() {
	Vel += Accel;
	Pos += Vel;
	Accel.Zero();
	
//	// Friction
//	Vel *= 0.997127;
}
