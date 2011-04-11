#include "Pushable.h"
#include "iostream"

Pushable::Pushable (V3D _Position) {
	Pos.Set(_Position);
	Accel.Zero();
}

Pushable::Pushable () {
	Pos.Zero();
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

float Pushable::GetSpeed() {
	return sqrt(
		pow(Vel.x, 2)
		+
		pow(Vel.y, 2)
		+
		pow(Vel.z, 2)
	);
}
