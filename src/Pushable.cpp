#include "Pushable.h"
#include "iostream"

Pushable::Pushable (V3D _pos, float _mass) {
	Mass = _mass;
	Pos.Set(_pos);
	Vel.Zero();
	Accel.Zero();
}

void Pushable::PushLocal(V3D _force) {
	_force /= Mass;
	Accel += (Rt * _force.x);
	Accel += (Up * _force.y);
	Accel += (Fd * _force.z);
}

void Pushable::PushGlobal(V3D _force) {
	_force /= Mass;
	Accel += _force;
}

void Pushable::Update() {
	Vel += Accel;
	Pos += Vel;
	Accel.Zero();
	
	// Friction
	Vel *= 0.997127;
}
