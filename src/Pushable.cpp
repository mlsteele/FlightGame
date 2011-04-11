#include "Pushable.h"
#include "iostream"

Pushable::Pushable () {
	Pos.Zero();
	Accel.Zero();
}

Pushable::Pushable (V3D _Position) {
	Pos.Set(_Position);
	Accel.Zero();
}

void Pushable::PushLocal(V3D _Accel) {
	Accel += (Rt * _Accel.x);
	Accel += (Up * _Accel.y);
	Accel += (Fd * _Accel.z);
}

void Pushable::PushGlobal(V3D _Accel) {
	Accel += _Accel;
}

void Pushable::Update() {
	Vel += Accel;
	Pos += Vel;
	Accel.Zero();
	
	// Friction
	Vel *= 0.997127;
}
