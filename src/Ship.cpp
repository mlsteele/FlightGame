#include "Ship.h"

Ship::Ship (V3D _pos, float _mass)
	: Pushable(_pos, _mass)
	, Thrust(V3D(0, 0, 0))
	, Rot(V3D(0, 0, 0))
{
	
}

void Ship::Update() {
	PushLocal(Thrust);
	Pitch(Rot.x);
	Yaw(Rot.y);
	Roll(Rot.z);
	Pushable::Update();
}
