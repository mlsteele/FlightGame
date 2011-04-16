#include "Ship.h"

Ship::Ship (V3D _pos)
	: Pushable(_pos, 5, 2) // Ship mass and radius compiled in
	, Thrust(V3D(0, 0, 0))
	, ThrustFactor(.002)
	, Rot(V3D(0, 0, 0))
{
	
}

void Ship::Update() {
	PushLocal(Thrust * ThrustFactor);
	Pitch(Rot.x);
	Yaw(Rot.y);
	Roll(Rot.z);
	Pushable::Update();
}
